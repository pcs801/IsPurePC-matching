// FUNCTION: SLPM 0x001C7178  size 52  core 52
extern char D_00238870[];
extern char D_00238868[];

void FUN_001c7178(int a0, int *out1, int *out2)
{
    if (*(int *)D_00238870 == 1 && *(int *)D_00238868 <= 0)
        return;
    *out1 = 0;
    *out2 = 0xBB80;
}
