// FUNCTION: SLPM 0x001C0340  size 48  core 44
// fp = *(void(**)(int,int,int))D_0231234; if (fp) fp(*(int*)D_0231238, a1, a0)
// (the daddu a2,a0 before the guard forwards the caller's a0 as the 3rd argument)
extern char D_0231234[];
extern char D_0231238[];

void FUN_001c0340(int a0, int a1)
{
    void (*fp)(int, int, int);

    fp = *(void (**)(int, int, int))D_0231234;
    if (fp != 0)
        fp(*(int *)D_0231238, a1, a0);
}
