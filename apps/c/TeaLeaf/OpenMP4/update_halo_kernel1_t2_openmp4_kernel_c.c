//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_update_halo_kernel1_t2;
extern int xdim1_update_halo_kernel1_t2;
extern int xdim2_update_halo_kernel1_t2;
extern int xdim3_update_halo_kernel1_t2;
extern int xdim4_update_halo_kernel1_t2;
extern int xdim5_update_halo_kernel1_t2;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5

#define OPS_ACC0(x, y) (x + xdim0_update_halo_kernel1_t2 * (y))
#define OPS_ACC1(x, y) (x + xdim1_update_halo_kernel1_t2 * (y))
#define OPS_ACC2(x, y) (x + xdim2_update_halo_kernel1_t2 * (y))
#define OPS_ACC3(x, y) (x + xdim3_update_halo_kernel1_t2 * (y))
#define OPS_ACC4(x, y) (x + xdim4_update_halo_kernel1_t2 * (y))
#define OPS_ACC5(x, y) (x + xdim5_update_halo_kernel1_t2 * (y))

// user function

void update_halo_kernel1_t2_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    double *p_a4, int base4, int tot4, double *p_a5, int base5, int tot5,
    int *p_a6, int tot6, int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(                                             \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2],                       \
                                              p_a3[0 : tot3],                  \
                                                   p_a4[0 : tot4],             \
                                                        p_a5[0 : tot5],        \
                                                             p_a6[0 : tot6])
#ifdef OPS_GPU

#pragma omp target map(                                                        \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2],                       \
                                              p_a3[0 : tot3],                  \
                                                   p_a4[0 : tot4],             \
                                                        p_a5[0 : tot5],        \
                                                             p_a6[0 : tot6])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(2) schedule(static, 1)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *density0 = p_a0 + base0 + n_x * 1 * 1 +
                         n_y * xdim0_update_halo_kernel1_t2 * 1 * 1;

      double *energy0 = p_a1 + base1 + n_x * 1 * 1 +
                        n_y * xdim1_update_halo_kernel1_t2 * 1 * 1;
      double *energy1 = p_a2 + base2 + n_x * 1 * 1 +
                        n_y * xdim2_update_halo_kernel1_t2 * 1 * 1;

      double *u = p_a3 + base3 + n_x * 1 * 1 +
                  n_y * xdim3_update_halo_kernel1_t2 * 1 * 1;
      double *p = p_a4 + base4 + n_x * 1 * 1 +
                  n_y * xdim4_update_halo_kernel1_t2 * 1 * 1;

      double *sd = p_a5 + base5 + n_x * 1 * 1 +
                   n_y * xdim5_update_halo_kernel1_t2 * 1 * 1;
      const int *fields = p_a6;

      if (fields[FIELD_DENSITY] == 1)
        density0[OPS_ACC0(0, 0)] = density0[OPS_ACC0(0, -3)];
      if (fields[FIELD_ENERGY0] == 1)
        energy0[OPS_ACC1(0, 0)] = energy0[OPS_ACC1(0, -3)];
      if (fields[FIELD_ENERGY1] == 1)
        energy1[OPS_ACC2(0, 0)] = energy1[OPS_ACC2(0, -3)];
      if (fields[FIELD_U] == 1)
        u[OPS_ACC3(0, 0)] = u[OPS_ACC3(0, -3)];
      if (fields[FIELD_P] == 1)
        p[OPS_ACC4(0, 0)] = p[OPS_ACC4(0, -3)];
      if (fields[FIELD_SD] == 1)
        sd[OPS_ACC5(0, 0)] = sd[OPS_ACC5(0, -3)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
