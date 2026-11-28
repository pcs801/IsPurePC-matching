// FUNCTION: SLPM 0x0016E120  (TU tu/0016de48 family, recipe from t561)
// idx = D_00270590 (gp); t = *(int*)(D_00218DB8 + idx*16); u = *(int*)(D_0085E418 + idx*36);
// FUN_00169e28(a0, (int)D_0A98DA2, *(int*)(t + u*4), 0);
extern int D_00270590;
extern char D_00218DB8[];
extern char D_0085E418[];
extern char D_0A98DA2[];
extern void FUN_00169e28(int, int, int, int);

void FUN_0016e120(int a0)
{
    int idx;
    int t;
    int u;

    idx = D_00270590;
    t = *(int *)(D_00218DB8 + idx * 16);
    u = *(int *)(D_0085E418 + idx * 36);
    FUN_00169e28(a0, (int)D_0A98DA2, *(int *)(t + u * 4), 0);
}
