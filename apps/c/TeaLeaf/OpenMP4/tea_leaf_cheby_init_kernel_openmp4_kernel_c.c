//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_cheby_init_kernel;
extern int xdim1_tea_leaf_cheby_init_kernel;
extern int xdim2_tea_leaf_cheby_init_kernel;
extern int xdim3_tea_leaf_cheby_init_kernel;
extern int xdim4_tea_leaf_cheby_init_kernel;
extern int xdim5_tea_leaf_cheby_init_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_cheby_init_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_tea_leaf_cheby_init_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_tea_leaf_cheby_init_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_tea_leaf_cheby_init_kernel * (y))
#define OPS_ACC4(x, y) (x + xdim4_tea_leaf_cheby_init_kernel * (y))
#define OPS_ACC5(x, y) (x + xdim5_tea_leaf_cheby_init_kernel * (y))

// user function

void tea_leaf_cheby_init_kernel_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    double *p_a4, int base4, int tot4, double *p_a5, int base5, int tot5,
    double p_a6, double p_a7, int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(                                             \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2],                       \
                                              p_a3[0 : tot3],                  \
                                                   p_a4[0 : tot4],             \
                                                        p_a5[0 : tot5])
#ifdef OPS_GPU

#pragma omp target map(                                                        \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2],                       \
                                              p_a3[0 : tot3],                  \
                                                   p_a4[0 : tot4],             \
                                                        p_a5[0 : tot5])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(2) schedule(static, 1)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *w = p_a0 + base0 + n_x * 1 * 1 +
                  n_y * xdim0_tea_leaf_cheby_init_kernel * 1 * 1;

      double *r = p_a1 + base1 + n_x * 1 * 1 +
                  n_y * xdim1_tea_leaf_cheby_init_kernel * 1 * 1;
      const double *Kx = p_a2 + base2 + n_x * 1 * 1 +
                         n_y * xdim2_tea_leaf_cheby_init_kernel * 1 * 1;

      const double *Ky = p_a3 + base3 + n_x * 1 * 1 +
                         n_y * xdim3_tea_leaf_cheby_init_kernel * 1 * 1;
      const double *u = p_a4 + base4 + n_x * 1 * 1 +
                        n_y * xdim4_tea_leaf_cheby_init_kernel * 1 * 1;

      const double *u0 = p_a5 + base5 + n_x * 1 * 1 +
                         n_y * xdim5_tea_leaf_cheby_init_kernel * 1 * 1;
      const double *rx = &p_a6;

      const double *ry = &p_a7;

      w[OPS_ACC0(0, 0)] =
          (1.0 + (*ry) * (Ky[OPS_ACC3(0, 1)] + Ky[OPS_ACC3(0, 0)]) +
           (*rx) * (Kx[OPS_ACC2(1, 0)] + Kx[OPS_ACC2(0, 0)])) *
              u[OPS_ACC4(0, 0)] -
          (*ry) * (Ky[OPS_ACC3(0, 1)] * u[OPS_ACC4(0, 1)] +
                   Ky[OPS_ACC3(0, 0)] * u[OPS_ACC4(0, -1)]) -
          (*rx) * (Kx[OPS_ACC2(1, 0)] * u[OPS_ACC4(1, 0)] +
                   Kx[OPS_ACC2(0, 0)] * u[OPS_ACC4(-1, 0)]);
      r[OPS_ACC1(0, 0)] = u0[OPS_ACC5(0, 0)] - w[OPS_ACC0(0, 0)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
