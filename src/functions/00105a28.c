extern char D_D6E8D0[];
extern int FUN_00102260(void);

int FUN_00105a28(void)
{
    *(int *)(D_D6E8D0 + 0x00) = 0;
    *(int *)(D_D6E8D0 + 0x24) = 2000;
    *(int *)(D_D6E8D0 + 0x10) = 0;
    *(int *)(D_D6E8D0 + 0x14) = 0;
    *(int *)(D_D6E8D0 + 0x18) = 0;
    *(int *)(D_D6E8D0 + 0x1C) = 0;
    *(int *)(D_D6E8D0 + 0x20) = 0;
    return FUN_00102260();
}
