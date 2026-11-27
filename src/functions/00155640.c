// FUNCTION: SLPM 0x00155640  size 1152  core 1148  (needs_G8)
// 5-phase scene state machine; jtbl_0025C2D0 = 0x0025C2D0 (5 entries).
// Accumulated source: entry + case0 (memset + fill + continuation) + case1
// + case2 + case3 + case4 + shared exit. Intra-block alignment not chased yet.
extern int D_00270BD0;
extern int D_00270C0C;
extern char D_002173D0[];
extern int D_C56500[];
extern char D_1B73FC0[];
extern int FUN_001fbb84(void *p, int c, int n);
extern int FUN_00171720(void *p);
extern int FUN_0017efe8(void);
extern int FUN_00160570(void);
extern int FUN_0015b598(void *a, void *b, void *c, int d, int e, int f, int g);
extern int FUN_00154f98(void);
extern int FUN_00160a70(void *p, int v);
extern int FUN_0015c6d8(int v);
extern int FUN_0017efa0(int a, int b);
extern int FUN_00106668(int a);
extern int FUN_00177e88(void *a, void *b, int c, int d, int e, int f);
extern int FUN_00178080(void *a, void *b, int c, int d, int e, int f);
extern int FUN_00102020(void);
extern int FUN_00104e20(void);
extern int FUN_00157dd8(void *a, void *b);
extern int FUN_0015bd40(void);

int FUN_00155640(char *obj)
{
    int i;
    int v;

    D_00270BD0 = *(int *)(obj + 0x44);

    switch (*(short *)(obj + 0x10)) {
    case 0:
        FUN_001fbb84((void *)D_00270BD0, 0, 0x414B80);
        for (i = 0; i < 3; i++) {
            *(int *)(D_002173D0 + 0x10 + i * 0x24) = 0x2DEBA0 + D_00270BD0;
            FUN_00171720((void *)(D_002173D0 + i * 0x24));
        }
        if (D_00270C0C == 19)
            FUN_0015b598((void *)(0x10800 + D_00270BD0), (void *)(0x314B80 + D_00270BD0),
                         (void *)(0xF7EC + D_00270BD0), 0x80, 1, 4, 0);
        else
            FUN_0015b598((void *)(0x10800 + D_00270BD0), (void *)(0x314B80 + D_00270BD0),
                         (void *)(0xF7EC + D_00270BD0), 0x80, 1, 4, 0);
        FUN_00154f98();
        FUN_00160a70((void *)(0x10800 + D_00270BD0), *(int *)(D_00270BD0 + 0x7F8));
        FUN_0015c6d8(0);
        FUN_0017efa0(2, 10);
        *(short *)(obj + 0x10) = 1;
        break;
    case 1:
        if (FUN_0017efe8() == 1)
            *(short *)(obj + 0x10) = 2;
        break;
    case 2:
        if (D_C56500[2] & 0x2000) {
            int q = *(int *)(D_00270BD0 + 0x10808);
            char *r = (char *)(D_00270BD0 + 0xF7E0 + q * 0x20);
            if (*(signed char *)(r + 20) != 0 || *(signed char *)(r + 17) != 0) {
                FUN_00106668(11);
            } else {
                FUN_00106668(0);
                FUN_00177e88((void *)(0x2DB480 + D_00270BD0), (void *)0x217450, 1, 0, -1, 0xE66);
                *(int *)(D_00270BD0 + 0x107F4) = 1;
                *(short *)(obj + 0x10) = 3;
            }
        } else if (D_C56500[2] & 0x4300) {
            FUN_00106668(1);
            FUN_0017efa0(3, 10);
            *(int *)(D_00270BD0 + 0x107F0) = 1;
            *(short *)(obj + 0x10) = 4;
        } else {
            FUN_0015bd40();
        }
        break;
    case 3:
        if (D_C56500[2] & 0x2000) {
            if (*(int *)(D_00270BD0 + 0x107F4) != 0) {
                FUN_00106668(1);
                *(short *)(obj + 0x10) = 2;
            } else {
                FUN_00106668(0);
                FUN_0017efa0(3, 10);
                *(int *)(D_00270BD0 + 0x107F4) = 2;
                *(short *)(obj + 0x10) = 4;
            }
        } else if (D_C56500[4] & 0xF0) {
            FUN_00106668(3);
            *(int *)(D_00270BD0 + 0x107F4) = (*(int *)(D_00270BD0 + 0x107F4) < 1);
        }
        {
            int args[6];
            args[0] = 320;
            args[1] = 224;
            args[2] = 0;
            args[3] = 0;
            args[4] = 32;
            args[5] = 32;
            FUN_00178080((void *)(0x2DB480 + D_00270BD0), args, 0,
                         ~*(int *)(D_00270BD0 + 0x107F4), 1, 1);
        }
        break;
    case 4:
        if (FUN_0017efe8() != 1)
            break;
        FUN_00102020();
        v = *(int *)(D_00270BD0 + 0x107F4);
        if (v != 2)
            return v;
        FUN_00104e20();
        *(int *)(D_1B73FC0 + 0xD0) =
            *(int *)(D_00270BD0 + 0x2BC + *(int *)(D_00270BD0 + 0x10808) * 0x1EC);
        *(int *)(D_1B73FC0 + 0xCC) = *(int *)(D_00270BD0 + 0x107EC);
        FUN_00157dd8((void *)0x25C2B0, D_1B73FC0);
        return *(int *)(D_00270BD0 + 0x107F0);
    default:
        break;
    }

    FUN_00160570();
    return 0;
}