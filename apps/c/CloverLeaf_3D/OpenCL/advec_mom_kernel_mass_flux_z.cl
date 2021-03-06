//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#include "ops_opencl_reduction.h"
#include "user_types.h"

#ifndef MIN
#define MIN(a, b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a > b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a, b) ((b < 0.0) ? (a * (-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_advec_mom_kernel_mass_flux_z * (y) +                              \
   xdim0_advec_mom_kernel_mass_flux_z * ydim0_advec_mom_kernel_mass_flux_z *   \
       (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_advec_mom_kernel_mass_flux_z * (y) +                              \
   xdim1_advec_mom_kernel_mass_flux_z * ydim1_advec_mom_kernel_mass_flux_z *   \
       (z))

// user function
inline void
advec_mom_kernel_mass_flux_z(__global double *restrict node_flux,
                             const __global double *restrict mass_flux_z)

{

  node_flux[OPS_ACC0(0, 0, 0)] =
      0.125 *
      (mass_flux_z[OPS_ACC1(-1, 0, 0)] + mass_flux_z[OPS_ACC1(0, 0, 0)] +
       mass_flux_z[OPS_ACC1(-1, 0, 1)] + mass_flux_z[OPS_ACC1(0, 0, 1)] +
       mass_flux_z[OPS_ACC1(-1, -1, 0)] + mass_flux_z[OPS_ACC1(0, -1, 0)] +
       mass_flux_z[OPS_ACC1(-1, -1, 1)] + mass_flux_z[OPS_ACC1(0, -1, 1)]);
}

__kernel void ops_advec_mom_kernel_mass_flux_z(
    __global double *restrict arg0, __global const double *restrict arg1,
    const int base0, const int base1, const int size0, const int size1,
    const int size2) {

  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    advec_mom_kernel_mass_flux_z(
        &arg0[base0 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim0_advec_mom_kernel_mass_flux_z +
              idx_z * 1 * 1 * xdim0_advec_mom_kernel_mass_flux_z *
                  ydim0_advec_mom_kernel_mass_flux_z],
        &arg1[base1 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim1_advec_mom_kernel_mass_flux_z +
              idx_z * 1 * 1 * xdim1_advec_mom_kernel_mass_flux_z *
                  ydim1_advec_mom_kernel_mass_flux_z]);
  }
}
