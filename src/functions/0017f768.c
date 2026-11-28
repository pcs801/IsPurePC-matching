// FUNCTION: SLPM 0x0017F768  size 96  core 76
// q = *(int**)(p+0x44); if (FUN_0017f298(p) != 0) return;
// *(int*)b = *(int*)((char*)q + 0x15); b[3] = -0x80 - *(unsigned char*)((char*)q+0xC);
// FUN_001a09a0(D_1B9F880, b, *(int*)((char*)q+4));
extern char D_1B9F880[];
extern int FUN_0017f298(char *);
extern void FUN_001a09a0(char *, char *, int);

void FUN_0017f768(char *p)
{
    int *q;
    char b[4];

    q = *(int **)(p + 0x44);
    if (FUN_0017f298(p) != 0)
        return;
    *(int *)b = *(int *)((char *)q + 0x15);
    b[3] = -0x80 - *(unsigned char *)((char *)q + 0xC);
    FUN_001a09a0(D_1B9F880, b, *(int *)((char *)q + 4));
}
