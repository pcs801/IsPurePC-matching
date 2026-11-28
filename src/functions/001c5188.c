extern char D_00268860[];
extern int FUN_001c4cf8(int a0, char *a1);

int FUN_001c5188(int a0)
{
    if (a0 == 0) {
        FUN_001c4cf8(0, D_00268860);
        return 0;
    }
    return *(int *)(a0 + 0x10);
}
