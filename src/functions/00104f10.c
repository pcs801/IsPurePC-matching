extern unsigned char D_A98D90;
extern void FUN_001b98e8(int);

void FUN_00104f10(int v)
{
    D_A98D90 = v;
    if (D_A98D90 == 0)
        FUN_001b98e8(0);
    else
        FUN_001b98e8(1);
}
