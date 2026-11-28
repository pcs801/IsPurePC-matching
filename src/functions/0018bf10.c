// FUNCTION: SLPM 0x0018bf10  size 96  core 96
extern int FUN_0020c708(char *a0, char *a1);

int FUN_0018bf10(char *p, char *q)
{
    int i = 0;

    while (i < 0x64) {
        if (FUN_0020c708(p, q) == 0)
            break;
        q += 0x144;
        i++;
    }
    return i;
}
