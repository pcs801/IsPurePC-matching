extern void FUN_00128638(int a0, int a1);
extern void FUN_00117dc0(char *p);

int FUN_0011c7d0(char *p)
{
    unsigned char *b = (unsigned char *)*(int **)((char *)*(int **)(p + 0x44) + 8);

    FUN_00128638(b[1], b[2]);
    *(int *)((char *)*(int **)(p + 0x44) + 8) = *(int *)((char *)*(int **)(p + 0x44) + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
