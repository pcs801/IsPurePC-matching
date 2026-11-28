// FUNCTION: SLPM 0x001F8758  size 56  core 52
// if (*D_086C1F0 == 0) { *D_086C1F0 = 1; FUN_001f8698(); }
extern char D_086C1F0[];
extern void FUN_001f8698(void);

void FUN_001f8758(void)
{
    if (*(int *)D_086C1F0 == 0) {
        *(int *)D_086C1F0 = 1;
        FUN_001f8698();
    }
}
