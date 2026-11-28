extern void FUN_0012c120(int a0);
extern void FUN_00117dc0(char *p);

int FUN_0011cbc8(char *p)
{
    unsigned char *b = (unsigned char *)*(int **)((char *)*(int **)(p + 0x44) + 8);

    FUN_0012c120(b[1]);
    *(int *)((char *)*(int **)(p + 0x44) + 8) = *(int *)((char *)*(int **)(p + 0x44) + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
