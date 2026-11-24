#include <features.h>

/* These functions will not work, but suffice for targets where the
 * kernel sigaction structure does not actually use sa_restorer. */

hidden void __restore()
{
#ifdef MIVINCI_NATIVE
	__builtin_trap();
#endif
}

hidden void __restore_rt()
{
#ifdef MIVINCI_NATIVE
	__builtin_trap();
#endif
}
