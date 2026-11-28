// FUNCTION: SLPM 0x001CC388  size 48  core 44
// if (*(int*)(p+0xC0) != 0) (*(void(**)(void))D_0241E80)();
extern char D_0241E80[];

void FUN_001cc388(char *p)
{
    if (*(int *)(p + 0xC0) != 0)
        (*(void (**)(void))D_0241E80)();
}
