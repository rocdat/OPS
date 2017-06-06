//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_update_halo_kernel2_yvel_plus_4_back;
extern int ydim0_update_halo_kernel2_yvel_plus_4_back;
extern int xdim1_update_halo_kernel2_yvel_plus_4_back;
extern int ydim1_update_halo_kernel2_yvel_plus_4_back;

#undef OPS_OPENMP40
#undef OPS_OPENMP41

#define OPS_OPENMP40(x, y, z)                                                  \
  (x + xdim0_update_halo_kernel2_yvel_plus_4_back * (y) +                      \
   xdim0_update_halo_kernel2_yvel_plus_4_back *                                \
       ydim0_update_halo_kernel2_yvel_plus_4_back * (z))
#define OPS_OPENMP41(x, y, z)                                                  \
  (x + xdim1_update_halo_kernel2_yvel_plus_4_back * (y) +                      \
   xdim1_update_halo_kernel2_yvel_plus_4_back *                                \
       ydim1_update_halo_kernel2_yvel_plus_4_back * (z))

// user function

void update_halo_kernel2_yvel_plus_4_back_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    int *p_a2, int tot2, int x_size, int y_size, int z_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(to : p_a0[0 : tot0], p_a1[0 : tot1],         \
                                                            p_a2[0 : tot2])
#ifdef OPS_GPU

#pragma omp target map(to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2])
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
        double *yvel0 =
            p_a0 + base0 + n_x * 1 * 1 +
            n_y * xdim0_update_halo_kernel2_yvel_plus_4_back * 1 * 1 +
            n_z * xdim0_update_halo_kernel2_yvel_plus_4_back *
                ydim0_update_halo_kernel2_yvel_plus_4_back * 1;

        double *yvel1 =
            p_a1 + base1 + n_x * 1 * 1 +
            n_y * xdim1_update_halo_kernel2_yvel_plus_4_back * 1 * 1 +
            n_z * xdim1_update_halo_kernel2_yvel_plus_4_back *
                ydim1_update_halo_kernel2_yvel_plus_4_back * 1;

        const int *fields = p_a2;

        if (fields[FIELD_YVEL0] == 1)
          yvel0[OPS_ACC0(0, 0, 0)] = yvel0[OPS_ACC0(0, 0, 4)];
        if (fields[FIELD_YVEL1] == 1)
          yvel1[OPS_ACC1(0, 0, 0)] = yvel1[OPS_ACC1(0, 0, 4)];
      }
    }
  }
}
#undef OPS_OPENMP40
#undef OPS_OPENMP41
