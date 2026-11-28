// FUNCTION: SLPM 0x001BED40  size 488  core 488
// jtbl_00267670 = 10 entries, 3 distinct targets: idx2 -> 0x1BED90,
// idx1/3/9 -> 0x1BEE08, idx0/4/5/6/7/8 -> 0x1BEE10 (clears s[4]).
extern int D_002305BC;
extern int D_002305C0;
extern int D_002305C4;
extern int D_002305F0;
extern unsigned char D_002305F4;
extern char D_00267648[];
extern int FUN_001bf5a8(int a);
extern int FUN_001f5d28(void);
extern int FUN_001f4e30(int a);
extern int FUN_00208450(void *a, int b);
extern int FUN_001f5868(int a, int b, int c);
extern int FUN_001bebe0(void *a);

void FUN_001bed40(char *s)
{
    int a1 = *(unsigned char *)(s + 2);
    int v;
    int r;

    if (*(int *)(s + 4) == 1) {
        v = *(signed char *)(s + 2);
        if ((unsigned int)v >= 10) {
            *(int *)(s + 4) = 0;
        } else {
            switch (v) {
            case 2:
                FUN_001bf5a8(5632);
                r = FUN_001f5d28();
                FUN_001bf5a8(5633);
                if (r == 0)
                    FUN_00208450(D_00267648, D_002305BC);
                FUN_001bf5a8(5888);
                FUN_001f4e30(0);
                FUN_001bf5a8(5889);
                *(char *)(s + 2) = 0;
                D_002305C4++;
                a1 = 0;
                *(int *)(s + 4) = 0;
                break;
            case 1:
            case 3:
            case 9:
                *(char *)(s + 2) = 0;
                a1 = 0;
                *(int *)(s + 4) = 0;
                break;
            default:
                *(int *)(s + 4) = 0;
                break;
            }
        }
    }

    v = (signed char)a1;
    if (v == 1) {
        FUN_001bf5a8(6144);
        if (D_002305F0 == v)
            *(char *)(s + 21) = D_002305F4;
        r = FUN_001f5868(*(int *)(s + 8), *(int *)(s + 12), *(int *)(s + 16));
        FUN_001bf5a8(6145);
        if (r == v) {
            *(char *)(s + 2) = 2;
            D_002305C0++;
            a1 = 2;
        } else {
            *(char *)(s + 2) = 9;
            a1 = 9;
            *(int *)(s + 52) = -1;
        }
    }

    v = (signed char)a1;
    if (v == 2) {
        FUN_001bf5a8(6400);
        r = FUN_001f4e30(1);
        FUN_001bf5a8(6401);
        v = FUN_001bebe0(s);
        if (r == 0) {
            *(char *)(s + 2) = v == 1 ? 9 : 3;
            D_002305C4++;
        }
    }
}
