//
// auto-generated by ops.py
//
__constant__ int xdim0_multidim_reduce_kernel;
int xdim0_multidim_reduce_kernel_h = -1;
int ydim0_multidim_reduce_kernel_h = -1;


#define OPS_ACC_MD0(d,x,y) ((x)*2+(d)+(xdim0_multidim_reduce_kernel*(y)*2))
//user function
__device__

void multidim_reduce_kernel(const double *val, double *redu_dat1) {

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(1,0,0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(2,0,0)];
}




#undef OPS_ACC_MD0

__global__ void ops_multidim_reduce_kernel(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1 ){

  double arg1_l[2];
  for (int d=0; d<2; d++) arg1_l[d] = ZERO_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*2 + idx_y * 1*2 * xdim0_multidim_reduce_kernel;

  if (idx_x < size0 && idx_y < size1) {
    multidim_reduce_kernel(arg0, arg1_l);
  }
  for (int d=0; d<2; d++)
    ops_reduction_cuda<OPS_INC>(&arg1[d+blockIdx.x + blockIdx.y*gridDim.x],arg1_l[d]);

}

// host stub function
void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,2)) return;
  #endif

  ops_timing_realloc(2,"multidim_reduce_kernel");
  OPS_kernels[2].count++;

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  if (xdim0 != xdim0_multidim_reduce_kernel_h) {
    cudaMemcpyToSymbol( xdim0_multidim_reduce_kernel, &xdim0, sizeof(int) );
    xdim0_multidim_reduce_kernel_h = xdim0;
  }


  #ifdef OPS_MPI
  double *arg1h = (double *)(((ops_reduction)args[1].data)->data + ((ops_reduction)args[1].data)->size * block->index);
  #else //OPS_MPI
  double *arg1h = (double *)(((ops_reduction)args[1].data)->data);
  #endif //OPS_MPI

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*2*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*2);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<2; d++) ((double *)arg1.data)[d+b*2] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*2*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->elem_size;

  char *p_a[2];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data_d + base0;


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[2].mpi_time += t1-t2;

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y;

  nshared = MAX(nshared,sizeof(double)*2);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_multidim_reduce_kernel<<<grid, tblock, nshared >>> (  (double *)p_a[0], (double *)arg1.data_d,x_size, y_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<2; d++ ){
      arg1h[d] = arg1h[d] + ((double *)arg1.data)[d+b*2];
    }
  }
  arg1.data = (char *)arg1h;

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[2].time += t2-t1;
  ops_set_dirtybit_device(args, 2);

  //Update kernel record
  OPS_kernels[2].transfer += ops_compute_transfer(dim, range, &arg0);
}
