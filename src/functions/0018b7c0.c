// FUNCTION: SLPM 0x0018B7C0  size 88  core 88
// Symbol region = this function (64 B) + three tiny returns at 0x0018B800/08/10.
extern char D_002708B0[];
extern char D_00262558[];
extern int FUN_0020c108(void *a0, int a1, int a2, int a3);
extern void FUN_001862e0(void *a0, int a1);

int FUN_0018b7c0(void)
{
    int r = FUN_0020c108(D_002708B0, 0, 0, 0);

    FUN_001862e0(D_00262558, r);
    return 1;
}

int FUN_0018b800(void)
{
    return 1;
}

int FUN_0018b808(void)
{
    return 1;
}

int FUN_0018b810(void)
{
    return 0;
}
