// FUNCTION: SLPM 0x00106FA8  size 520  core 516
extern unsigned char D_281580[];
extern char D_00258050[];
extern char D_00258060[];
extern char D_00258080[];
extern char D_00258090[];
extern char D_002580A8[];
extern char D_002580C0[];
extern char D_002580D8[];
extern char D_002580E8[];
extern char D_00258100[];
extern char D_00258118[];
extern int D_0026FC70;
extern int D_00D6E8E0[];

extern int FUN_001b7758(int);
extern int FUN_001b8a70(int);
extern int FUN_001b7e58(int);
extern int FUN_001b7bf0(int, int);
extern int FUN_001b7090(int);
extern int FUN_0010bed8(char *, ...);
extern int FUN_001fbd78(void *, ...);
extern void FUN_00102260(void);

void FUN_00106fa8(int a0)
{
    unsigned char *p = D_281580 + a0 * 0x4E280;
    int t;
    int s3, s2, s1, t0;
    int idx;

    t = FUN_001b7758(*(int *)(p + 4));
    FUN_0010bed8(D_00258050, t / 6000, (t / 100) % 60, t % 100);
    s3 = FUN_001b8a70(*(int *)(p + 4));
    s2 = FUN_001b7e58(*(int *)(p + 4));
    s1 = FUN_001b7bf0(*(int *)(p + 4), 0);
    t0 = FUN_001b7bf0(*(int *)(p + 4), 1);
    FUN_0010bed8(D_00258060, s3, s2, s1, t0);
    idx = FUN_001b7090(*(int *)(p + 4));
    if (idx != D_0026FC70) {
        D_0026FC70 = idx;
        if ((unsigned int)idx < 7) {
            switch (idx) {
            case 0:
                FUN_001fbd78(D_00258080, 0, 0, 0);
                break;
            case 1:
                FUN_001fbd78(D_00258090, 0, 0, 0);
                break;
            case 2:
                FUN_001fbd78(D_002580A8, 0, 0, 0);
                break;
            case 3:
                FUN_001fbd78(D_002580C0, 0, 0, 0);
                break;
            case 4:
                FUN_001fbd78(D_002580D8, 0, 0, 0);
                break;
            case 5:
                FUN_001fbd78(D_002580E8, 0, 0, 0);
                break;
            case 6:
                FUN_001fbd78(D_00258100, 0, 0, 0);
                break;
            }
        }
    }
    FUN_00102260();
    FUN_001fbd78(D_00258118, D_00D6E8E0[2], D_00D6E8E0[1], D_00D6E8E0[0]);
}
