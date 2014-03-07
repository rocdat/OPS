//
// auto-generated by ops.py on 2014-03-07 14:06
//

__constant__ int xdim0_advec_mom_kernel_pre_advec_y;
__constant__ int xdim1_advec_mom_kernel_pre_advec_y;
__constant__ int xdim2_advec_mom_kernel_pre_advec_y;

#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel_pre_advec_y*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel_pre_advec_y*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel_pre_advec_y*(y))

//user function
__device__

inline void advec_mom_kernel_pre_advec_y( double *node_mass_pre, const double *node_mass_post,
                                  const double *node_flux) {

  node_mass_pre[OPS_ACC0(0,0)] = node_mass_post[OPS_ACC1(0,0)] - node_flux[OPS_ACC2(0,-1)] + node_flux[OPS_ACC2(0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


__global__ void ops_advec_mom_kernel_pre_advec_y(
double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_mom_kernel_pre_advec_y;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_mom_kernel_pre_advec_y;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_advec_mom_kernel_pre_advec_y;

  if (idx_x < size0 && idx_y < size1) {
    advec_mom_kernel_pre_advec_y(arg0, arg1, arg2);
  }

}

// host stub function
void ops_par_loop_advec_mom_kernel_pre_advec_y(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(31,"advec_mom_kernel_pre_advec_y");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[31].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_mom_kernel_pre_advec_y, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_mom_kernel_pre_advec_y, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_mom_kernel_pre_advec_y, &xdim2, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[3];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];


  ops_H_D_exchanges_cuda(args, 3);


  //call kernel wrapper function, passing in pointers to data
  ops_advec_mom_kernel_pre_advec_y<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2],x_size, y_size);

  if (OPS_diags>1) cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 3);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[31].count++;
  OPS_kernels[31].time += t2-t1;
  OPS_kernels[31].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[31].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[31].transfer += ops_compute_transfer(dim, range, &arg2);
}
