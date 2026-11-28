extern char D_00268468[];
extern int FUN_001c4708(char *p);

int FUN_001c4098(int a0)
{
    if (a0 == 0) {
        FUN_001c4708(D_00268468);
        return -1;
    }
    return *(signed char *)(a0 + 1);
}
