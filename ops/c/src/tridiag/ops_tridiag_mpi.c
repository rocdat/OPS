/*
* Open source copyright declaration based on BSD open source template:
* http://www.opensource.org/licenses/bsd-license.php
*
* This file is part of the OPS distribution.
*
* Copyright (c) 2013, Mike Giles and others. Please see the AUTHORS file in
* the main source directory for a full list of copyright holders.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * The name of Mike Giles may not be used to endorse or promote products
* derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Mike Giles ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Mike Giles BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* @brief OPS API calls and wrapper routins for Tridiagonal solvers
* @author Gihan Mudalige, Istvan Reguly
* @details Implementations of the OPS API calls, wrapper routines and other
* functions for interfacing with external Tridiagonal libraries
*/

#include <ops_lib_core.h>
#include <ops_mpi_core.h>

#define FP double // doubles when calling thomas should be FPs
#define N_MAX 1024
#include "trid_mpi_cpu.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void ops_initTridMultiDimBatchSolve(int ndim, int *dims) {
  // dummy routine for non-GPU backends
}

void ops_tridMultiDimBatch(
    int ndim,     // number of dimsnsions, ndim <= MAXDIM = 8
    int solvedim, // user chosen dimension to perform solve
    int *dims,    // array containing the sizes of each ndim dimensions
    ops_dat a, ops_dat b, ops_dat c, // left hand side coefficients of a
    // multidimensional problem. An array containing
    // A matrices of individual problems
    ops_dat d, // right hand side coefficients of a multidimensional problem. An
               // array containing d column vectors of individual problems
    ops_dat u,
    int *opts // indicates different algorithms to use -- not used for CPU
              // backends
    ) {

  /*Do only the X dim solver .. later generalize for all three dims*/

  int a_size[3] = {a->size[0] + a->d_m[0] - a->d_p[0],
                   a->size[1] + a->d_m[1] - a->d_p[1],
                   a->size[2] + a->d_m[2] - a->d_p[2]};
  int b_size[3] = {b->size[0] + b->d_m[0] - b->d_p[0],
                   b->size[1] + b->d_m[1] - b->d_p[1],
                   b->size[2] + b->d_m[2] - b->d_p[2]};
  int c_size[3] = {c->size[0] + c->d_m[0] - c->d_p[0],
                   c->size[1] + c->d_m[1] - c->d_p[1],
                   c->size[2] + c->d_m[2] - c->d_p[2]};
  int d_size[3] = {d->size[0] + d->d_m[0] - d->d_p[0],
                   d->size[1] + d->d_m[1] - d->d_p[1],
                   d->size[2] + d->d_m[2] - d->d_p[2]};
  int u_size[3] = {u->size[0] + u->d_m[0] - u->d_p[0],
                   u->size[1] + u->d_m[1] - u->d_p[1],
                   u->size[2] + u->d_m[2] - u->d_p[2]};

  // check if sizes match
  for (int i = 0; i < 3; i++) {
    if (a_size[i] != b_size[i] || b_size[i] != c_size[i] ||
        c_size[i] != d_size[i] || u_size[i] != u_size[i]) {
      ops_printf("Size Mistmatch: Abort\n");
      exit(-2);
    }
  }

  // compute tridiagonal system sizes
  ops_block block = a->block;
  sub_block *sb = OPS_sub_block_list[block->index];
  int sys_len_l = sb->pdims[0] * 2;         // Reduced system size in x dim
  int n_sys_g = a_size[1] * a_size[2];      // ny*nz
  int n_sys_l_tmp = n_sys_g / sb->pdims[0]; // mpi.procs;
  int n_sys_l = (1 + (n_sys_l_tmp - 1) / sb->pdims[0]) * sb->pdims[0];

  // create separate coommunicator for x dimension communications
  int free_coords[3];
  MPI_Comm x_comm;
  free_coords[0] = 1;
  free_coords[1] = 0;
  free_coords[2] = 0;
  MPI_Cart_sub(sb->comm, free_coords, &x_comm);

  // Containers used to communicate preprocess halo
  double *halo_sndbuf = (double *)ops_malloc(n_sys_l * sys_len_l * 3 *
                                             sizeof(double)); // Send Buffer
  double *halo_rcvbuf = (double *)ops_malloc(n_sys_l * sys_len_l * 3 *
                                             sizeof(double)); // Receive Buffer
  double *halo_sndbuf2 = (double *)ops_malloc(2 * a_size[1] * a_size[2] *
                                              sizeof(double)); // Send Buffer
  double *halo_rcvbuf2 = (double *)ops_malloc(2 * a_size[1] * a_size[2] *
                                              sizeof(double)); // Receive Buffer

  // Containers used to communicate reduced system
  double *aa_r = (double *)ops_malloc(sizeof(double) * sys_len_l * n_sys_l);
  double *cc_r = (double *)ops_malloc(sizeof(double) * sys_len_l * n_sys_l);
  double *dd_r = (double *)ops_malloc(sizeof(double) * sys_len_l * n_sys_l);

  // Do modified Thomas
  double *aa =
      (double *)ops_malloc(sizeof(double) * a_size[0] * a_size[1] * a_size[2]);
  double *bb =
      (double *)ops_malloc(sizeof(double) * b_size[0] * b_size[1] * b_size[2]);
  double *cc =
      (double *)ops_malloc(sizeof(double) * c_size[0] * c_size[1] * c_size[2]);
  double *dd =
      (double *)ops_malloc(sizeof(double) * d_size[0] * d_size[1] * d_size[2]);
#pragma omp parallel for
  for (int id = 0; id < n_sys_g; id++) {
    int a_base = id * a->size[0] - a->d_m[0];
    int b_base = id * b->size[0] - b->d_m[0];
    int c_base = id * c->size[0] - c->d_m[0];
    int d_base = id * d->size[0] - d->d_m[0];
    int u_base = id * u->size[0] - u->d_m[0];

    int base = id * a_size[0];
    thomas_forward((&((const double *)a->data)[a_base]),
                   (&((const double *)b->data)[b_base]),
                   (&((const double *)c->data)[c_base]),
                   (&((const double *)d->data)[d_base]),
                   (&((const double *)u->data)[u_base]), (double *)(&aa[base]),
                   (double *)(&cc[base]), (double *)(&dd[base]), a_size[0], 1);
  }

  // Communicate boundary values
  // Pack boundary to a single data structure
  #pragma omp parallel for
    for (int id = 0; id < n_sys_g; id++) {
      // Gather coefficients of a,c,d
      halo_sndbuf[id * 3 * 2 + 0 * 2] = aa[id * a_size[0]];
      halo_sndbuf[id * 3 * 2 + 0 * 2 + 1] = aa[id * a_size[0] + a_size[0] - 1];
      halo_sndbuf[id * 3 * 2 + 1 * 2] = cc[id * a_size[0]];
      halo_sndbuf[id * 3 * 2 + 1 * 2 + 1] = cc[id * a_size[0] + a_size[0] - 1];
      halo_sndbuf[id * 3 * 2 + 2 * 2] = dd[id * a_size[0]];
      halo_sndbuf[id * 3 * 2 + 2 * 2 + 1] = dd[id * a_size[0] + a_size[0] - 1];
    }

    MPI_Alltoall(halo_sndbuf, n_sys_l * 3 * 2, MPI_DOUBLE, halo_rcvbuf,
                 n_sys_l * 3 * 2, MPI_DOUBLE, x_comm);

  // Unpack boundary data
  #pragma omp parallel for collapse(2)
    for (int p = 0; p < sb->pdims[0]; p++) {
      for (int id = 0; id < n_sys_l; id++) {
        aa_r[id * sys_len_l + p * 2] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 0 * 2];
        aa_r[id * sys_len_l + p * 2 + 1] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 0 * 2 + 1];
        cc_r[id * sys_len_l + p * 2] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 1 * 2];
        cc_r[id * sys_len_l + p * 2 + 1] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 1 * 2 + 1];
        dd_r[id * sys_len_l + p * 2] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 2 * 2];
        dd_r[id * sys_len_l + p * 2 + 1] =
            halo_rcvbuf[p * n_sys_l * 3 * 2 + id * 3 * 2 + 2 * 2 + 1];
      }
    }

  // Compute reduced system
  #pragma omp parallel for
    for (int id = 0; id < n_sys_l; id++) {
      int base = id * sys_len_l;
      thomas_on_reduced(&aa_r[base], &cc_r[base], &dd_r[base], sys_len_l, 1);
    }

  // Pack boundary solution data
  #pragma omp parallel for
    for (int p = 0; p < sb->pdims[0]; p++) {
      for (int id = 0; id < n_sys_l; id++) {
        halo_rcvbuf[p * n_sys_l * 2 + id * 2] = dd_r[id * sys_len_l + p * 2];
        halo_rcvbuf[p * n_sys_l * 2 + id * 2 + 1] =
            dd_r[id * sys_len_l + p * 2 + 1];
      }
    }

    // Send back new values
    MPI_Alltoall(halo_rcvbuf, n_sys_l * 2, MPI_DOUBLE, halo_sndbuf, n_sys_l * 2,
                 MPI_DOUBLE, x_comm);

  // Unpack boundary solution
  #pragma omp parallel for
    for (int id = 0; id < n_sys_g; id++) {
      // Gather coefficients of a,c,d
      dd[id * a_size[0]] = halo_sndbuf[id * 2];
      dd[id * a_size[0] + a_size[0] - 1] = halo_sndbuf[id * 2 + 1];
    }

  // Do the backward pass of modified Thomas
  #pragma omp parallel for
    for (int id = 0; id < n_sys_g; id++) {
      int u_base = id * u->size[0] - u->d_m[0];
      int base = id * a_size[0];
      thomas_backward((double *)(&aa[base]), (double *)(&cc[base]),
                      (double *)(&dd[base]), &((double *)u->data)[u_base],
                      a_size[0], 1);
    }

  ops_free(aa);
  ops_free(bb);
  ops_free(cc);
  ops_free(dd);


  /* Right now, we are simply using the same memory allocated by OPS
  as can be seen by the use of a->data, b->data, c->data etc.

  These data is currently not padded to be 32 or 64 bit aligned
  in the x-lines and so is inefficient.

  In the ADI example currently the mesh size is 256^3 and so we are
  32/54 bit alighed, thus we do not see any performance definiencies
  but other sizes will show this issue

  As such we will need to think on how to pad arrays.
  The problem is that on apps like Cloverleaf we see poorer performance
  due to extra x dim padding.
  */

  /*
  For MPI padding will be more important as the partition allocated per MPI proc
  will definitely not be a multiple of 32 or 64 in the x dimension

  Perhaps we make use of a setup phase to add padding to the ops data arrays
  and then use them in the tridiagonal solvers. But now the problem is
  that the original OPS lib will not be able to use these padded arrays
  and produce correct results -- need to think how to solve this
  */
}

void ops_tridMultiDimBatch_Inc(
    int ndim,     // number of dimsnsions, ndim <= MAXDIM = 8
    int solvedim, // user chosen dimension to perform solve
    int *dims,    // array containing the sizes of each ndim dimensions
    ops_dat a, ops_dat b, ops_dat c, // left hand side coefficients of a
    // multidimensional problem. An array containing
    // A matrices of individual problems
    ops_dat d, // right hand side coefficients of a multidimensional problem. An
               // array containing d column vectors of individual problems
    ops_dat u,
    int *opts // indicates different algorithms to use -- not used for CPU
              // backends
    ) {

  /*tridDmtsvStridedBatchInc((const double *)a->data,
    (const double *)b->data,
    (const double *)c->data,
    (double *)d->data, (double *)u->data, ndim, solvedim, dims, dims);*/
}

void ops_exitTridMultiDimBatchSolve() {
  // free memory allocated during tridiagonal solve e.g. mpi buffers
}

#ifdef __cplusplus
}
#endif