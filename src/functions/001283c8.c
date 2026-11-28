// FUNCTION: SLPM 0x001283C8  size 88  core 88
extern int D_00270C68;

void FUN_001283c8(void)
{
    char *q = (char *)&D_00270C68;
    int i;

    q[7] = 0;
    *(int *)(q + 0x0C) = 0;
    *(int *)(q + 0x10) = 0;
    *(int *)(q + 0x14) = 0;
    *(int *)(q + 0x18) = 0;
    *(int *)(q + 0x294) = 0;
    *(int *)(q + 0x290) = 0;
    for (i = 0; i < 14; i++) {
        *(int *)(q + 0x24 + i * 0x2C + 4) = 0;
        *(int *)(q + 0x24 + i * 0x2C + 8) = 0;
        *(int *)(q + 0x24 + i * 0x2C + 0x0C) = 0;
    }
}
