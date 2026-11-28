// FUNCTION: SLPM 0x0016DE48  (TU tu/0016de48 probe)
extern int D_00270590;
extern char D_00218DB8[];
extern char D_0085E418[];
extern char D_0A98D9D[];
extern char D_0016B238[];
extern void FUN_001699d8(int, int, int, int);

void FUN_0016de48(int a0)
{
    int idx;
    int t;
    int u;

    idx = D_00270590;
    t = *(int *)(D_00218DB8 + idx * 16);
    u = *(int *)(D_0085E418 + idx * 36);
    FUN_001699d8(a0, (int)D_0A98D9D, *(int *)(t + u * 4), (int)D_0016B238);
}
