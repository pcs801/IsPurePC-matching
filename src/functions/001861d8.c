// FUNCTION: SLPM 0x001861d8  size 80  core 80
extern char D_1B9F780[];
extern int FUN_001a09a0(int a0, char *a1, int a2);

int FUN_001861d8(char *p)
{
    char buf[4];
    char *q = *(char **)(p + 0x44);

    *q = 1;
    buf[2] = -1;
    buf[1] = -1;
    buf[0] = -1;
    buf[3] = -0x80;
    FUN_001a09a0((int)D_1B9F780, buf, *(int *)(q + 4));
    return 0;
}
