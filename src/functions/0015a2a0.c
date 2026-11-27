// FUNCTION: SLPM 0x0015A2A0  size 40  core 40
extern unsigned char D_009B5C00[];

int FUN_0015a2a0(void)
{
    unsigned char *p = D_009B5C00;

    if (*(unsigned short *)p == 0)
        return p[2] != 0;
    return 1;
}
