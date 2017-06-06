//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_calc_dt_kernel;
extern int ydim0_calc_dt_kernel;
extern int xdim1_calc_dt_kernel;
extern int ydim1_calc_dt_kernel;
extern int xdim2_calc_dt_kernel;
extern int ydim2_calc_dt_kernel;
extern int xdim3_calc_dt_kernel;
extern int ydim3_calc_dt_kernel;
extern int xdim4_calc_dt_kernel;
extern int ydim4_calc_dt_kernel;
extern int xdim5_calc_dt_kernel;
extern int ydim5_calc_dt_kernel;
extern int xdim6_calc_dt_kernel;
extern int ydim6_calc_dt_kernel;
extern int xdim7_calc_dt_kernel;
extern int ydim7_calc_dt_kernel;
extern int xdim8_calc_dt_kernel;
extern int ydim8_calc_dt_kernel;
extern int xdim9_calc_dt_kernel;
extern int ydim9_calc_dt_kernel;
extern int xdim10_calc_dt_kernel;
extern int ydim10_calc_dt_kernel;
extern int xdim11_calc_dt_kernel;
extern int ydim11_calc_dt_kernel;
extern int xdim12_calc_dt_kernel;
extern int ydim12_calc_dt_kernel;
extern int xdim13_calc_dt_kernel;
extern int ydim13_calc_dt_kernel;

#undef OPS_OPENMP40
#undef OPS_OPENMP41
#undef OPS_OPENMP42
#undef OPS_OPENMP43
#undef OPS_OPENMP44
#undef OPS_OPENMP45
#undef OPS_OPENMP46
#undef OPS_OPENMP47
#undef OPS_OPENMP48
#undef OPS_OPENMP49
#undef OPS_OPENMP410
#undef OPS_OPENMP411
#undef OPS_OPENMP412
#undef OPS_OPENMP413

#define OPS_OPENMP40(x, y, z)                                                  \
  (x + xdim0_calc_dt_kernel * (y) +                                            \
   xdim0_calc_dt_kernel * ydim0_calc_dt_kernel * (z))
#define OPS_OPENMP41(x, y, z)                                                  \
  (x + xdim1_calc_dt_kernel * (y) +                                            \
   xdim1_calc_dt_kernel * ydim1_calc_dt_kernel * (z))
#define OPS_OPENMP42(x, y, z)                                                  \
  (x + xdim2_calc_dt_kernel * (y) +                                            \
   xdim2_calc_dt_kernel * ydim2_calc_dt_kernel * (z))
#define OPS_OPENMP43(x, y, z)                                                  \
  (x + xdim3_calc_dt_kernel * (y) +                                            \
   xdim3_calc_dt_kernel * ydim3_calc_dt_kernel * (z))
#define OPS_OPENMP44(x, y, z)                                                  \
  (x + xdim4_calc_dt_kernel * (y) +                                            \
   xdim4_calc_dt_kernel * ydim4_calc_dt_kernel * (z))
#define OPS_OPENMP45(x, y, z)                                                  \
  (x + xdim5_calc_dt_kernel * (y) +                                            \
   xdim5_calc_dt_kernel * ydim5_calc_dt_kernel * (z))
#define OPS_OPENMP46(x, y, z)                                                  \
  (x + xdim6_calc_dt_kernel * (y) +                                            \
   xdim6_calc_dt_kernel * ydim6_calc_dt_kernel * (z))
#define OPS_OPENMP47(x, y, z)                                                  \
  (x + xdim7_calc_dt_kernel * (y) +                                            \
   xdim7_calc_dt_kernel * ydim7_calc_dt_kernel * (z))
#define OPS_OPENMP48(x, y, z)                                                  \
  (x + xdim8_calc_dt_kernel * (y) +                                            \
   xdim8_calc_dt_kernel * ydim8_calc_dt_kernel * (z))
#define OPS_OPENMP49(x, y, z)                                                  \
  (x + xdim9_calc_dt_kernel * (y) +                                            \
   xdim9_calc_dt_kernel * ydim9_calc_dt_kernel * (z))
#define OPS_OPENMP410(x, y, z)                                                 \
  (x + xdim10_calc_dt_kernel * (y) +                                           \
   xdim10_calc_dt_kernel * ydim10_calc_dt_kernel * (z))
#define OPS_OPENMP411(x, y, z)                                                 \
  (x + xdim11_calc_dt_kernel * (y) +                                           \
   xdim11_calc_dt_kernel * ydim11_calc_dt_kernel * (z))
#define OPS_OPENMP412(x, y, z)                                                 \
  (x + xdim12_calc_dt_kernel * (y) +                                           \
   xdim12_calc_dt_kernel * ydim12_calc_dt_kernel * (z))
#define OPS_OPENMP413(x, y, z)                                                 \
  (x + xdim13_calc_dt_kernel * (y) +                                           \
   xdim13_calc_dt_kernel * ydim13_calc_dt_kernel * (z))

// user function

void calc_dt_kernel_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    double *p_a4, int base4, int tot4, double *p_a5, int base5, int tot5,
    double *p_a6, int base6, int tot6, double *p_a7, int base7, int tot7,
    double *p_a8, int base8, int tot8, double *p_a9, int base9, int tot9,
    double *p_a10, int base10, int tot10, double *p_a11, int base11, int tot11,
    double *p_a12, int base12, int tot12, double *p_a13, int base13, int tot13,
    int x_size, int y_size, int z_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(                                             \
    to : p_a0                                                                  \
    [0 : tot0],                                                                \
     p_a1[0 : tot1],                                                           \
          p_a2[0 : tot2],                                                      \
               p_a3[0 : tot3],                                                 \
                    p_a4[0 : tot4],                                            \
                         p_a5[0 : tot5],                                       \
                              p_a6[0 : tot6],                                  \
                                   p_a7[0 : tot7],                             \
                                        p_a8[0 : tot8],                        \
                                             p_a9[0 : tot9],                   \
                                                  p_a10[0 : tot10], p_a11      \
                                                        [0 : tot11], p_a12     \
                                                         [0 : tot12],          \
                                                          p_a13[0 : tot13])
#ifdef OPS_GPU

#pragma omp target map(                                                        \
    to : p_a0                                                                  \
    [0 : tot0],                                                                \
     p_a1[0 : tot1],                                                           \
          p_a2[0 : tot2],                                                      \
               p_a3[0 : tot3],                                                 \
                    p_a4[0 : tot4],                                            \
                         p_a5[0 : tot5],                                       \
                              p_a6[0 : tot6],                                  \
                                   p_a7[0 : tot7],                             \
                                        p_a8[0 : tot8],                        \
                                             p_a9[0 : tot9],                   \
                                                  p_a10[0 : tot10], p_a11      \
                                                        [0 : tot11], p_a12     \
                                                         [0 : tot12],          \
                                                          p_a13[0 : tot13])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        const double *celldx =
            p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_calc_dt_kernel * 0 * 1 +
            n_z * xdim0_calc_dt_kernel * ydim0_calc_dt_kernel * 0;

        const double *celldy =
            p_a1 + base1 + n_x * 0 * 1 + n_y * xdim1_calc_dt_kernel * 1 * 1 +
            n_z * xdim1_calc_dt_kernel * ydim1_calc_dt_kernel * 0;

        const double *soundspeed =
            p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_calc_dt_kernel * 1 * 1 +
            n_z * xdim2_calc_dt_kernel * ydim2_calc_dt_kernel * 1;

        const double *viscosity =
            p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_calc_dt_kernel * 1 * 1 +
            n_z * xdim3_calc_dt_kernel * ydim3_calc_dt_kernel * 1;

        const double *density0 =
            p_a4 + base4 + n_x * 1 * 1 + n_y * xdim4_calc_dt_kernel * 1 * 1 +
            n_z * xdim4_calc_dt_kernel * ydim4_calc_dt_kernel * 1;

        const double *xvel0 =
            p_a5 + base5 + n_x * 1 * 1 + n_y * xdim5_calc_dt_kernel * 1 * 1 +
            n_z * xdim5_calc_dt_kernel * ydim5_calc_dt_kernel * 1;

        const double *xarea =
            p_a6 + base6 + n_x * 1 * 1 + n_y * xdim6_calc_dt_kernel * 1 * 1 +
            n_z * xdim6_calc_dt_kernel * ydim6_calc_dt_kernel * 1;

        const double *volume =
            p_a7 + base7 + n_x * 1 * 1 + n_y * xdim7_calc_dt_kernel * 1 * 1 +
            n_z * xdim7_calc_dt_kernel * ydim7_calc_dt_kernel * 1;

        const double *yvel0 =
            p_a8 + base8 + n_x * 1 * 1 + n_y * xdim8_calc_dt_kernel * 1 * 1 +
            n_z * xdim8_calc_dt_kernel * ydim8_calc_dt_kernel * 1;

        const double *yarea =
            p_a9 + base9 + n_x * 1 * 1 + n_y * xdim9_calc_dt_kernel * 1 * 1 +
            n_z * xdim9_calc_dt_kernel * ydim9_calc_dt_kernel * 1;

        double *dt_min =
            p_a10 + base10 + n_x * 1 * 1 + n_y * xdim10_calc_dt_kernel * 1 * 1 +
            n_z * xdim10_calc_dt_kernel * ydim10_calc_dt_kernel * 1;

        const double *celldz =
            p_a11 + base11 + n_x * 0 * 1 + n_y * xdim11_calc_dt_kernel * 0 * 1 +
            n_z * xdim11_calc_dt_kernel * ydim11_calc_dt_kernel * 1;

        const double *zvel0 =
            p_a12 + base12 + n_x * 1 * 1 + n_y * xdim12_calc_dt_kernel * 1 * 1 +
            n_z * xdim12_calc_dt_kernel * ydim12_calc_dt_kernel * 1;

        const double *zarea =
            p_a13 + base13 + n_x * 1 * 1 + n_y * xdim13_calc_dt_kernel * 1 * 1 +
            n_z * xdim13_calc_dt_kernel * ydim13_calc_dt_kernel * 1;

        double div, ds, dtut, dtvt, dtct, dtwt, dtdivt, cc, dv1, dv2, du1, du2,
            dw1, dw2;

        ds = MIN(MIN(celldx[OPS_ACC0(0, 0, 0)], celldy[OPS_ACC1(0, 0, 0)]),
                 celldz[OPS_ACC11(0, 0, 0)]);
        ds = 1.0 / (ds * ds);

        cc = soundspeed[OPS_ACC2(0, 0, 0)] * soundspeed[OPS_ACC2(0, 0, 0)];
        cc = cc +
             2.0 * viscosity[OPS_ACC3(0, 0, 0)] / density0[OPS_ACC4(0, 0, 0)];

        dtct = ds * cc;
        dtct = dtc_safe * 1.0 / MAX(sqrt(dtct), g_small);

        du1 = (xvel0[OPS_ACC5(0, 0, 0)] + xvel0[OPS_ACC5(0, 1, 0)] +
               xvel0[OPS_ACC5(0, 0, 1)] + xvel0[OPS_ACC5(0, 1, 1)]) *
              xarea[OPS_ACC6(0, 0, 0)];
        du2 = (xvel0[OPS_ACC5(1, 0, 0)] + xvel0[OPS_ACC5(1, 1, 0)] +
               xvel0[OPS_ACC5(1, 0, 1)] + xvel0[OPS_ACC5(1, 1, 1)]) *
              xarea[OPS_ACC6(0, 0, 0)];

        dtut =
            dtu_safe * 4.0 * volume[OPS_ACC7(0, 0, 0)] /
            MAX(MAX(fabs(du1), fabs(du2)), 1.0e-5 * volume[OPS_ACC7(0, 0, 0)]);

        dv1 = (yvel0[OPS_ACC8(0, 0, 0)] + yvel0[OPS_ACC8(1, 0, 0)] +
               yvel0[OPS_ACC8(0, 0, 1)] + yvel0[OPS_ACC8(1, 0, 1)]) *
              yarea[OPS_ACC9(0, 0, 0)];
        dv2 = (yvel0[OPS_ACC8(0, 1, 0)] + yvel0[OPS_ACC8(1, 1, 0)] +
               yvel0[OPS_ACC8(0, 1, 1)] + yvel0[OPS_ACC8(1, 1, 1)]) *
              yarea[OPS_ACC9(0, 0, 0)];

        dtvt =
            dtv_safe * 4.0 * volume[OPS_ACC7(0, 0, 0)] /
            MAX(MAX(fabs(dv1), fabs(dv2)), 1.0e-5 * volume[OPS_ACC7(0, 0, 0)]);

        dw1 = (zvel0[OPS_ACC12(0, 0, 0)] + zvel0[OPS_ACC12(0, 1, 0)] +
               zvel0[OPS_ACC12(1, 0, 0)] + zvel0[OPS_ACC12(1, 1, 0)]) *
              zarea[OPS_ACC13(0, 0, 0)];
        dw2 = (zvel0[OPS_ACC12(0, 0, 1)] + zvel0[OPS_ACC12(0, 1, 1)] +
               zvel0[OPS_ACC12(1, 0, 1)] + zvel0[OPS_ACC12(1, 1, 1)]) *
              zarea[OPS_ACC13(0, 0, 0)];

        dtwt =
            dtw_safe * 4.0 * volume[OPS_ACC7(0, 0, 0)] /
            MAX(MAX(fabs(dw1), fabs(dw2)), 1.0e-5 * volume[OPS_ACC7(0, 0, 0)]);

        div = du2 - du1 + dv2 - dv1 + dw2 - dw1;
        dtdivt = dtdiv_safe * 4.0 * (volume[OPS_ACC7(0, 0, 0)]) /
                 MAX(volume[OPS_ACC7(0, 0, 0)] * 1.0e-05, fabs(div));

        dt_min[OPS_ACC10(0, 0, 0)] =
            MIN(MIN(MIN(dtct, dtut), MIN(dtvt, dtdivt)), dtwt);
      }
    }
  }
}
#undef OPS_OPENMP40
#undef OPS_OPENMP41
#undef OPS_OPENMP42
#undef OPS_OPENMP43
#undef OPS_OPENMP44
#undef OPS_OPENMP45
#undef OPS_OPENMP46
#undef OPS_OPENMP47
#undef OPS_OPENMP48
#undef OPS_OPENMP49
#undef OPS_OPENMP410
#undef OPS_OPENMP411
#undef OPS_OPENMP412
#undef OPS_OPENMP413
