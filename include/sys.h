#ifndef LIBSYSY_SYS_H_
#define LIBSYSY_SYS_H_




#define __riscv_xlen 64
#if __riscv_xlen == 32
#define SYS_32
#elif __risv_xlen == 64
#define SYS_64
#endif



#define SYS_READ 63
#define SYS_WRITE 64
#define SYS_EXIT 93
#define SYS_GETTIMEOFDAY 169

#define SYSCALL1(number, arg0)                                         \
  ({                                                                   \
    long int _sys_result;                                              \
    long int _arg0 = (long int)(arg0);                                 \
    register long int __a7 asm("a7") = number;                         \
    register long int __a0 asm("a0") = _arg0;                          \
    __asm__ volatile("ecall\n\t" : "+r"(__a0) : "r"(__a7) : "memory"); \
    _sys_result = __a0;                                                \
    _sys_result;                                                       \
  })
#define SYSCALL2(number, arg0, arg1)           \
  ({                                           \
    long int _sys_result;                      \
    long int _arg0 = (long int)(arg0);         \
    long int _arg1 = (long int)(arg1);         \
    register long int __a7 asm("a7") = number; \
    register long int __a0 asm("a0") = _arg0;  \
    register long int __a1 asm("a1") = _arg1;  \
    __asm__ volatile("ecall\n\t"               \
                     : "+r"(__a0)              \
                     : "r"(__a7), "r"(__a1)    \
                     : "memory");              \
    _sys_result = __a0;                        \
    _sys_result;                               \
  })
#define SYSCALL3(number, arg0, arg1, arg2)             \
  ({                                                   \
    long int _sys_result;                              \
    long int _arg0 = (long int)(arg0);                 \
    long int _arg1 = (long int)(arg1);                 \
    long int _arg2 = (long int)(arg2);                 \
    register long int __a7 asm("a7") = number;         \
    register long int __a0 asm("a0") = _arg0;          \
    register long int __a1 asm("a1") = _arg1;          \
    register long int __a2 asm("a2") = _arg2;          \
    __asm__ volatile("ecall\n\t"                       \
                     : "+r"(__a0)                      \
                     : "r"(__a7), "r"(__a1), "r"(__a2) \
                     : "memory");                      \
    _sys_result = __a0;                                \
    _sys_result;                                       \
  })

#endif  // LIBSYSY_SYS_H_
