//
// auto-generated by ops.py//

//header
#define OPS_ACC_MD_MACROS
#include "ops_lib_cpp.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

#include "vars.h"

// global constants
//user kernel files
#include "initialize_kernel_seq_kernel.cpp"
#include "save_kernel_seq_kernel.cpp"
#include "zerores_kernel_seq_kernel.cpp"
#include "drhoudx_kernel_seq_kernel.cpp"
#include "drhouupdx_kernel_seq_kernel.cpp"
#include "drhoEpudx_kernel_seq_kernel.cpp"
#include "updateRK3_kernel_seq_kernel.cpp"
#include "Riemann_kernel_seq_kernel.cpp"
#include "limiter_kernel_seq_kernel.cpp"
#include "tvd_kernel_seq_kernel.cpp"
#include "vars_kernel_seq_kernel.cpp"
#include "calupwindeff_kernel_seq_kernel.cpp"
#include "fact_kernel_seq_kernel.cpp"
#include "update_kernel_seq_kernel.cpp"
#include "test_kernel_seq_kernel.cpp"
