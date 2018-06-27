//
// auto-generated by ops.py
//
__constant__ int xdim0_multidim_reduce_kernel;
int xdim0_multidim_reduce_kernel_h = -1;
__constant__ int ydim0_multidim_reduce_kernel;
int ydim0_multidim_reduce_kernel_h = -1;

#undef OPS_ACC_MD0

#define OPS_ACC_MD0(d, x, y)                                                   \
  ((x) + (xdim0_multidim_reduce_kernel * (y)) +                                \
   (d)*xdim0_multidim_reduce_kernel * ydim0_multidim_reduce_kernel)
// user function
__device__

    void
    multidim_reduce_kernel_gpu(const double *val, double *redu_dat1) {

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0, 0, 0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1, 0, 0)];
}

#undef OPS_ACC_MD0

__global__ void ops_multidim_reduce_kernel(const double *__restrict arg0,
                                           double *__restrict arg1, int size0,
                                           int size1) {

  double arg1_l[2];
  for (int d = 0; d < 2; d++)
    arg1_l[d] = ZERO_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_multidim_reduce_kernel;

  if (idx_x < size0 && idx_y < size1) {
    multidim_reduce_kernel_gpu(arg0, arg1_l);
  }
  for (int d = 0; d < 2; d++)
    ops_reduction_cuda<OPS_INC>(
        &arg1[d + (blockIdx.x + blockIdx.y * gridDim.x) * 2], arg1_l[d]);
}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block,
                                         int dim, int *range, ops_arg arg0,
                                         ops_arg arg1) {
#else
void ops_par_loop_multidim_reduce_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
#endif

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[2] = {arg0, arg1};

#if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args, 2, range, 2))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(2, "multidim_reduce_kernel");
    OPS_kernels[2].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 2; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];

  if (xdim0 != xdim0_multidim_reduce_kernel_h ||
      ydim0 != ydim0_multidim_reduce_kernel_h) {
    cudaMemcpyToSymbol(xdim0_multidim_reduce_kernel, &xdim0, sizeof(int));
    xdim0_multidim_reduce_kernel_h = xdim0;
    cudaMemcpyToSymbol(ydim0_multidim_reduce_kernel, &ydim0, sizeof(int));
    ydim0_multidim_reduce_kernel_h = ydim0;
  }

#ifdef OPS_LAZY
  ops_block block = desc->block;
#endif
#ifdef OPS_MPI
  double *arg1h =
      (double *)(((ops_reduction)args[1].data)->data +
                 ((ops_reduction)args[1].data)->size * block->index);
#else
  double *arg1h = (double *)(((ops_reduction)args[1].data)->data);
#endif

  dim3 grid((x_size - 1) / OPS_block_size_x + 1,
            (y_size - 1) / OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x, OPS_block_size_y, 1);

  int nblocks = ((x_size - 1) / OPS_block_size_x + 1) *
                ((y_size - 1) / OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks * 2 * sizeof(double));
  reduct_size = MAX(reduct_size, sizeof(double) * 2);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d + reduct_bytes;
  for (int b = 0; b < maxblocks; b++)
    for (int d = 0; d < 2; d++)
      ((double *)arg1.data)[d + b * 2] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks * 2 * sizeof(double));

  mvReductArraysToDevice(reduct_bytes);
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);

  char *p_a[2];

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0 +
          dat0 * args[0].dat->size[0] * (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

#ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args, 2, range);
#endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[2].mpi_time += t2 - t1;
  }

  int nshared = 0;
  int nthread = OPS_block_size_x * OPS_block_size_y;

  nshared = MAX(nshared, sizeof(double) * 2);

  nshared = MAX(nshared * nthread, reduct_size * nthread);

  // call kernel wrapper function, passing in pointers to data
  ops_multidim_reduce_kernel<<<grid, tblock, nshared>>>(
      (double *)p_a[0], (double *)arg1.data_d, x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  mvReductArraysToHost(reduct_bytes);
  for (int b = 0; b < maxblocks; b++) {
    for (int d = 0; d < 2; d++) {
      arg1h[d] = arg1h[d] + ((double *)arg1.data)[d + b * 2];
    }
  }
  arg1.data = (char *)arg1h;

  if (OPS_diags > 1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1, &t1);
    OPS_kernels[2].time += t1 - t2;
  }

#ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 2);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[2].mpi_time += t2 - t1;
    OPS_kernels[2].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block,
                                         int dim, int *range, ops_arg arg0,
                                         ops_arg arg1) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 2;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 2;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 2;
  desc->args = (ops_arg *)malloc(2 * sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->function = ops_par_loop_multidim_reduce_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(2, "multidim_reduce_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
