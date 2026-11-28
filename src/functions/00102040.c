// FUNCTION: SLPM 0x00102040  size 56  core 56
extern char D_00D70000[];

void FUN_00102040(void)
{
    int *p = (int *)(D_00D70000 - 6528) + 3;
    int i = 3;

    do {
        i--;
        *p = 0;
        p--;
    } while (i >= 0);
}
