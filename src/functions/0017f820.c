// FUNCTION: SLPM 0x0017f820  size 80  core 76
extern char D_1B9F780[];
extern int FUN_001a09a0(int a0, char *a1, int a2);

int FUN_0017f820(char *p)
{
    char buf[4];
    char *q = *(char **)(p + 0x44);

    *q = 1;
    buf[3] = -0x80;
    buf[2] = 0;
    buf[1] = 0;
    buf[0] = 0;
    FUN_001a09a0((int)D_1B9F780, buf, *(int *)(q + 4));
    return 0;
}
