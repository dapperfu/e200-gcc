/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-*spe* } { "*" } { "" } } */
/* { dg-options "-O3 -fbypass-load-on-store -fdump-rtl-sched1 -fdump-rtl-sched2 -fsched-verbose=2" } */

void nescaf(void)
{

	extern long a, b, c, d, e, f;
	volatile long z, w;

	a = 41; b = 79; c = 20; d = 11; e = 12; f = 100;

	/* Now, we have a store followed by a load. The assignments to a-t are
	 * all independent of the store-load computation below. The question is:
	 * Under -fschedule-insns -fbypass-load-on-store, are 14 of the above
	 * instructions moved between the store-load?
	 */
	z = 121;
	w = z;
}

/* Note: There is going to be exactly one insn that will be assigned cost 15.
 *       Since its insn-number will likely change, we do not include the insn
 *       number in the scan - just the part of the dump that'll be invariant.
 */
/* { dg-final { scan-rtl-dump "into queue with cost=15" "sched1" { target powerpc*-*-* } } } */
/* { dg-final { cleanup-rtl-dump "sched*" } } */
