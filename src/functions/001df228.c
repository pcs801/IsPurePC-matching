extern signed char D_00249D50[];
extern signed char D_00249D58[];

int FUN_001df228(unsigned int a0, int a1)
{
    unsigned int i;

    i = a0 & 7;
    return (a1 - D_00249D58[i]) / D_00249D50[i];
}
