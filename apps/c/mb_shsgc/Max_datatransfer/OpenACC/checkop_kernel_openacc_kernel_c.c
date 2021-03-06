//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

int xdim0_checkop_kernel;
int xdim1_checkop_kernel;
int xdim2_checkop_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)

// user function
inline void checkop_kernel(const double *rho_new, const double *x,
                           const double *rhoin, double *pre, double *post,
                           int *num) {
  double diff;
  diff = (rho_new[OPS_ACC0(0)] - rhoin[OPS_ACC2(0)]);
  if (fabs(diff) < 0.01 && x[OPS_ACC1(0)] > -4.1) {
    *post = *post + diff * diff;
    *num = *num + 1;

  } else
    *pre = *pre + (rho_new[OPS_ACC0(0)] - rhol) * (rho_new[OPS_ACC0(0)] - rhol);
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

void checkop_kernel_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                              double *p_a3, double *p_a4, int *p_a5,
                              int x_size) {
  double p_a3_0 = p_a3[0];
  double p_a4_0 = p_a4[0];
  int p_a5_0 = p_a5[0];
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2) reduction(                    \
    + : p_a3_0) reduction(+ : p_a4_0) reduction(+ : p_a5_0)
#pragma acc loop reduction(+ : p_a3_0) reduction(+ : p_a4_0)                   \
                                                     reduction(+ : p_a5_0)
#endif
  for (int n_x = 0; n_x < x_size; n_x++) {
    checkop_kernel(p_a0 + n_x * 1 * 1, p_a1 + n_x * 1 * 1, p_a2 + n_x * 1 * 1,
                   &p_a3_0, &p_a4_0, &p_a5_0);
  }
  p_a3[0] = p_a3_0;
  p_a4[0] = p_a4_0;
  p_a5[0] = p_a5_0;
}
