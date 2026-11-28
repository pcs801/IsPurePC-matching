// FUNCTION: SLPM 0x001BC328  size 48  core 44
// fp = *(void(**)(int))D_023055C; if (fp) fp(*(int*)D_0230560);
extern char D_023055C[];
extern char D_0230560[];

void FUN_001bc328(void)
{
    void (*fp)(int);

    fp = *(void (**)(int))D_023055C;
    if (fp != 0)
        fp(*(int *)D_0230560);
}
