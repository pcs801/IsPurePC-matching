// FUNCTION: SLPM 0x001B2110  size 48  core 40
// v0 = 0x863078; v1 = *v0; if (v1) jalr v1 with a0 = *(int*)(v0+4)
extern char D_0863078[];

void FUN_001b2110(void)
{
    void (*fp)(int);

    fp = *(void (**)(int))D_0863078;
    if (fp != 0)
        fp(*(int *)(D_0863078 + 4));
}
