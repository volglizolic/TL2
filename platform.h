/* =============================================================================
 *
 * platform.h
 *
 * Platform-specific bindings
 *
 * =============================================================================
 */


#ifndef PLATFORM_H
#define PLATFORM_H 1

#include <stdint.h>
#include "common.h"

#include <stdatomic.h>


/* =============================================================================
 * Compare-and-swap
 *
 * =============================================================================
 */
#define CAS(m,c,s)  __sync_val_compare_and_swap((intptr_t*)m, (intptr_t)c, (intptr_t)s)


/* =============================================================================
 * Memory Barriers
 * =============================================================================
 */
#define MEMBARLDLD()   atomic_thread_fence(memory_order_acquire) /* nothing */
#define MEMBARSTST()   atomic_thread_fence(memory_order_release) /* nothing */
#define MEMBARSTLD()   atomic_thread_fence(memory_order_acq_rel) /*__asm__ __volatile__ ("membar #StoreLoad" : : :"memory")*/


/* =============================================================================
 * Prefetching
 *
 * We use PREFETCHW in LD...CAS and LD...ST circumstances to force the $line
 * directly into M-state, avoiding RTS->RTO upgrade txns.
 * =============================================================================
 */
__INLINE__ void prefetchw (volatile void* x){
    __builtin_prefetch((const void *) x);
}


/* =============================================================================
 * Non-faulting load
 * =============================================================================
 */
__INLINE__ intptr_t
LDNF (volatile intptr_t* a)
{
    return atomic_load_explicit((long*) a, memory_order_seq_cst);
}


/* =============================================================================
 * MP-polite spinning
 * -- Ideally we would like to drop the priority of our CMT strand.
 * =============================================================================
 */
#define PAUSE()  /* nothing */


/* =============================================================================
 * Timer functions
 * =============================================================================
 */

typedef unsigned long long TL2_TIMER_T;


#define TL2_TIMER_READ() ({ \
struct timespec time; \
clock_gettime(CLOCK_MONOTONIC, &time); \
(long)time.tv_sec * 1000000000L + (long)time.tv_nsec; \
})

#endif /* PLATFORM_H */


/* =============================================================================
 *
 * End of platform.h
 *
 * =============================================================================
 */
