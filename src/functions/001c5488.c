// FUNCTION: SLPM 0x001C5488  size 56  core 56
extern char D_002688E8[];
extern void FUN_001c4cf8(void *a0, void *a1);

int FUN_001c5488(char *p)
{
    if (p == 0) {
        FUN_001c4cf8(p, D_002688E8);
        return 0;
    }
    return *(int *)(p + 20);
}
