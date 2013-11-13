//
// auto-generated by ops.py on 2013-11-12 12:46
//

//user function
#include "update_halo_kernel.h"

__global__ void ops_update_halo_kernel3_minus_4_a(
double* __restrict arg0,
double* __restrict arg1,
int* fields_device,
int size0,
int size1 ){

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_device;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_device;
  if (idx_x < size0 && idx_y < size1) {
    update_halo_kernel3_minus_4_a(arg0 ,arg1 , fields_device);
  }
}

// host stub function
void ops_par_loop_update_halo_kernel3_minus_4_a(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};



  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];

  cudaMemcpyToSymbol( xdim0_device, &xdim0, sizeof(int) );
  cudaMemcpyToSymbol( xdim1_device, &xdim1, sizeof(int) );
  cudaMemcpyToSymbol( dt_device,  &dt, sizeof(double) );
  cudaMalloc((void **)&fields_device, sizeof(int)*NUM_FIELDS);
  cudaMemcpy(fields_device, fields , sizeof(int)*NUM_FIELDS, cudaMemcpyHostToDevice);

  char *p_a[2];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 2);

  int block_size = 16;
  dim3 grid( (x_size-1)/block_size+ 1, (y_size-1)/block_size + 1, 1);
  dim3 block(16,16,1);

  //call kernel wrapper function, passing in pointers to data
  ops_update_halo_kernel3_minus_4_a<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],fields_device, x_size, y_size);

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 2);
}
