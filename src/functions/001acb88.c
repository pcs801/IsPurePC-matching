extern void FUN_001ace68(char *a0, int a1, int a2, int a3, int t0, int t1);
extern char D_00224240[];

void FUN_001acb88(char *a0, int a1, int a2, int a3)
{
    FUN_001ace68(a0, a1, a2, a3, ((int)D_00224240 + 0x17) & -64, 0x800);
}
