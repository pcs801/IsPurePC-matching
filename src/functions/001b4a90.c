// FUNCTION: SLPM 0x001B4A90  size 64  core 60
// FUN_001b5c28(p); if ((*(long long*)p & 0xFFFF00) != 0x10200) ...
extern void FUN_001b5c28(char *);

void FUN_001b4a90(char *p)
{
    FUN_001b5c28(p);
    if ((*(long long *)p & 0xFFFF00) != 0x10200) {
        return;
    }
}
