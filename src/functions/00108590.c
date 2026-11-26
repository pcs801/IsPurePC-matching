// FUNCTION: SLPM 0x00108590  size 432
// sig: addiu ; lw ; sd ; daddu ; sd ; sd ; sd ; sd ; sd ; sd ; sd ; lw

extern int *D_00270AB0;
extern unsigned char D_1B741F8[];
extern unsigned char D_B257C8[];
extern int D_00212F60[];
extern char D_0026FCC8[];
extern char D_0026FCD0[];
extern char D_0026FCD8[];
extern char D_0026FCE0[];
extern char D_0026FCE8[];
extern char D_002583A0[];
extern char D_002583B0[];
extern int FUN_0010bed8(const char *, ...);

int FUN_00108590(int a0, int a1)
{
    int i;

    if (D_00270AB0[1] == a1) {
        if (D_1B741F8[a1] == 6) {
            FUN_0010bed8(D_0026FCC8);
            for (i = 0; i < 5; i++) {
                if (*(int *)((char *)D_00270AB0 + (a1 + 2) * 4) == i)
                    FUN_0010bed8(D_0026FCD0);
                else
                    FUN_0010bed8(D_0026FCD8);
            }
            FUN_0010bed8(D_0026FCE0);
        } else {
            FUN_0010bed8(D_002583A0);
        }
    } else {
        FUN_0010bed8(D_0026FCE0);
    }
    FUN_0010bed8(D_0026FCE8, a0, D_00212F60[D_1B741F8[a1]]);
    if (D_1B741F8[a1] == 6)
        return FUN_0010bed8(D_002583B0, D_B257C8[a1 * 4], D_B257C8[a1 * 4 + 1],
                            D_B257C8[a1 * 4 + 2], D_B257C8[a1 * 4 + 3]);
    return FUN_0010bed8(D_0026FCE0);
}
