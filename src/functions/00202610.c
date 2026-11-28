// FUNCTION: SLPM 0x00202610  size 128  core 128
extern char D_0204960[];
extern char D_02049C8[];
extern char D_0204A48[];
extern char D_0204AB0[];

void FUN_00202610(char *p, int a1, int a2, int a3)
{
    *(int *)p = 0;
    *(int *)(p + 4) = 0;
    *(int *)(p + 8) = 0;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x18) = 0;
    *(int *)(p + 0x1C) = (int)p;
    *(int *)(p + 0x20) = (int)D_0204960;
    *(int *)(p + 0x24) = (int)D_02049C8;
    *(int *)(p + 0x28) = (int)D_0204A48;
    *(int *)(p + 0x2C) = (int)D_0204AB0;
    *(int *)(p + 0x54) = a3;
    *(short *)(p + 0xC) = a1;
    *(short *)(p + 0xE) = a2;
}
