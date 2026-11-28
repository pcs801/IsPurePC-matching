extern void FUN_00128340(char *p);
extern void FUN_001283c8(void);
extern void FUN_00117dc0(char *p);

int FUN_0011b3e0(char *p)
{
    int *q;

    FUN_00128340(p);
    FUN_001283c8();
    q = *(int **)(p + 0x44);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
