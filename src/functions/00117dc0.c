// FUNCTION: SLPM 0x00117DC0
extern char D_00213590[];
extern int FUN_001fc8c0(char *, int);

int FUN_00117dc0(char *p)
{
    int idx = *(unsigned char *)(*(int *)(*(int *)(p + 0x44) + 8));
    int *t = (int *)(D_00213590 + idx * 24);
    int a;
    int b;

    p[0xD] = 1;
    a = t[0];
    b = t[1];
    *(short *)(p + 0x10) = 0;
    *(int *)p = a;
    return FUN_001fc8c0(p + 0x14, b);
}
