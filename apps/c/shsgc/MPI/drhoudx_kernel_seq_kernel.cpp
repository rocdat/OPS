//
// auto-generated by ops.py
//

// user function
inline void drhoudx_kernel(const double *rhou_new, double *rho_res) {

  double fnim1 = rhou_new[OPS_ACC0(-1)];
  double fnim2 = rhou_new[OPS_ACC0(-2)];
  double fnip1 = rhou_new[OPS_ACC0(1)];
  double fnip2 = rhou_new[OPS_ACC0(2)];

  double deriv = (fnim2 - fnip2 + 8.0 * (fnip1 - fnim1)) / (12.00 * dx);
  rho_res[OPS_ACC1(0)] = deriv;
}

// host stub function
void ops_par_loop_drhoudx_kernel(char const *name, ops_block block, int dim,
                                 int *range, ops_arg arg0, ops_arg arg1) {

  // Timing
  double t1, t2, c1, c2;

  char *p_a[2];
  int offs[2][1];
  ops_arg args[2] = {arg0, arg1};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 2, range, 3))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(3, "drhoudx_kernel");
    OPS_kernels[3].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[1];
  int end[1];

#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 1; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 1; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif
#ifdef OPS_DEBUG
  ops_register_args(args, "drhoudx_kernel");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension

  int off0_0 = offs[0][0];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset +
              (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
                  start[0] * args[0].stencil->stride[0];
  p_a[0] = (char *)args[0].data + base0;

  int base1 = args[1].dat->base_offset +
              (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size) *
                  start[0] * args[1].stencil->stride[0];
  p_a[1] = (char *)args[1].data + base1;

  // initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args, 2, range);
  ops_H_D_exchanges_host(args, 2);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[3].mpi_time += t1 - t2;
  }

  int n_x;
#pragma novector
  for (n_x = start[0];
       n_x < start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
       n_x += SIMD_VEC) {
// call kernel function, passing in pointers to data -vectorised
#pragma simd
    for (int i = 0; i < SIMD_VEC; i++) {
      drhoudx_kernel((double *)p_a[0] + i * 1 * 1,
                     (double *)p_a[1] + i * 1 * 1);
    }

    // shift pointers to data x direction
    p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
    p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
  }

  for (int n_x = start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
       n_x < end[0]; n_x++) {
    // call kernel function, passing in pointers to data - remainder
    drhoudx_kernel((double *)p_a[0], (double *)p_a[1]);

    // shift pointers to data x direction
    p_a[0] = p_a[0] + (dat0 * off0_0);
    p_a[1] = p_a[1] + (dat1 * off1_0);
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[3].time += t2 - t1;
  }
  ops_set_dirtybit_host(args, 2);
  ops_set_halo_dirtybit3(&args[1], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[3].mpi_time += t1 - t2;
    OPS_kernels[3].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[3].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
