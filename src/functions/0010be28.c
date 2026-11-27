// FUNCTION: SLPM 0x0010BE28
extern int D_47B168[];
extern int FUN_00205c20(int);
extern int FUN_00208690(void *, int);
extern int FUN_00205d40(int);

int FUN_0010be28(int a0, int a1, int a2)
{
    int id;

    D_47B168[1] = a0;
    D_47B168[0] = a1;
    D_47B168[2] = a2;
    D_47B168[3] = 0;
    FUN_00205c20(0);
    id = FUN_00208690(D_47B168, 1);
    while (FUN_00205d40(id) >= 0)
        ;
    return id != 0 ? 0 : -1;
}
