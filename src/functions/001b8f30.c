// FUNCTION: SLPM 0x001B8F30  size 48 core 44
extern char D_00266480[];
extern int FUN_001cf618(char *);

int FUN_001b8f30(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00266480);
        return 0;
    }
    return *(signed char *)(p + 0x72);
}
