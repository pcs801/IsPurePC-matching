extern char D_002683A8[];
extern int FUN_001c4708(char *p);

void FUN_001c3dc8(int a0)
{
    if (a0 == 0) {
        FUN_001c4708(D_002683A8);
        return;
    }
    if (*(signed char *)(a0 + 1) == 0) {
        *(int *)(a0 + 0x1C) = 0;
        *(int *)(a0 + 0x24) = 0;
        *(int *)(a0 + 0x20) = 0;
    }
}
