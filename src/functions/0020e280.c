// FUNCTION: SLPM 0x0020E280  size 48  core 44
extern int D_02566F0;
extern char D_08705E8[];
extern void FUN_001fbb84(char *, int, int);

int FUN_0020e280(void)
{
    char *p;

    p = D_08705E8;
    D_02566F0 = -1;
    FUN_001fbb84(p, 0, 4);
    return 0;
}
