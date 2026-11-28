// FUNCTION: SLPM 0x001CF5B8
extern char D_00242F20[];
extern int D_00242F18;
extern int D_00242F1C;
extern void FUN_001fbb84(char *, int, int);

void FUN_001cf5b8(void)
{
    FUN_001fbb84(D_00242F20, 0, 0x100);
    D_00242F1C = 0;
    D_00242F18 = 0;
}
