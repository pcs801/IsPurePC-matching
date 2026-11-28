// FUNCTION: SLPM 0x00161A60  size 80  core 80
extern char D_00217B38[];
extern void FUN_001fc8c0(void *a0, int a1);
extern void FUN_0019daf8(void *a0, void *a1, int a2, int a3);

void FUN_00161a60(char *p, int a1, int a2, int a3, int t0, int t1, int t2)
{
    *(int *)(p + 8) = a1;
    *(int *)(p + 12) = a2;
    *(int *)(p + 540) = t0;
    *(int *)(p + 548) = t1;
    *(int *)(p + 544) = t2;
    FUN_001fc8c0(p + 20, a3);
    FUN_0019daf8(D_00217B38, p, 1024, 2);
}
