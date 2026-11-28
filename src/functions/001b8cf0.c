extern char D_002663E8[];
extern void FUN_001cf618(char *);

void FUN_001b8cf0(char *p, int v)
{
    if (p == 0) {
        FUN_001cf618(D_002663E8);
        return;
    }
    *(char *)(p + 0x70) = (char)v;
}