// FUNCTION: SLPM 0x001C7080  size 52  core 52
extern char D_00238870[];
extern char D_00238868[];
extern char D_0023889C[];

int FUN_001c7080(void)
{
    if (*(int *)D_00238870 == 1) {
        if (*(int *)D_00238868 <= 0)
            return 0;
    }
    return *(int *)D_0023889C;
}
