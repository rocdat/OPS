//
// auto-generated by ops.py on 2013-11-27 12:43
//

__constant__ int xdim0_calc_dt_kernel_print;
__constant__ int xdim1_calc_dt_kernel_print;
__constant__ int xdim2_calc_dt_kernel_print;
__constant__ int xdim3_calc_dt_kernel_print;
__constant__ int xdim4_calc_dt_kernel_print;
__constant__ int xdim5_calc_dt_kernel_print;
__constant__ int xdim6_calc_dt_kernel_print;
__constant__ int xdim7_calc_dt_kernel_print;

#define OPS_ACC0(x,y) (x+xdim0_calc_dt_kernel_print*(y))
#define OPS_ACC1(x,y) (x+xdim1_calc_dt_kernel_print*(y))
#define OPS_ACC2(x,y) (x+xdim2_calc_dt_kernel_print*(y))
#define OPS_ACC3(x,y) (x+xdim3_calc_dt_kernel_print*(y))
#define OPS_ACC4(x,y) (x+xdim4_calc_dt_kernel_print*(y))
#define OPS_ACC5(x,y) (x+xdim5_calc_dt_kernel_print*(y))
#define OPS_ACC6(x,y) (x+xdim6_calc_dt_kernel_print*(y))
#define OPS_ACC7(x,y) (x+xdim7_calc_dt_kernel_print*(y))

//user function
__device__

inline void calc_dt_kernel_print(const double *cellx, const double *celly,
                        const double *xvel0, const double *yvel0,
                        const double *density0, const double *energy0,
                        const double *pressure, const double *soundspeed) {
  printf("Cell velocities:\n");
  printf("%E, %E \n",xvel0[OPS_ACC2(1,0)], yvel0[OPS_ACC3(1,0)]);
  printf("%E, %E \n",xvel0[OPS_ACC2(-1,0)], yvel0[OPS_ACC3(-1,0)]);
  printf("%E, %E \n",xvel0[OPS_ACC2(0,1)], yvel0[OPS_ACC3(0,1)]);
  printf("%E, %E \n",xvel0[OPS_ACC2(0,-1)], yvel0[OPS_ACC3(0,-1)]);

  printf("density, energy, pressure, soundspeed = %lf, %lf, %lf, %lf \n",
    density0[OPS_ACC4(0,0)], energy0[OPS_ACC5(0,0)], pressure[OPS_ACC6(0,0)], soundspeed[OPS_ACC7(0,0)]);
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


__global__ void ops_calc_dt_kernel_print(
const double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
const double* __restrict arg6,
const double* __restrict arg7,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 0 * xdim0_calc_dt_kernel_print;
  arg1 += idx_x * 0 + idx_y * 1 * xdim1_calc_dt_kernel_print;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_calc_dt_kernel_print;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_calc_dt_kernel_print;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_calc_dt_kernel_print;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_calc_dt_kernel_print;
  arg6 += idx_x * 1 + idx_y * 1 * xdim6_calc_dt_kernel_print;
  arg7 += idx_x * 1 + idx_y * 1 * xdim7_calc_dt_kernel_print;

  if (idx_x < size0 && idx_y < size1) {
    calc_dt_kernel_print(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7);
  }

}

// host stub function
void ops_par_loop_calc_dt_kernel_print(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];
  int xdim4 = args[4].dat->block_size[0];
  int xdim5 = args[5].dat->block_size[0];
  int xdim6 = args[6].dat->block_size[0];
  int xdim7 = args[7].dat->block_size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(3,"calc_dt_kernel_print");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[3].count == 0) {
    cudaMemcpyToSymbol( xdim0_calc_dt_kernel_print, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_calc_dt_kernel_print, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_calc_dt_kernel_print, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_calc_dt_kernel_print, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_calc_dt_kernel_print, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_calc_dt_kernel_print, &xdim5, sizeof(int) );
    cudaMemcpyToSymbol( xdim6_calc_dt_kernel_print, &xdim6, sizeof(int) );
    cudaMemcpyToSymbol( xdim7_calc_dt_kernel_print, &xdim7, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[8];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 0 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 0 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];

  p_a[4] = &args[4].data_d[
  + args[4].dat->size * args[4].dat->block_size[0] * ( range[2] * 1 - args[4].dat->offset[1] )
  + args[4].dat->size * ( range[0] * 1 - args[4].dat->offset[0] ) ];

  p_a[5] = &args[5].data_d[
  + args[5].dat->size * args[5].dat->block_size[0] * ( range[2] * 1 - args[5].dat->offset[1] )
  + args[5].dat->size * ( range[0] * 1 - args[5].dat->offset[0] ) ];

  p_a[6] = &args[6].data_d[
  + args[6].dat->size * args[6].dat->block_size[0] * ( range[2] * 1 - args[6].dat->offset[1] )
  + args[6].dat->size * ( range[0] * 1 - args[6].dat->offset[0] ) ];

  p_a[7] = &args[7].data_d[
  + args[7].dat->size * args[7].dat->block_size[0] * ( range[2] * 1 - args[7].dat->offset[1] )
  + args[7].dat->size * ( range[0] * 1 - args[7].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 8);


  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_print<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],x_size, y_size);

  if (OPS_diags>1) cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 8);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[3].count++;
  OPS_kernels[3].time += t2-t1;
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg7);
}
