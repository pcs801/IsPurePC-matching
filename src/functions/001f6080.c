// FUNCTION: SLPM 0x001F6080  size 56  core 52
extern char D_00255E74[];
extern void FUN_001f63c8(void *a0, int a1, int a2, int a3, int a4);

void FUN_001f6080(void *a0, int a1)
{
    *(int *)D_00255E74 = 1;
    do {
        FUN_001f63c8(a0, 0, 0, 1, a1);
    } while (0);
}
