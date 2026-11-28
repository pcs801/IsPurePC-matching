extern int D_00232624;
extern int D_00232628;
extern int D_0023262C;

void FUN_001c45f8(void)
{
    void (*fn)(int, int) = *(void (**)(int, int))&D_00232624;

    if (fn != 0)
        fn(D_00232628, D_0023262C);
}
