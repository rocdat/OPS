//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_update_halo_kernel3_minus_4_b;
extern int ydim0_update_halo_kernel3_minus_4_b;
extern int xdim1_update_halo_kernel3_minus_4_b;
extern int ydim1_update_halo_kernel3_minus_4_b;

#undef OPS_OPENMP40
#undef OPS_OPENMP41

#define OPS_OPENMP40(x, y, z)                                                  \
  (x + xdim0_update_halo_kernel3_minus_4_b * (y) +                             \
   xdim0_update_halo_kernel3_minus_4_b * ydim0_update_halo_kernel3_minus_4_b * \
       (z))
#define OPS_OPENMP41(x, y, z)                                                  \
  (x + xdim1_update_halo_kernel3_minus_4_b * (y) +                             \
   xdim1_update_halo_kernel3_minus_4_b * ydim1_update_halo_kernel3_minus_4_b * \
       (z))

// user function

void update_halo_kernel3_minus_4_b_c_wrapper(double *p_a0, int base0, int tot0,
                                             double *p_a1, int base1, int tot1,
                                             int *p_a2, int tot2, int x_size,
                                             int y_size, int z_size) {
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
        double *vol_flux_x = p_a0 + base0 + n_x * 1 * 1 +
                             n_y * xdim0_update_halo_kernel3_minus_4_b * 1 * 1 +
                             n_z * xdim0_update_halo_kernel3_minus_4_b *
                                 ydim0_update_halo_kernel3_minus_4_b * 1;

        double *mass_flux_x =
            p_a1 + base1 + n_x * 1 * 1 +
            n_y * xdim1_update_halo_kernel3_minus_4_b * 1 * 1 +
            n_z * xdim1_update_halo_kernel3_minus_4_b *
                ydim1_update_halo_kernel3_minus_4_b * 1;

        const int *fields = p_a2;

        if (fields[FIELD_VOL_FLUX_X] == 1)
          vol_flux_x[OPS_ACC0(0, 0, 0)] = -(vol_flux_x[OPS_ACC0(-4, 0, 0)]);
        if (fields[FIELD_MASS_FLUX_X] == 1)
          mass_flux_x[OPS_ACC1(0, 0, 0)] = -(mass_flux_x[OPS_ACC1(-4, 0, 0)]);
      }
    }
  }
}
#undef OPS_OPENMP40
#undef OPS_OPENMP41
