extern int FUN_001b4568(int a0);
extern int FUN_001af828(void);

void FUN_001b46c0(int a0)
{
    int c;

    FUN_001b4568(a0);
    do {
        FUN_001af828();
        c = *(signed char *)(a0 + 0x49);
    } while (c != 0);
}
