// FUNCTION: SLPM 0x001C0418  size 200  core 196
// jtbl_00267A00 (10 entries, recovered with tools/jtbl.py --va 0x00267A00 --count 10):
//   [9] -> f2 = 3; [3] -> f14 = f10, f2 = 1, fC += f10; [0] -> f2 = 0;
//   [1,2,4..8] and out-of-range -> tail-call FUN_001caeb0 without FUN_001be630/clear.
// All ten labels are listed (empty ones first) so ee-gcc keeps the dense jump table;
// the table address needs the build/jtbl-map.json entry because 0x267A00 lies above the
// resolver's target-guided fallback window (< 0x20000000).
// NEAR-MISS: 196/196 bytes, 24 words left - only the placement of the shared exit block
// differs (target: case bodies -> be630/clear tail -> exit; ours: exit first).

struct S {
    unsigned char pad0[2];
    unsigned char f2;
    unsigned char pad1[9];
    int fC;
    int f10;
    int f14;
    unsigned char pad2[4];
    int f1C;
};

extern void FUN_001cae38(struct S *);
extern int FUN_001be870(int);
extern void FUN_001be630(int);
extern void FUN_001caeb0(void);

void FUN_001c0418(struct S *p)
{
    int v;

    if (p->f1C == 0)
        return;
    FUN_001cae38(p);
    v = FUN_001be870(p->f1C);
    switch (v) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    default:
        FUN_001caeb0();
        return;
    case 9:
        p->f2 = 3;
        break;
    case 3:
        p->f14 = p->f10;
        p->f2 = 1;
        p->fC += p->f10;
        break;
    case 0:
        p->f2 = 0;
        break;
    }
    FUN_001be630(p->f1C);
    p->f1C = 0;
    FUN_001caeb0();
}
