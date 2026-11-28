// FUNCTION: SLPM 0x001fbcc8  size 80  core 76
extern int D_0025661C;
extern int D_00256618;
extern int D_00256710;
extern int FUN_002059c0(int a0);

void FUN_001fbcc8(void)
{
    if (--D_0025661C == 0) {
        D_00256618 = -1;
        FUN_002059c0(D_00256710);
    }
}
