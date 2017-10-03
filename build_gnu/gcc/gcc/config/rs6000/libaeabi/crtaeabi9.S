#include "ppc-asm.h"

	.file	"sim-crt9.S"

#if defined (__powerpc64__)
	.section ".init","ax"
	bl	FUNC_NAME(main)
	nop
	/* return value from main is argument to exit */
	bl	FUNC_NAME(exit)
	nop
#endif
