#include "SeOmp.h"

#ifdef WIN32
    int CPU_THREAD_NUM = (omp_get_num_procs() - 1) > 1 ? (omp_get_num_procs() - 1) : 1;
#else
    int CPU_THREAD_NUM =  1;
#endif
