//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_zero_y;

#undef OPS_ACC0

#define OPS_ACC0(x, y) (x + xdim0_initialise_chunk_kernel_zero_y * (y))

// user function

void initialise_chunk_kernel_zero_y_c_wrapper(double *p_a0, int base0, int tot0,
                                              int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(to : p_a0[0 : tot0])
#ifdef OPS_GPU

#pragma omp target map(to : p_a0[0 : tot0])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(2) schedule(static, 1)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *var = p_a0 + base0 + n_x * 0 * 1 +
                    n_y * xdim0_initialise_chunk_kernel_zero_y * 1 * 1;

      *var = 0.0;
    }
  }
}
#undef OPS_ACC0
