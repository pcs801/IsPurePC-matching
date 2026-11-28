// FUNCTION: SLPM 0x00172F30  size 144  core 140
extern int FUN_00172588(char *p, int a1, int a2, int a3);

int FUN_00172f30(char *p, int n, int a2, int a3, int a4)
{
    int sum = 0;
    int i;

    for (i = 0; i < n; i++) {
        sum += FUN_00172588(p, a2, a3 + sum, a4);
        p += 0x10;
    }
    return sum;
}
