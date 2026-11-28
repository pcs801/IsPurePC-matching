// FUNCTION: SLPM 0x001CBB78  size 48  core 44
// fp = *(void(**)(int))D_0865C40; if (fp) fp(*(int*)D_0865C44);
extern char D_0865C40[];

void FUN_001cbb78(void)
{
    void (*fp)(int);

    fp = *(void (**)(int))D_0865C40;
    if (fp != 0)
        fp(*(int *)(D_0865C40 + 4));
}
