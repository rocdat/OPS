//
// auto-generated by ops.py on 2014-03-21 10:18
//

#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "accelerate_kernel.h"

// host stub function
void ops_par_loop_accelerate_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7,
 ops_arg arg8, ops_arg arg9, ops_arg arg10) {

  int  offs[11][2];
  ops_arg args[11] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block

  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = sb->istart[n];end[n] = sb->iend[n]+1;
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end[n] = sb->sizes[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "accelerate_kernel");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
  &end[0],args[0].dat->block_size, args[0].stencil->stride);

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
  &end[0],args[1].dat->block_size, args[1].stencil->stride);

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off2D(1, &start[0],
  &end[0],args[2].dat->block_size, args[2].stencil->stride);

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off2D(1, &start[0],
  &end[0],args[3].dat->block_size, args[3].stencil->stride);

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off2D(1, &start[0],
  &end[0],args[4].dat->block_size, args[4].stencil->stride);

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off2D(1, &start[0],
  &end[0],args[5].dat->block_size, args[5].stencil->stride);

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off2D(1, &start[0],
  &end[0],args[6].dat->block_size, args[6].stencil->stride);

  offs[7][0] = args[7].stencil->stride[0]*1;  //unit step in x dimension
  offs[7][1] = off2D(1, &start[0],
  &end[0],args[7].dat->block_size, args[7].stencil->stride);

  offs[8][0] = args[8].stencil->stride[0]*1;  //unit step in x dimension
  offs[8][1] = off2D(1, &start[0],
  &end[0],args[8].dat->block_size, args[8].stencil->stride);

  offs[9][0] = args[9].stencil->stride[0]*1;  //unit step in x dimension
  offs[9][1] = off2D(1, &start[0],
  &end[0],args[9].dat->block_size, args[9].stencil->stride);

  offs[10][0] = args[10].stencil->stride[0]*1;  //unit step in x dimension
  offs[10][1] = off2D(1, &start[0],
  &end[0],args[10].dat->block_size, args[10].stencil->stride);



  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;
  int off2_1 = offs[2][0];
  int off2_2 = offs[2][1];
  int dat2 = args[2].dat->size;
  int off3_1 = offs[3][0];
  int off3_2 = offs[3][1];
  int dat3 = args[3].dat->size;
  int off4_1 = offs[4][0];
  int off4_2 = offs[4][1];
  int dat4 = args[4].dat->size;
  int off5_1 = offs[5][0];
  int off5_2 = offs[5][1];
  int dat5 = args[5].dat->size;
  int off6_1 = offs[6][0];
  int off6_2 = offs[6][1];
  int dat6 = args[6].dat->size;
  int off7_1 = offs[7][0];
  int off7_2 = offs[7][1];
  int dat7 = args[7].dat->size;
  int off8_1 = offs[8][0];
  int off8_2 = offs[8][1];
  int dat8 = args[8].dat->size;
  int off9_1 = offs[9][0];
  int off9_2 = offs[9][1];
  int dat9 = args[9].dat->size;
  int off10_1 = offs[10][0];
  int off10_2 = offs[10][1];
  int dat10 = args[10].dat->size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  xdim7 = args[7].dat->block_size[0]*args[7].dat->dim;
  xdim8 = args[8].dat->block_size[0]*args[8].dat->dim;
  xdim9 = args[9].dat->block_size[0]*args[9].dat->dim;
  xdim10 = args[10].dat->block_size[0]*args[10].dat->dim;

  int max0[2]; int min0[2];
  for ( int n=0; n<2; n++ ){
    max0[n] = 0;min0[n] = 0;
  }
  for ( int p=0; p<args[0].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max0[n] = MAX(max0[n],args[0].stencil->stencil[2*p + n]);
      min0[n] = MIN(min0[n],args[0].stencil->stencil[2*p + n]);
    }
  }
  int max1[2]; int min1[2];
  for ( int n=0; n<2; n++ ){
    max1[n] = 0;min1[n] = 0;
  }
  for ( int p=0; p<args[1].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max1[n] = MAX(max1[n],args[1].stencil->stencil[2*p + n]);
      min1[n] = MIN(min1[n],args[1].stencil->stencil[2*p + n]);
    }
  }
  int max2[2]; int min2[2];
  for ( int n=0; n<2; n++ ){
    max2[n] = 0;min2[n] = 0;
  }
  for ( int p=0; p<args[2].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max2[n] = MAX(max2[n],args[2].stencil->stencil[2*p + n]);
      min2[n] = MIN(min2[n],args[2].stencil->stencil[2*p + n]);
    }
  }
  int max3[2]; int min3[2];
  for ( int n=0; n<2; n++ ){
    max3[n] = 0;min3[n] = 0;
  }
  for ( int p=0; p<args[3].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max3[n] = MAX(max3[n],args[3].stencil->stencil[2*p + n]);
      min3[n] = MIN(min3[n],args[3].stencil->stencil[2*p + n]);
    }
  }
  int max4[2]; int min4[2];
  for ( int n=0; n<2; n++ ){
    max4[n] = 0;min4[n] = 0;
  }
  for ( int p=0; p<args[4].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max4[n] = MAX(max4[n],args[4].stencil->stencil[2*p + n]);
      min4[n] = MIN(min4[n],args[4].stencil->stencil[2*p + n]);
    }
  }
  int max5[2]; int min5[2];
  for ( int n=0; n<2; n++ ){
    max5[n] = 0;min5[n] = 0;
  }
  for ( int p=0; p<args[5].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max5[n] = MAX(max5[n],args[5].stencil->stencil[2*p + n]);
      min5[n] = MIN(min5[n],args[5].stencil->stencil[2*p + n]);
    }
  }
  int max6[2]; int min6[2];
  for ( int n=0; n<2; n++ ){
    max6[n] = 0;min6[n] = 0;
  }
  for ( int p=0; p<args[6].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max6[n] = MAX(max6[n],args[6].stencil->stencil[2*p + n]);
      min6[n] = MIN(min6[n],args[6].stencil->stencil[2*p + n]);
    }
  }
  int max7[2]; int min7[2];
  for ( int n=0; n<2; n++ ){
    max7[n] = 0;min7[n] = 0;
  }
  for ( int p=0; p<args[7].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max7[n] = MAX(max7[n],args[7].stencil->stencil[2*p + n]);
      min7[n] = MIN(min7[n],args[7].stencil->stencil[2*p + n]);
    }
  }
  int max8[2]; int min8[2];
  for ( int n=0; n<2; n++ ){
    max8[n] = 0;min8[n] = 0;
  }
  for ( int p=0; p<args[8].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max8[n] = MAX(max8[n],args[8].stencil->stencil[2*p + n]);
      min8[n] = MIN(min8[n],args[8].stencil->stencil[2*p + n]);
    }
  }
  int max9[2]; int min9[2];
  for ( int n=0; n<2; n++ ){
    max9[n] = 0;min9[n] = 0;
  }
  for ( int p=0; p<args[9].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max9[n] = MAX(max9[n],args[9].stencil->stencil[2*p + n]);
      min9[n] = MIN(min9[n],args[9].stencil->stencil[2*p + n]);
    }
  }
  int max10[2]; int min10[2];
  for ( int n=0; n<2; n++ ){
    max10[n] = 0;min10[n] = 0;
  }
  for ( int p=0; p<args[10].stencil->points; p++ ){
    for ( int n=0; n<2; n++ ){
      max10[n] = MAX(max10[n],args[10].stencil->stencil[2*p + n]);
      min10[n] = MIN(min10[n],args[10].stencil->stencil[2*p + n]);
    }
  }
  //Halo Exchanges
  ops_exchange_halo2(&args[0],max0,min0);
  ops_exchange_halo2(&args[1],max1,min1);
  ops_exchange_halo2(&args[3],max3,min3);
  ops_exchange_halo2(&args[5],max5,min5);
  ops_exchange_halo2(&args[6],max6,min6);
  ops_exchange_halo2(&args[7],max7,min7);
  ops_exchange_halo2(&args[9],max9,min9);
  ops_exchange_halo2(&args[10],max10,min10);

  ops_H_D_exchanges(args, 11);


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(47,"accelerate_kernel");
  ops_timers_core(&c1,&t1);


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    //start index for each dimension
    int start0;
    int start1;

    int y_size = end[1]-start[1];
    char *p_a[11];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get addresss per thread
    start0 = start[0];
    start1 = start[1] + ((y_size-1)/nthreads+1)*thr;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->offset[0]);
    base0 = base0  + dat0 * args[0].dat->block_size[0] * 
    (start1 * args[0].stencil->stride[1] - args[0].dat->offset[1]);
    p_a[0] = (char *)args[0].data + base0;

    //set up initial pointers 
    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->offset[0]);
    base1 = base1  + dat1 * args[1].dat->block_size[0] * 
    (start1 * args[1].stencil->stride[1] - args[1].dat->offset[1]);
    p_a[1] = (char *)args[1].data + base1;

    //set up initial pointers 
    int base2 = dat2 * 1 * 
    (start0 * args[2].stencil->stride[0] - args[2].dat->offset[0]);
    base2 = base2  + dat2 * args[2].dat->block_size[0] * 
    (start1 * args[2].stencil->stride[1] - args[2].dat->offset[1]);
    p_a[2] = (char *)args[2].data + base2;

    //set up initial pointers 
    int base3 = dat3 * 1 * 
    (start0 * args[3].stencil->stride[0] - args[3].dat->offset[0]);
    base3 = base3  + dat3 * args[3].dat->block_size[0] * 
    (start1 * args[3].stencil->stride[1] - args[3].dat->offset[1]);
    p_a[3] = (char *)args[3].data + base3;

    //set up initial pointers 
    int base4 = dat4 * 1 * 
    (start0 * args[4].stencil->stride[0] - args[4].dat->offset[0]);
    base4 = base4  + dat4 * args[4].dat->block_size[0] * 
    (start1 * args[4].stencil->stride[1] - args[4].dat->offset[1]);
    p_a[4] = (char *)args[4].data + base4;

    //set up initial pointers 
    int base5 = dat5 * 1 * 
    (start0 * args[5].stencil->stride[0] - args[5].dat->offset[0]);
    base5 = base5  + dat5 * args[5].dat->block_size[0] * 
    (start1 * args[5].stencil->stride[1] - args[5].dat->offset[1]);
    p_a[5] = (char *)args[5].data + base5;

    //set up initial pointers 
    int base6 = dat6 * 1 * 
    (start0 * args[6].stencil->stride[0] - args[6].dat->offset[0]);
    base6 = base6  + dat6 * args[6].dat->block_size[0] * 
    (start1 * args[6].stencil->stride[1] - args[6].dat->offset[1]);
    p_a[6] = (char *)args[6].data + base6;

    //set up initial pointers 
    int base7 = dat7 * 1 * 
    (start0 * args[7].stencil->stride[0] - args[7].dat->offset[0]);
    base7 = base7  + dat7 * args[7].dat->block_size[0] * 
    (start1 * args[7].stencil->stride[1] - args[7].dat->offset[1]);
    p_a[7] = (char *)args[7].data + base7;

    //set up initial pointers 
    int base8 = dat8 * 1 * 
    (start0 * args[8].stencil->stride[0] - args[8].dat->offset[0]);
    base8 = base8  + dat8 * args[8].dat->block_size[0] * 
    (start1 * args[8].stencil->stride[1] - args[8].dat->offset[1]);
    p_a[8] = (char *)args[8].data + base8;

    //set up initial pointers 
    int base9 = dat9 * 1 * 
    (start0 * args[9].stencil->stride[0] - args[9].dat->offset[0]);
    base9 = base9  + dat9 * args[9].dat->block_size[0] * 
    (start1 * args[9].stencil->stride[1] - args[9].dat->offset[1]);
    p_a[9] = (char *)args[9].data + base9;

    //set up initial pointers 
    int base10 = dat10 * 1 * 
    (start0 * args[10].stencil->stride[0] - args[10].dat->offset[0]);
    base10 = base10  + dat10 * args[10].dat->block_size[0] * 
    (start1 * args[10].stencil->stride[1] - args[10].dat->offset[1]);
    p_a[10] = (char *)args[10].data + base10;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          accelerate_kernel(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (double *)p_a[2]+ i*1,
           (double *)p_a[3]+ i*1, (double *)p_a[4]+ i*1, (double *)p_a[5]+ i*1, (double *)p_a[6]+ i*1,
           (double *)p_a[7]+ i*1, (double *)p_a[8]+ i*1, (double *)p_a[9]+ i*1, (double *)p_a[10]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_1)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_1)*SIMD_VEC;
        p_a[3]= p_a[3] + (dat3 * off3_1)*SIMD_VEC;
        p_a[4]= p_a[4] + (dat4 * off4_1)*SIMD_VEC;
        p_a[5]= p_a[5] + (dat5 * off5_1)*SIMD_VEC;
        p_a[6]= p_a[6] + (dat6 * off6_1)*SIMD_VEC;
        p_a[7]= p_a[7] + (dat7 * off7_1)*SIMD_VEC;
        p_a[8]= p_a[8] + (dat8 * off8_1)*SIMD_VEC;
        p_a[9]= p_a[9] + (dat9 * off9_1)*SIMD_VEC;
        p_a[10]= p_a[10] + (dat10 * off10_1)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        accelerate_kernel(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3], (double *)p_a[4], (double *)p_a[5], (double *)p_a[6],
           (double *)p_a[7], (double *)p_a[8], (double *)p_a[9], (double *)p_a[10] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
        p_a[5]= p_a[5] + (dat5 * off5_1);
        p_a[6]= p_a[6] + (dat6 * off6_1);
        p_a[7]= p_a[7] + (dat7 * off7_1);
        p_a[8]= p_a[8] + (dat8 * off8_1);
        p_a[9]= p_a[9] + (dat9 * off9_1);
        p_a[10]= p_a[10] + (dat10 * off10_1);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
      p_a[5]= p_a[5] + (dat5 * off5_2);
      p_a[6]= p_a[6] + (dat6 * off6_2);
      p_a[7]= p_a[7] + (dat7 * off7_2);
      p_a[8]= p_a[8] + (dat8 * off8_2);
      p_a[9]= p_a[9] + (dat9 * off9_2);
      p_a[10]= p_a[10] + (dat10 * off10_2);
    }
  }
  ops_set_dirtybit_host(args, 11);

  ops_set_halo_dirtybit(&args[2]);
  ops_set_halo_dirtybit(&args[4]);
  ops_set_halo_dirtybit(&args[8]);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[47].count++;
  OPS_kernels[47].time += t2-t1;
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg7);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg8);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg9);
  OPS_kernels[47].transfer += ops_compute_transfer(dim, range, &arg10);
}
