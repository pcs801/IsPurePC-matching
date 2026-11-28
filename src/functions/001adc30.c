// FUNCTION: SLPM 0x001ADC30  size 64  core 64
extern void FUN_001b4650(int a0);
extern int FUN_001b4828(int a0);
extern void FUN_001b4768(int a0);

int FUN_001adc30(char *p, int a1, int a2, int a3, int t0)
{
    *(int *)(p + 44) = a3;
    *(int *)(p + 48) = a2;
    *(int *)(p + 12) = t0;
    *(int *)(p + 16) = 0;
    FUN_001b4650(*(int *)(p + 4));
    if (FUN_001b4828(*(int *)(p + 4)) == 4) {
        FUN_001b4768(*(int *)(p + 4));
        return -1;
    }
    return 0;
}
