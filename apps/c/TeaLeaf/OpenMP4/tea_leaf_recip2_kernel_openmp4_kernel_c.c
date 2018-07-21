//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"
#include <omp.h>
#define OPS_GPU

extern int xdim0_tea_leaf_recip2_kernel;
extern int xdim1_tea_leaf_recip2_kernel;
extern int xdim2_tea_leaf_recip2_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim0_tea_leaf_recip2_kernel * 1 * 1 + x +              \
   xdim0_tea_leaf_recip2_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim1_tea_leaf_recip2_kernel * 1 * 1 + x +              \
   xdim1_tea_leaf_recip2_kernel * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim2_tea_leaf_recip2_kernel * 1 * 1 + x +              \
   xdim2_tea_leaf_recip2_kernel * (y))

// user function

void tea_leaf_recip2_kernel_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                      int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    const int id =
        omp_get_num_threads() * omp_get_team_num() + omp_get_thread_num();
    const int n_x = id % x_size;
    const int n_y = id / x_size;
    double *z = p_a0;

    const double *x = p_a1;
    const double *y = p_a2;

    z[OPS_ACC0(0, 0)] = x[OPS_ACC1(0, 0)] / y[OPS_ACC2(0, 0)];
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2