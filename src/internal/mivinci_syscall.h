#ifndef _INTERNAL_MIVINCI_SYSCALL_H
#define _INTERNAL_MIVINCI_SYSCALL_H

#include <errno.h>

#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)
#define IPC_64 0

/* Linux numbers and argument layouts must never reach the native trap. */
static inline long __syscall0(long n)
{
	(void)n;
	return -ENOSYS;
}

static inline long __syscall1(long n, long a)
{
	(void)a;
	return __syscall0(n);
}

static inline long __syscall2(long n, long a, long b)
{
	(void)b;
	return __syscall1(n, a);
}

static inline long __syscall3(long n, long a, long b, long c)
{
	(void)c;
	return __syscall2(n, a, b);
}

static inline long __syscall4(long n, long a, long b, long c, long d)
{
	(void)d;
	return __syscall3(n, a, b, c);
}

static inline long __syscall5(long n, long a, long b, long c, long d, long e)
{
	(void)e;
	return __syscall4(n, a, b, c, d);
}

static inline long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
	(void)f;
	return __syscall5(n, a, b, c, d, e);
}

#endif
