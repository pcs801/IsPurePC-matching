// FUNCTION: SLPM 0x001CA260  size 88  core 88
extern void FUN_001fbb84(int a0, int a1, int a2);
extern void FUN_001fcfa0(int a0, int a1, int a2);
extern void FUN_001ca118(int a0, int a1);

void FUN_001ca260(char *p, int v)
{
    FUN_001fbb84(*(int *)(p + 0), 0, *(int *)(p + 4));
    FUN_001fcfa0(*(int *)(p + 0), v, 7);
    FUN_001ca118(*(int *)(p + 4) - 16, *(int *)(p + 0) + 8);
}
