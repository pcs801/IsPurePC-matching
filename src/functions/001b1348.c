// FUNCTION: SLPM 0x001B1348  size 80  core 80
extern char D_002270A8[];
extern char D_002270B8[];
extern char D_002270C8[];
extern char D_002270D8[];
extern char D_002270E8[];
extern char D_002270F8[];

int FUN_001b1348(void)
{
    long long one = 1;

    *(long long *)D_002270A8 = one;
    *(long long *)D_002270B8 = one;
    *(long long *)D_002270C8 = one;
    *(long long *)D_002270D8 = one;
    *(long long *)D_002270E8 = one;
    *(long long *)D_002270F8 = one;
    return 1;
}
