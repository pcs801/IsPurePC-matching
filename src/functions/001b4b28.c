extern int FUN_001b4a60(int a0);
extern int FUN_001af828(void);

void FUN_001b4b28(int a0)
{
    FUN_001b4a60(a0);
    while (*(signed char *)(a0 + 1) != 1)
        FUN_001af828();
}
