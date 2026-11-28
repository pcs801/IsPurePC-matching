// FUNCTION: SLPM 0x00117E18  size 272  core 272
extern char D_0026FFD0[];
extern void FUN_001fc2a8(void *a0, void *a1, int a2, void *a3);
extern void FUN_001a9588(void *buf);

void FUN_00117e18(char *p)
{
    char buf[256];
    int *q = *(int **)(p + 68);

    FUN_001fc2a8(buf, D_0026FFD0, q[1], p + 20);
    FUN_001a9588(buf);
}
