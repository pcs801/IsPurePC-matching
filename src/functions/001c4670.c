// FUNCTION: SLPM 0x001C4670  size 48 core 44
extern char D_002686D0[];
extern void FUN_001c4708(char *);

void FUN_001c4670(char *p, int v)
{
    if (p == 0) {
        FUN_001c4708(D_002686D0);
        return;
    }
    *(char *)(p + 3) = (char)v;
}
