//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_common_init_u_u0_kernel;
extern int xdim1_tea_leaf_common_init_u_u0_kernel;
extern int xdim2_tea_leaf_common_init_u_u0_kernel;
extern int xdim3_tea_leaf_common_init_u_u0_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_tea_leaf_common_init_u_u0_kernel * (y))

// user function

void tea_leaf_common_init_u_u0_kernel_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(                                             \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2], p_a3[0 : tot3])
#ifdef OPS_GPU

#pragma omp target map(                                                        \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2], p_a3[0 : tot3])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(2) schedule(static, 1)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *u = p_a0 + base0 + n_x * 1 * 1 +
                  n_y * xdim0_tea_leaf_common_init_u_u0_kernel * 1 * 1;

      double *u0 = p_a1 + base1 + n_x * 1 * 1 +
                   n_y * xdim1_tea_leaf_common_init_u_u0_kernel * 1 * 1;
      const double *energy =
          p_a2 + base2 + n_x * 1 * 1 +
          n_y * xdim2_tea_leaf_common_init_u_u0_kernel * 1 * 1;

      const double *density =
          p_a3 + base3 + n_x * 1 * 1 +
          n_y * xdim3_tea_leaf_common_init_u_u0_kernel * 1 * 1;

      u[OPS_ACC0(0, 0)] = energy[OPS_ACC2(0, 0)] * density[OPS_ACC3(0, 0)];
      u0[OPS_ACC1(0, 0)] = energy[OPS_ACC2(0, 0)] * density[OPS_ACC3(0, 0)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
