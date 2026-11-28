// FUNCTION: SLPM 0x001CBDB8  size 96  core 88  (splat merged two functions)
//  0x1CBDB8: if (p == 0) return; FUN_001ce988(); FUN_001fbb84(p, 0, 0x30);
//  0x1CBE08: return *(signed char*)(p+1);
extern void FUN_001ce988(void);
extern void FUN_001fbb84(char *, int, int);

void FUN_001cbdb8(char *p)
{
    if (p == 0)
        return;
    FUN_001ce988();
    FUN_001fbb84(p, 0, 0x30);
}

int FUN_001cbe08(char *p)
{
    return *(signed char *)(p + 1);
}
