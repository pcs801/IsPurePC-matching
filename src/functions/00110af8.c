// FUNCTION: SLPM 0x00110AF8
extern int D_01B9F8F0[];
extern int D_01B7E4A8[];
extern int D_01B7E430[];
extern int D_01B7E448[];
extern int D_0026FEA8;
extern int D_0026FEA0;
extern void FUN_00105fb8(void);
extern void FUN_00112588(int);
extern int FUN_00111768(char *, int *);
extern int FUN_00113820(char *, int, int);
extern void FUN_001117a8(char *, int);
extern void FUN_00111238(void);
extern int FUN_00111810(char *, int *);
extern int FUN_001ee720(char *, int, int, char *, int);
extern void FUN_00111870(char *, int);
extern void FUN_00111250(void);
extern int FUN_00112ac8(void *);
extern int FUN_001113d0(void);
extern void FUN_00113420(int);
extern void FUN_00111d80(void *);
extern int FUN_00112598(char *);
extern int FUN_00112618(char *);
extern void FUN_00113480(void);
extern void FUN_00111de8(void *);

int FUN_00110af8(char *a0, char *a1, char *a2)
{
    int out[12];
    int n;
    int d;
    int flag = 0;
    int s3 = *(int *)(a2 + 4);
    int s4 = s3;
    int *tbl = D_01B9F8F0;

    while (s3 >= 5) {
        if (FUN_00112598(a0) == 3)
            break;
        FUN_00105fb8();
        if (*(int *)(a0 + 8) >= 11 && D_0026FEA8 != 0 &&
            (*(int *)(*(int *)((char *)tbl + 0x10) + 8) & 8) != 0)
            FUN_00112588((int)D_01B7E4A8);
        d = FUN_00111768(a1, &out[8]);
        if (s4 > 0 && d > 0xFFFF) {
            int t;
            t = FUN_00113820(a2, out[8], 0x10000);
            FUN_001117a8(a1, t);
            s4 -= t;
        }
        FUN_00111238();
        n = FUN_00111810(a1, &out[9]);
        if (n > 0) {
            int t;
            t = FUN_001ee720(a0, out[9], n, a1, *(int *)(a1 + 0x50008));
            FUN_00111870(a1, t);
            s3 -= t;
        }
        FUN_00111250();
        if (flag == 0 && FUN_00112ac8(D_01B7E430) != 0 && FUN_001113d0() != 0) {
            FUN_00113420(1);
            if (D_0026FEA0 != 0)
                FUN_00111d80(D_01B7E448);
            flag = 1;
        }
    }

    while (FUN_00112618(a0) == 0)
        FUN_00111238();
    while (FUN_00112598(a0) != 3)
        FUN_00111238();
    FUN_00113480();
    if (D_0026FEA0 != 0)
        FUN_00111de8(D_01B7E448);
    return 1;
}
