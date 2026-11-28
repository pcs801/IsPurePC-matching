// FUNCTION: SLPM 0x001B99E0  size 48 core 44
extern char D_00266540[];
extern int FUN_001cf618(char *);
extern int FUN_001b3c70(int);

int FUN_001b99e0(char *p)
{
    if (p == 0)
        return FUN_001cf618(D_00266540);
    return FUN_001b3c70(*(int *)(p + 4));
}
