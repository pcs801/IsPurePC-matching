extern int *D_00270AB0;
extern unsigned char D_1B741F8[];
extern signed char D_00212F80[];
extern unsigned char D_B257C7[];

void FUN_00108740(int a0)
{
    int i = D_00270AB0[1];
    int v;
    for (; ; i = D_00270AB0[1]) {
        if (D_1B741F8[i] != 6) {
            D_1B741F8[i] = (D_1B741F8[i] + a0 + 8) % 8;
            if (D_00212F80[D_00270AB0[1] * 8 + D_1B741F8[D_00270AB0[1]]] != 0)
                return;
        } else {
            v = D_00270AB0[i + 2];
            if (v != 0) {
                D_B257C7[i * 4 + v] += a0;
                return;
            }
            D_1B741F8[i] = (D_1B741F8[i] + a0 + 8) % 8;
            if (D_00212F80[D_00270AB0[1] * 8 + D_1B741F8[D_00270AB0[1]]] != 0)
                return;
        }
    }
}
