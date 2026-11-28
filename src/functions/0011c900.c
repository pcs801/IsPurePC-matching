extern void FUN_0012b1c8(int a0, int a1);
extern void FUN_00117dc0(char *p);

int FUN_0011c900(char *p)
{
    unsigned char *b = (unsigned char *)*(int **)((char *)*(int **)(p + 0x44) + 8);

    FUN_0012b1c8(b[1], *(unsigned short *)(b + 2));
    *(int *)((char *)*(int **)(p + 0x44) + 8) = *(int *)((char *)*(int **)(p + 0x44) + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
