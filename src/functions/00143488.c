// FUNCTION: SLPM 0x00143488  size 176  core 176  (g=8)
// Jump-table dispatcher over s->f0 (11 entries at 0x0025AA80):
//   idx 0/1/2  -> 0x14352C (return, no call)
//   idx 3..6   -> 0x1434C8 (idx = (s->f6F8 < 2) ? 3 : 0)
//   idx 7..10  -> 0x1434E0 (idx = s->f154 ? 1 : 2)
// Then FUN_00179208(s + 0x2881C, tbl[idx].p, tbl[idx].n, tag{0,0}, 1).
// Status: 176/176 bytes, 4 words off - target selects the case-A value branchlessly
// (li v1,3 / move a1,zero / slti / movn a1,v1,v0) while ee-gcc -O2 picks a branch
// (slti / beq / move a1,zero / li a1,3). Same width, same semantics.
extern void *D_00270BBC;
extern void FUN_00179208(void *dst, void *src, int size, int *tag, int flag);

struct S {
    int f0;
    char pad0[0x14C - 0x4];
    int f14C;
    int pad14C;
    int f154;
    char pad154[0x6F8 - 0x158];
    int f6F8;
};

struct Pair {
    void *p;
    int n;
};

extern struct Pair D_00215990[];

void FUN_00143488(void)
{
    struct S *s = D_00270BBC;
    int idx;
    int tag[2];

    if (s->f14C != 0)
        return;
    switch (s->f0) {
    case 0:
    case 1:
    case 2:
        return;
    case 3:
    case 4:
    case 5:
    case 6:
        idx = 0;
        if (s->f6F8 < 2)
            idx = 3;
        break;
    case 7:
    case 8:
    case 9:
    case 10:
        idx = s->f154 == 0 ? 2 : 1;
        break;
    }
    tag[0] = 0;
    tag[1] = 0;
    FUN_00179208((char *)s + 0x2881C, D_00215990[idx].p, D_00215990[idx].n, tag, 1);
}