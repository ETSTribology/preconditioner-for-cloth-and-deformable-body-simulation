#pragma once

#include <omp.h>

extern int CPU_THREAD_NUM;

#define OMP_BARRIER __pragma(omp barrier)
#define OMP_PARALLEL __pragma(omp parallel num_threads(CPU_THREAD_NUM))
#define OMP_FOR __pragma(omp for)
#define OMP_PARALLEL_FOR __pragma(omp parallel for num_threads(CPU_THREAD_NUM)) 
#define OMP_PARALLEL_FOR_SUM_REDUCTION(sum) __pragma(omp parallel for num_threads(CPU_THREAD_NUM) reduction(+: sum)) 
