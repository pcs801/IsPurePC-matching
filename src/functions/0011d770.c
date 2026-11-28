// FUNCTION: SLPM 0x0011D770  size 64  core 60
// q = *(int**)(p+0x44); if (*(unsigned char*)(D_00270CAC + 0x4C5) == 0) { ... }
extern char *D_00270CAC;
extern void FUN_00115f90(int);
extern void FUN_00116c0(int);

void FUN_0011d770(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (*(unsigned char *)(D_00270CAC + 0x4C5) == 0) {
        FUN_00115f90(*(unsigned short *)(*(int *)(q + 8) + 2));
        FUN_00116c0(*(int *)(q + 8));
    }
}
