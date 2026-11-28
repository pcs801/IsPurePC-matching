// FUNCTION: SLPM 0x00119498  size 48  core 44
extern void FUN_00117dc0(void);

int FUN_00119498(char *p)
{
    int *q = *(int **)(p + 0x44);

    q[2] = q[2] + 4;
    FUN_00117dc0();
    return 0;
}
