// FUNCTION: SLPM 0x0011F030  size 120  core 116
extern int FUN_00115730(int);
extern int FUN_0013eeb0(int, int);
extern int FUN_00117dc0(void *);

int FUN_0011f030(char *obj)
{
    char *rec = *(char **)(*(int *)(obj + 0x44) + 8);
    int a = FUN_00115730(*(short *)(rec + 4));
    int b = FUN_00115730(*(short *)(rec + 6));

    FUN_0013eeb0(a, b);
    *(int *)(*(int *)(obj + 0x44) + 8) += 8;
    FUN_00117dc0(obj);
    return 0;
}
