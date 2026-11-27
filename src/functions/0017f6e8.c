// FUNCTION: SLPM 0x0017F6E8  size 40  core 40
extern void FUN_0017f048(void *);
extern void FUN_0017f168(void *);

void FUN_0017f6e8(char *obj)
{
    if (*(unsigned char *)(*(int *)(obj + 0x44) + 2) == 0)
        FUN_0017f048(obj);
    else
        FUN_0017f168(obj);
}
