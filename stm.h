/* =============================================================================
 *
 * stm.h
 *
 * User program interface for STM. For an STM to interface with STAMP, it needs
 * to have its own stm.h for which it redefines the macros appropriately.
 *
 * =============================================================================
 *
 * Author: Chi Cao Minh
 *
 * =============================================================================
 */


#ifndef STM_H
#define STM_H 1


#include "tl2.h"
#include "util.h"


#define STM_RETRYING_DECL               int Tx_retries
#define STM_RETRYING_VAR                Tx_retries
#define STM_THREAD_T                    Thread
#define STM_SELF                        Self
#define STM_RO_FLAG                     ROFlag

#define STM_MALLOC(size)                TxAlloc(STM_SELF, size)
#define STM_FREE(ptr)                   TxFree(STM_SELF, ptr)


#define malloc(size)                  tmalloc_reserve(size)
#define calloc(n, size)               tmalloc_reserve_z(n, size)

#define realloc(ptr, size)            tmalloc_reserveAgain(ptr, size)
#define free(ptr)                     tmalloc_release(ptr)


#  include <setjmp.h>
#  define STM_JMPBUF_T                  sigjmp_buf
#  define STM_JMPBUF                    buf


#define STM_VALID()                     (1)
#define STM_RESTART()                   TxAbort(STM_SELF)

#define STM_STARTUP(...)                   TxOnce()
#define STM_SHUTDOWN()                  TxShutdown()

#define STM_NEW_THREAD()                TxNewThread()
#define STM_INIT_THREAD(t, id)          TxInitThread(t, id)
#define STM_FREE_THREAD(t)              TxFreeThread(t)






#  define STM_BEGIN_PERS()              STM_RETRYING_DECL; \
                                        do { \
                                            STM_JMPBUF_T STM_JMPBUF; \
                                            int STM_RO_FLAG = 0; \
                                            STM_RETRYING_VAR = sigsetjmp(STM_JMPBUF, 1); \
                                            TxStart(STM_SELF, &STM_JMPBUF, &STM_RO_FLAG); \
                                        } while (0) /* enforce comma */

#  define STM_BEGIN(isReadOnly)         do { \
                                            STM_JMPBUF_T STM_JMPBUF; \
                                            int STM_RO_FLAG = isReadOnly; \
                                            sigsetjmp(STM_JMPBUF, 1); \
                                            TxStart(STM_SELF, &STM_JMPBUF, &STM_RO_FLAG); \
                                        } while (0) /* enforce comma */

#define STM_BEGIN_RD()                  STM_BEGIN(1)
#define STM_BEGIN_WR()                  STM_BEGIN(0)
#define STM_END()                       TxCommit(STM_SELF)

typedef volatile intptr_t               vintp;

#define STM_READ(var, offset)                   TxLoad(STM_SELF, (vintp*)(void*)&(var), sizeof(var))
#define STM_READ_F(var, offset)                 IP2F(TxLoad(STM_SELF, \
                                                    (vintp*)FP2IPP(&(var)), \
                                                    sizeof(var)))
#define STM_READ_P(var, offset)                 IP2VP(TxLoad(STM_SELF, \
                                                     (vintp*)(void*)&(var), \
                                                     sizeof(uint64_t)))

#define STM_WRITE(var, val, offset)             TxStore(STM_SELF, \
                                                (vintp*)(void*)&(var), \
                                                (uint64_t)(val), \
                                                sizeof(var))
#define STM_WRITE_F(var, val, offset)           TxStore(STM_SELF, \
                                                (vintp*)FP2IPP(&(var)), \
                                                F2IP(val), \
                                                sizeof(var))
#define STM_WRITE_P(var, val, offset)           TxStore(STM_SELF, \
                                                (vintp*)(void*)&(var), \
                                                VP2IP(val), \
                                                sizeof(uint64_t))

#define STM_LOCAL_WRITE(var, val)       ({var = val; var;})
#define STM_LOCAL_WRITE_F(var, val)     ({var = val; var;})
#define STM_LOCAL_WRITE_P(var, val)     ({var = val; var;})


#endif /* STM_H */


/* =============================================================================
 *
 * End of stm.h
 *
 * =============================================================================
 */
