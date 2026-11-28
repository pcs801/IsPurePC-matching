// FUNCTION: SLPM 0x001AE750  size 64  core 60
// if ((a2 & 0x3F) != 0) { FUN_001cf618(D_0265588); return -3; } return FUN_001ae558(a0, a1, a2);
extern char D_0265588[];
extern void FUN_001cf618(char *);
extern int FUN_001ae558(int, int, int);

int FUN_001ae750(int a0, int a1, int a2)
{
    if ((a2 & 0x3F) != 0) {
        FUN_001cf618(D_0265588);
        return -3;
    }
    return FUN_001ae558(a0, a1, a2);
}
