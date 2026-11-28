// FUNCTION: SLPM 0x001B95E0  size 48 core 44
extern char D_00266510[];
extern int FUN_001cf618(char *);
extern int FUN_001b3c38(int);

int FUN_001b95e0(char *p)
{
    if (p == 0)
        return FUN_001cf618(D_00266510);
    return FUN_001b3c38(*(int *)(p + 4));
}
