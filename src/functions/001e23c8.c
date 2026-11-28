// FUNCTION: SLPM 0x001E23C8  size 56  core 52
extern void FUN_001e1cd8(void *p, int a1, int a2);

int FUN_001e23c8(int *p, int a1, int a2, int a3)
{
    if (a2 != 1) {
        FUN_001e1cd8(p, a1, a3);
        return 0;
    }
    return (unsigned int)p[4] < (unsigned int)a1;
}
