// FUNCTION: SLPM 0x001619C0  size 72  core 72
extern char D_00217B18[];
extern void FUN_001fc8c0(void *a0, int a1);
extern void FUN_0019daf8(void *a0, void *a1, int a2, int a3);

void FUN_001619c0(char *p, int a1, int a2, int a3, int t0, int t1)
{
    *(int *)(p + 8) = a1;
    *(int *)(p + 12) = a2;
    *(int *)(p + 552) = t0;
    *(int *)(p + 536) = t1;
    FUN_001fc8c0(p + 276, a3);
    FUN_0019daf8(D_00217B18, p, 1024, 2);
}
