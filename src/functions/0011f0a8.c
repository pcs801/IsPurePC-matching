// FUNCTION: SLPM 0x0011F0A8  size 168  core 164
extern int FUN_00115730(int);
extern int FUN_0013f138(int, int, int, int);
extern int FUN_00117dc0(void *);

int FUN_0011f0a8(char *obj)
{
    char *rec = *(char **)(*(int *)(obj + 0x44) + 8);
    int a = FUN_00115730(*(short *)(rec + 4));
    int b = FUN_00115730(*(short *)(rec + 6));
    int c = FUN_00115730(*(short *)(rec + 8));
    int d = FUN_00115730(*(short *)(rec + 0xA));

    FUN_0013f138(a, b, c, d);
    *(int *)(*(int *)(obj + 0x44) + 8) += 0xC;
    FUN_00117dc0(obj);
    return 0;
}
