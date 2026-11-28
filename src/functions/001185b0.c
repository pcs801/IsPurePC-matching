extern char *D_00270CAC;
extern void FUN_001173e8(int a0, int a1);
extern void FUN_00117dc0(char *p);

int FUN_001185b0(char *p)
{
    unsigned short v = *(unsigned short *)(D_00270CAC + 0xD51FA);

    FUN_001173e8(v, 1);
    *(int *)((char *)*(int **)(p + 0x44) + 8) = *(int *)((char *)*(int **)(p + 0x44) + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
