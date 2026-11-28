extern void FUN_001f12a0(void);

void FUN_001f1798(void)
{
    if ((*(int *)0x10002010 & 0x80004000) != (int)0x80000000)
        return;
    FUN_001f12a0();
}
