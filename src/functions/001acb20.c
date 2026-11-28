// FUNCTION: SLPM 0x001ACB20  size 80  core 76  (4-arg skeleton)
extern void FUN_001af7d0(char *, int, int, int);
extern int FUN_001acb88(char *, int, int, int);
extern void FUN_001af7e8(void);

int FUN_001acb20(char *a0, int a1, int a2, int a3)
{
    int r;

    FUN_001af7d0(a0, a1, a2, a3);
    r = FUN_001acb88(a0, a1, a2, a3);
    FUN_001af7e8();
    return r;
}
