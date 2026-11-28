// FUNCTION: SLPM 0x001B6060  size 144  core 144 - wrapper ladder, 6 thunks
extern void FUN_001be9c0(void);
extern void FUN_001be9d0(void);
extern void FUN_001be9a0(void);
extern void FUN_001be9b0(void);
extern void FUN_001bea38(void);
extern void FUN_001cf618(void *p);

void FUN_001b6060(void)
{
    FUN_001be9c0();
}

void FUN_001b6078(void)
{
    FUN_001be9d0();
}

void FUN_001b6090(void)
{
    FUN_001be9a0();
}

void FUN_001b60a8(void)
{
    FUN_001be9b0();
}

void FUN_001b60c0(void)
{
    FUN_001bea38();
}

void FUN_001b60d8(int a0, int a1)
{
    FUN_001cf618((void *)a1);
}
