// FUNCTION: SLPM 0x001F6E78  size 56  core 56
extern char D_00255EA8[];
extern void FUN_001f6e08(void);

int FUN_001f6e78(void)
{
    if (*(signed char *)D_00255EA8 == 0)
        FUN_001f6e08();
    return *(signed char *)(D_00255EA8 + 4) == 0x54;
}
