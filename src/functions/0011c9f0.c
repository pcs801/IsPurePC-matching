// FUNCTION: SLPM 0x0011C9F0  size 104  core 100
extern int FUN_0012b7a8(signed char a, signed char b);
extern int FUN_00117dc0(char *p);

int FUN_0011c9f0(char *c)
{
    char *r = *(char **)(*(char **)(c + 0x44) + 8);

    if (FUN_0012b7a8(r[1], r[2]) == 0) {
        *(int *)(*(char **)(c + 0x44) + 8) += 4;
        FUN_00117dc0(c);
        return 0;
    }
    *(short *)(c + 0xE) = 0;
    c[0xD] = 0;
    return 0;
}
