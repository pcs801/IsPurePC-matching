// FUNCTION: SLPM 0x001C5080  size 64  core 68
extern void FUN_001c5348(void);
extern void FUN_001c4f50(char *);

void FUN_001c5080(char *p)
{
    if (p == 0)
        return;
    FUN_001c5348();
    if (*(signed char *)p == 1) {
        *(char *)p = 0;
        FUN_001c4f50(p);
    }
}
