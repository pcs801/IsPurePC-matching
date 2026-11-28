// FUNCTION: SLPM 0x001F9898  size 120  core 104
extern char D_00256714[];
extern char D_0086C1F8[];
extern void FUN_002059e0(int);
extern void FUN_002059c0(int);

void FUN_001f9898(int a0, int *p)
{
    int *head;


    p[2] = a0;
    p[1] = 0;
    p[0] = 0;
    p[3] = 0;
    p[4] = 0;
    FUN_002059e0(*(int *)D_00256714);
    head = (int *)D_0086C1F8;
    p[5] = *head;
    *head = (int)p;
    FUN_002059c0(*(int *)D_00256714);
}
