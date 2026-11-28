// FUNCTION: SLPM 0x001C1DC8  size 48  core 44
// fp = *(void(**)(int,int,int))D_02320CC; if (fp) fp(*(int*)D_02320D0, a1, a0)
// (daddu a2,a0 at 0x1C1DD4 forwards the caller's a0 as the 3rd argument)
extern char D_02320CC[];
extern char D_02320D0[];

void FUN_001c1dc8(int a0, int a1)
{
    void (*fp)(int, int, int);

    fp = *(void (**)(int, int, int))D_02320CC;
    if (fp != 0)
        fp(*(int *)D_02320D0, a1, a0);
}
