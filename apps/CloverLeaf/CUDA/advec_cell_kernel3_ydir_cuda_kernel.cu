//
// auto-generated by ops.py on 2013-11-27 12:43
//

__constant__ int xdim0_advec_cell_kernel3_ydir;
__constant__ int xdim1_advec_cell_kernel3_ydir;
__constant__ int xdim2_advec_cell_kernel3_ydir;
__constant__ int xdim3_advec_cell_kernel3_ydir;
__constant__ int xdim4_advec_cell_kernel3_ydir;
__constant__ int xdim5_advec_cell_kernel3_ydir;
__constant__ int xdim6_advec_cell_kernel3_ydir;
__constant__ int xdim7_advec_cell_kernel3_ydir;

#define OPS_ACC0(x,y) (x+xdim0_advec_cell_kernel3_ydir*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_cell_kernel3_ydir*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_cell_kernel3_ydir*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_cell_kernel3_ydir*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_cell_kernel3_ydir*(y))
#define OPS_ACC5(x,y) (x+xdim5_advec_cell_kernel3_ydir*(y))
#define OPS_ACC6(x,y) (x+xdim6_advec_cell_kernel3_ydir*(y))
#define OPS_ACC7(x,y) (x+xdim7_advec_cell_kernel3_ydir*(y))

//user function
__device__

inline void advec_cell_kernel3_ydir( const double *vol_flux_y, const double *pre_vol, const int *yy,
                              const double *vertexdy,
                              const double *density1, const double *energy1 ,
                              double *mass_flux_y, double *ener_flux) {

  double sigma, sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;


  int upwind,donor,downwind,dif;





  if(vol_flux_y[OPS_ACC0(0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (yy[OPS_ACC2(0,1)] < y_max+2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }


  sigmat = fabs(vol_flux_y[OPS_ACC0(0,0)])/pre_vol[OPS_ACC1(0,donor)];
  sigma3 = (1.0 + sigmat)*(vertexdy[OPS_ACC3(0,0)]/vertexdy[OPS_ACC3(0,dif)]);
  sigma4 = 2.0 - sigmat;

  sigma = sigmat;
  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(0,donor)] - density1[OPS_ACC4(0,upwind)];
  diffdw = density1[OPS_ACC4(0,downwind)] - density1[OPS_ACC4(0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_y[OPS_ACC6(0,0)] = (vol_flux_y[OPS_ACC0(0,0)]) * ( density1[OPS_ACC4(0,donor)] + limiter );

  sigmam = fabs(mass_flux_y[OPS_ACC6(0,0)])/( density1[OPS_ACC4(0,donor)] * pre_vol[OPS_ACC1(0,donor)]);
  diffuw = energy1[OPS_ACC5(0,donor)] - energy1[OPS_ACC5(0,upwind)];
  diffdw = energy1[OPS_ACC5(0,downwind)] - energy1[OPS_ACC5(0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0)] = mass_flux_y[OPS_ACC6(0,0)] * ( energy1[OPS_ACC0(0,donor)] + limiter );
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


__global__ void ops_advec_cell_kernel3_ydir(
const double* __restrict arg0,
const double* __restrict arg1,
const int* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_cell_kernel3_ydir;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_cell_kernel3_ydir;
  arg2 += idx_x * 0 + idx_y * 1 * xdim2_advec_cell_kernel3_ydir;
  arg3 += idx_x * 0 + idx_y * 1 * xdim3_advec_cell_kernel3_ydir;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_advec_cell_kernel3_ydir;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_advec_cell_kernel3_ydir;
  arg6 += idx_x * 1 + idx_y * 1 * xdim6_advec_cell_kernel3_ydir;
  arg7 += idx_x * 1 + idx_y * 1 * xdim7_advec_cell_kernel3_ydir;

  if (idx_x < size0 && idx_y < size1) {
    advec_cell_kernel3_ydir(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7);
  }

}

// host stub function
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, int dim, int* range,
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
  ops_timing_realloc(11,"advec_cell_kernel3_ydir");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[11].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_cell_kernel3_ydir, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_cell_kernel3_ydir, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_cell_kernel3_ydir, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_advec_cell_kernel3_ydir, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_advec_cell_kernel3_ydir, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_advec_cell_kernel3_ydir, &xdim5, sizeof(int) );
    cudaMemcpyToSymbol( xdim6_advec_cell_kernel3_ydir, &xdim6, sizeof(int) );
    cudaMemcpyToSymbol( xdim7_advec_cell_kernel3_ydir, &xdim7, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[8];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 0 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 0 - args[3].dat->offset[0] ) ];

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
  ops_advec_cell_kernel3_ydir<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (int *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],x_size, y_size);

  if (OPS_diags>1) cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 8);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[11].count++;
  OPS_kernels[11].time += t2-t1;
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg7);
}
