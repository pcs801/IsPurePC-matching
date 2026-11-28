extern void FUN_001b4af8(void);
extern void FUN_001b46f8(char *p);
extern void FUN_001af828(void);

void FUN_001b4798(char *p)
{
    FUN_001b4af8();
    FUN_001b46f8(p);
    while (*(signed char *)(p + 0x4D) != 0)
        FUN_001af828();
}
