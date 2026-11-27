// FUNCTION: SLPM 0x00107D10  size 120  core 120
// Same 0x4E280-stride block table as FUN_00107DB8. jtbl_00268150 =
// [0]=ret0, [1..4]=ret1, [5]=[6]=ret0; values >= 7 (default) fall through to ret 1.

struct Blk {
    char pad[3];
    unsigned char flag;
    int val;
};

extern char D_281580[];
extern int FUN_001b7090(int);

int FUN_00107d10(int idx)
{
    struct Blk *p;
    unsigned int v;

    p = (struct Blk *)(D_281580 + idx * 0x4E280);
    if (p->flag == 0)
        return 0;
    v = FUN_001b7090(p->val);
    switch (v) {
    case 0:
    case 5:
    case 6:
        return 0;
    case 1:
    case 2:
    case 3:
    case 4:
        return 1;
    }
    return 1;
}
