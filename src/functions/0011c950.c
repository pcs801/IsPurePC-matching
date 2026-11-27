// FUNCTION: SLPM 0x0011C950  size 80  core 80
extern void FUN_0012b6d8(int, int);
extern void FUN_00117dc0(char *);

int FUN_0011c950(char *p)
{
    int r = *(int *)(*(int *)(p + 0x44) + 8);
    int q;

    FUN_0012b6d8(*(unsigned char *)(r + 1), *(unsigned short *)(r + 2));
    q = *(int *)(p + 0x44);
    *(int *)(q + 8) = *(int *)(q + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
