//
// auto-generated by ops.py on 2013-11-27 12:49
//

#include "ops_lib_openmp.h"
#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "calc_dt_kernel.h"

// host stub function
void ops_par_loop_calc_dt_kernel_get(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  int  offs[4][2];
  ops_arg args[4] = { arg0, arg1, arg2, arg3};

  offs[0][0] = 1;  //unit step in x dimension
  offs[0][1] = ops_offs_set(range[0],range[2]+1, args[0]) - ops_offs_set(range[1],range[2], args[0]);
  if (args[0].stencil->stride[0] == 0) {
    offs[0][0] = 0;
    offs[0][1] = args[0].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[0].stencil->stride[1] == 0) {
    offs[0][0] = 1;
    offs[0][1] = -( range[1] - range[0] );
  }

  offs[1][0] = 1;  //unit step in x dimension
  offs[1][1] = ops_offs_set(range[0],range[2]+1, args[1]) - ops_offs_set(range[1],range[2], args[1]);
  if (args[1].stencil->stride[0] == 0) {
    offs[1][0] = 0;
    offs[1][1] = args[1].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[1].stencil->stride[1] == 0) {
    offs[1][0] = 1;
    offs[1][1] = -( range[1] - range[0] );
  }

  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;

  double*arg2h = (double *)arg2.data;
  double*arg3h = (double *)arg3.data;

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif

  //allocate and initialise arrays for global reduction
  //assumes a max of 64 threads with a cacche line size of 64 bytes
  double arg_gbl2[1 * 64 * 64];
  double arg_gbl3[1 * 64 * 64];
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<1; d++ ){
      arg_gbl2[d+64*thr] = ZERO_double;
    }
    for ( int d=0; d<1; d++ ){
      arg_gbl3[d+64*thr] = ZERO_double;
    }
  }

  int y_size = range[3]-range[2];

  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(2,"calc_dt_kernel_get");
  ops_timers_core(&c1,&t1);

  ops_halo_exchanges(args, 4);

  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    char *p_a[4];

    int start = range[2] + ((y_size-1)/nthreads+1)*thr;
    int finish = range[2] +  MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //set up initial pointers
    p_a[0] = &args[0].data[
    + args[0].dat->size * args[0].dat->block_size[0] * ( start * 0 - args[0].dat->offset[1] )
    + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

    p_a[1] = &args[1].data[
    + args[1].dat->size * args[1].dat->block_size[0] * ( start * 1 - args[1].dat->offset[1] )
    + args[1].dat->size * ( range[0] * 0 - args[1].dat->offset[0] ) ];

    p_a[2] = (char *)args[2].data;

    p_a[3] = (char *)args[3].data;


    for ( int n_y=start; n_y<finish; n_y++ ){
      for ( int n_x=range[0]; n_x<range[0]+(range[1]-range[0])/4; n_x++ ){
        //call kernel function, passing in pointers to data - vectorised
        for ( int i=0; i<4; i++ ){
          calc_dt_kernel_get(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*0,
           &arg_gbl2[64*thr], &arg_gbl3[64*thr] );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1)*4;
        p_a[1]= p_a[1] + (dat1 * off1_1)*4;
      }

      for ( int n_x=range[0]+((range[1]-range[0])/4)*4; n_x<range[1]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        calc_dt_kernel_get(  (double *)p_a[0], (double *)p_a[1],
           &arg_gbl2[64*thr], &arg_gbl3[64*thr] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
    }
  }


  // combine reduction data
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<1; d++ ){
      arg2h[0] += arg_gbl2[64*thr];
    }
    for ( int d=0; d<1; d++ ){
      arg3h[0] += arg_gbl3[64*thr];
    }
  }
  ops_set_dirtybit(args, 4);


  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[2].count++;
  OPS_kernels[2].time += t2-t1;
  OPS_kernels[2].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[2].transfer += ops_compute_transfer(dim, range, &arg1);
}
