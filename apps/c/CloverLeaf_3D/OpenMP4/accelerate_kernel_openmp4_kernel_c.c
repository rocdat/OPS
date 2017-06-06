//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_accelerate_kernel;
extern int ydim0_accelerate_kernel;
extern int xdim1_accelerate_kernel;
extern int ydim1_accelerate_kernel;
extern int xdim2_accelerate_kernel;
extern int ydim2_accelerate_kernel;
extern int xdim3_accelerate_kernel;
extern int ydim3_accelerate_kernel;
extern int xdim4_accelerate_kernel;
extern int ydim4_accelerate_kernel;
extern int xdim5_accelerate_kernel;
extern int ydim5_accelerate_kernel;
extern int xdim6_accelerate_kernel;
extern int ydim6_accelerate_kernel;
extern int xdim7_accelerate_kernel;
extern int ydim7_accelerate_kernel;
extern int xdim8_accelerate_kernel;
extern int ydim8_accelerate_kernel;
extern int xdim9_accelerate_kernel;
extern int ydim9_accelerate_kernel;
extern int xdim10_accelerate_kernel;
extern int ydim10_accelerate_kernel;
extern int xdim11_accelerate_kernel;
extern int ydim11_accelerate_kernel;
extern int xdim12_accelerate_kernel;
extern int ydim12_accelerate_kernel;
extern int xdim13_accelerate_kernel;
extern int ydim13_accelerate_kernel;

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
  (x + xdim0_accelerate_kernel * (y) +                                         \
   xdim0_accelerate_kernel * ydim0_accelerate_kernel * (z))
#define OPS_OPENMP41(x, y, z)                                                  \
  (x + xdim1_accelerate_kernel * (y) +                                         \
   xdim1_accelerate_kernel * ydim1_accelerate_kernel * (z))
#define OPS_OPENMP42(x, y, z)                                                  \
  (x + xdim2_accelerate_kernel * (y) +                                         \
   xdim2_accelerate_kernel * ydim2_accelerate_kernel * (z))
#define OPS_OPENMP43(x, y, z)                                                  \
  (x + xdim3_accelerate_kernel * (y) +                                         \
   xdim3_accelerate_kernel * ydim3_accelerate_kernel * (z))
#define OPS_OPENMP44(x, y, z)                                                  \
  (x + xdim4_accelerate_kernel * (y) +                                         \
   xdim4_accelerate_kernel * ydim4_accelerate_kernel * (z))
#define OPS_OPENMP45(x, y, z)                                                  \
  (x + xdim5_accelerate_kernel * (y) +                                         \
   xdim5_accelerate_kernel * ydim5_accelerate_kernel * (z))
#define OPS_OPENMP46(x, y, z)                                                  \
  (x + xdim6_accelerate_kernel * (y) +                                         \
   xdim6_accelerate_kernel * ydim6_accelerate_kernel * (z))
#define OPS_OPENMP47(x, y, z)                                                  \
  (x + xdim7_accelerate_kernel * (y) +                                         \
   xdim7_accelerate_kernel * ydim7_accelerate_kernel * (z))
#define OPS_OPENMP48(x, y, z)                                                  \
  (x + xdim8_accelerate_kernel * (y) +                                         \
   xdim8_accelerate_kernel * ydim8_accelerate_kernel * (z))
#define OPS_OPENMP49(x, y, z)                                                  \
  (x + xdim9_accelerate_kernel * (y) +                                         \
   xdim9_accelerate_kernel * ydim9_accelerate_kernel * (z))
#define OPS_OPENMP410(x, y, z)                                                 \
  (x + xdim10_accelerate_kernel * (y) +                                        \
   xdim10_accelerate_kernel * ydim10_accelerate_kernel * (z))
#define OPS_OPENMP411(x, y, z)                                                 \
  (x + xdim11_accelerate_kernel * (y) +                                        \
   xdim11_accelerate_kernel * ydim11_accelerate_kernel * (z))
#define OPS_OPENMP412(x, y, z)                                                 \
  (x + xdim12_accelerate_kernel * (y) +                                        \
   xdim12_accelerate_kernel * ydim12_accelerate_kernel * (z))
#define OPS_OPENMP413(x, y, z)                                                 \
  (x + xdim13_accelerate_kernel * (y) +                                        \
   xdim13_accelerate_kernel * ydim13_accelerate_kernel * (z))

// user function

void accelerate_kernel_c_wrapper(
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
        const double *density0 =
            p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_accelerate_kernel * 1 * 1 +
            n_z * xdim0_accelerate_kernel * ydim0_accelerate_kernel * 1;

        const double *volume =
            p_a1 + base1 + n_x * 1 * 1 + n_y * xdim1_accelerate_kernel * 1 * 1 +
            n_z * xdim1_accelerate_kernel * ydim1_accelerate_kernel * 1;

        double *stepbymass =
            p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_accelerate_kernel * 1 * 1 +
            n_z * xdim2_accelerate_kernel * ydim2_accelerate_kernel * 1;

        const double *xvel0 =
            p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_accelerate_kernel * 1 * 1 +
            n_z * xdim3_accelerate_kernel * ydim3_accelerate_kernel * 1;

        double *xvel1 =
            p_a4 + base4 + n_x * 1 * 1 + n_y * xdim4_accelerate_kernel * 1 * 1 +
            n_z * xdim4_accelerate_kernel * ydim4_accelerate_kernel * 1;

        const double *xarea =
            p_a5 + base5 + n_x * 1 * 1 + n_y * xdim5_accelerate_kernel * 1 * 1 +
            n_z * xdim5_accelerate_kernel * ydim5_accelerate_kernel * 1;

        const double *pressure =
            p_a6 + base6 + n_x * 1 * 1 + n_y * xdim6_accelerate_kernel * 1 * 1 +
            n_z * xdim6_accelerate_kernel * ydim6_accelerate_kernel * 1;

        const double *yvel0 =
            p_a7 + base7 + n_x * 1 * 1 + n_y * xdim7_accelerate_kernel * 1 * 1 +
            n_z * xdim7_accelerate_kernel * ydim7_accelerate_kernel * 1;

        double *yvel1 =
            p_a8 + base8 + n_x * 1 * 1 + n_y * xdim8_accelerate_kernel * 1 * 1 +
            n_z * xdim8_accelerate_kernel * ydim8_accelerate_kernel * 1;

        const double *yarea =
            p_a9 + base9 + n_x * 1 * 1 + n_y * xdim9_accelerate_kernel * 1 * 1 +
            n_z * xdim9_accelerate_kernel * ydim9_accelerate_kernel * 1;

        const double *viscosity =
            p_a10 + base10 + n_x * 1 * 1 +
            n_y * xdim10_accelerate_kernel * 1 * 1 +
            n_z * xdim10_accelerate_kernel * ydim10_accelerate_kernel * 1;

        const double *zvel0 =
            p_a11 + base11 + n_x * 1 * 1 +
            n_y * xdim11_accelerate_kernel * 1 * 1 +
            n_z * xdim11_accelerate_kernel * ydim11_accelerate_kernel * 1;

        double *zvel1 =
            p_a12 + base12 + n_x * 1 * 1 +
            n_y * xdim12_accelerate_kernel * 1 * 1 +
            n_z * xdim12_accelerate_kernel * ydim12_accelerate_kernel * 1;

        const double *zarea =
            p_a13 + base13 + n_x * 1 * 1 +
            n_y * xdim13_accelerate_kernel * 1 * 1 +
            n_z * xdim13_accelerate_kernel * ydim13_accelerate_kernel * 1;

        double nodal_mass = 0.0;
        nodal_mass =
            (density0[OPS_ACC0(-1, -1, 0)] * volume[OPS_ACC1(-1, -1, 0)] +
             density0[OPS_ACC0(0, -1, 0)] * volume[OPS_ACC1(0, -1, 0)] +
             density0[OPS_ACC0(0, 0, 0)] * volume[OPS_ACC1(0, 0, 0)] +
             density0[OPS_ACC0(-1, 0, 0)] * volume[OPS_ACC1(-1, 0, 0)] +
             density0[OPS_ACC0(-1, -1, -1)] * volume[OPS_ACC1(-1, -1, -1)] +
             density0[OPS_ACC0(0, -1, -1)] * volume[OPS_ACC1(0, -1, -1)] +
             density0[OPS_ACC0(0, 0, -1)] * volume[OPS_ACC1(0, 0, -1)] +
             density0[OPS_ACC0(-1, 0, -1)] * volume[OPS_ACC1(-1, 0, -1)]) *
            0.125;

        stepbymass[OPS_ACC2(0, 0, 0)] = 0.25 * dt / nodal_mass;

        xvel1[OPS_ACC4(0, 0, 0)] =
            xvel0[OPS_ACC3(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (xarea[OPS_ACC5(0, 0, 0)] * (pressure[OPS_ACC6(0, 0, 0)] -
                                             pressure[OPS_ACC6(-1, 0, 0)]) +
                 xarea[OPS_ACC5(0, -1, 0)] * (pressure[OPS_ACC6(0, -1, 0)] -
                                              pressure[OPS_ACC6(-1, -1, 0)]) +
                 xarea[OPS_ACC5(0, 0, -1)] * (pressure[OPS_ACC6(0, 0, -1)] -
                                              pressure[OPS_ACC6(-1, 0, -1)]) +
                 xarea[OPS_ACC5(0, -1, -1)] * (pressure[OPS_ACC6(0, -1, -1)] -
                                               pressure[OPS_ACC6(-1, -1, -1)]));

        yvel1[OPS_ACC8(0, 0, 0)] =
            yvel0[OPS_ACC7(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (yarea[OPS_ACC9(0, 0, 0)] * (pressure[OPS_ACC6(0, 0, 0)] -
                                             pressure[OPS_ACC6(0, -1, 0)]) +
                 yarea[OPS_ACC9(-1, 0, 0)] * (pressure[OPS_ACC6(-1, 0, 0)] -
                                              pressure[OPS_ACC6(-1, -1, 0)]) +
                 yarea[OPS_ACC9(0, 0, -1)] * (pressure[OPS_ACC6(0, 0, -1)] -
                                              pressure[OPS_ACC6(0, -1, -1)]) +
                 yarea[OPS_ACC9(-1, 0, -1)] * (pressure[OPS_ACC6(-1, 0, -1)] -
                                               pressure[OPS_ACC6(-1, -1, -1)]));

        zvel1[OPS_ACC12(0, 0, 0)] =
            zvel0[OPS_ACC11(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (zarea[OPS_ACC13(0, 0, 0)] * (pressure[OPS_ACC6(0, 0, 0)] -
                                              pressure[OPS_ACC6(0, 0, -1)]) +
                 zarea[OPS_ACC13(0, -1, 0)] * (pressure[OPS_ACC6(0, -1, 0)] -
                                               pressure[OPS_ACC6(0, -1, -1)]) +
                 zarea[OPS_ACC13(-1, 0, 0)] * (pressure[OPS_ACC6(-1, 0, 0)] -
                                               pressure[OPS_ACC6(-1, 0, -1)]) +
                 zarea[OPS_ACC13(-1, -1, 0)] *
                     (pressure[OPS_ACC6(-1, -1, 0)] -
                      pressure[OPS_ACC6(-1, -1, -1)]));

        xvel1[OPS_ACC4(0, 0, 0)] =
            xvel1[OPS_ACC4(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (xarea[OPS_ACC5(0, 0, 0)] * (viscosity[OPS_ACC10(0, 0, 0)] -
                                             viscosity[OPS_ACC10(-1, 0, 0)]) +
                 xarea[OPS_ACC5(0, -1, 0)] * (viscosity[OPS_ACC10(0, -1, 0)] -
                                              viscosity[OPS_ACC10(-1, -1, 0)]) +
                 xarea[OPS_ACC5(0, 0, -1)] * (viscosity[OPS_ACC10(0, 0, -1)] -
                                              viscosity[OPS_ACC10(-1, 0, -1)]) +
                 xarea[OPS_ACC5(0, -1, -1)] *
                     (viscosity[OPS_ACC10(0, -1, -1)] -
                      viscosity[OPS_ACC10(-1, -1, -1)]));

        yvel1[OPS_ACC8(0, 0, 0)] =
            yvel1[OPS_ACC8(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (yarea[OPS_ACC9(0, 0, 0)] * (viscosity[OPS_ACC10(0, 0, 0)] -
                                             viscosity[OPS_ACC10(0, -1, 0)]) +
                 yarea[OPS_ACC9(-1, 0, 0)] * (viscosity[OPS_ACC10(-1, 0, 0)] -
                                              viscosity[OPS_ACC10(-1, -1, 0)]) +
                 yarea[OPS_ACC9(0, 0, -1)] * (viscosity[OPS_ACC10(0, 0, -1)] -
                                              viscosity[OPS_ACC10(0, -1, -1)]) +
                 yarea[OPS_ACC9(-1, 0, -1)] *
                     (viscosity[OPS_ACC10(-1, 0, -1)] -
                      viscosity[OPS_ACC10(-1, -1, -1)]));

        zvel1[OPS_ACC12(0, 0, 0)] =
            zvel1[OPS_ACC12(0, 0, 0)] -
            stepbymass[OPS_ACC2(0, 0, 0)] *
                (zarea[OPS_ACC13(0, 0, 0)] * (viscosity[OPS_ACC10(0, 0, 0)] -
                                              viscosity[OPS_ACC10(0, 0, -1)]) +
                 zarea[OPS_ACC13(0, -1, 0)] *
                     (viscosity[OPS_ACC10(0, -1, 0)] -
                      viscosity[OPS_ACC10(0, -1, -1)]) +
                 zarea[OPS_ACC13(-1, 0, 0)] *
                     (viscosity[OPS_ACC10(-1, 0, 0)] -
                      viscosity[OPS_ACC10(-1, 0, -1)]) +
                 zarea[OPS_ACC13(-1, -1, 0)] *
                     (viscosity[OPS_ACC10(-1, -1, 0)] -
                      viscosity[OPS_ACC10(-1, -1, -1)]));
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
