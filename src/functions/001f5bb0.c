// FUNCTION: SLPM 0x001F5BB0  size 32  core 28
// r = FUN_001f5b18(); nor v1,zero,v0 / movz v0,zero,v1 -> return r, but 0 when r == -1
extern int FUN_001f5b18(void);

int FUN_001f5bb0(void)
{
    int r;

    r = FUN_001f5b18();
    return (r == -1) ? 0 : r;
}
