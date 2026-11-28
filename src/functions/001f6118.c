// FUNCTION: SLPM 0x001F6118  size 56  core 52
extern char D_00255E74[];
extern char D_0086B998[];
extern void FUN_001f63c8(int a0, int a1, int a2, int a3, void *a4);

void FUN_001f6118(void)
{
    char *p = D_0086B998;

    *(int *)D_00255E74 = 0;
    do {
        FUN_001f63c8(0, 0, 0, 3, p);
    } while (0);
}
