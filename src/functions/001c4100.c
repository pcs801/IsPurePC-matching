extern char D_00268498[];
extern int FUN_001c4708(char *p);

int FUN_001c4100(int a0)
{
    if (a0 == 0) {
        FUN_001c4708(D_00268498);
        return -1;
    }
    return *(int *)(a0 + 0x24);
}
