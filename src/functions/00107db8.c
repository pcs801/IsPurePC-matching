extern char D_00281580[];
extern int FUN_001b7090(int);
extern unsigned int FUN_001b77e0(int);
extern unsigned int FUN_001b7868(int);

struct Blk {
    char pad[3];
    unsigned char flag;
    int val;
};

int FUN_00107db8(int idx)
{
    unsigned int v;

    if (((struct Blk *)(D_00281580 + idx * 0x4E280))->flag == 0)
        return -1;
    v = FUN_001b7090(((struct Blk *)(D_00281580 + idx * 0x4E280))->val);
    switch (v) {
    case 0:
    case 1:
    case 6:
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        return 48 * FUN_001b77e0(((struct Blk *)(D_00281580 + idx * 0x4E280))->val) /
               (FUN_001b7868(((struct Blk *)(D_00281580 + idx * 0x4E280))->val) / 1000);
    }
    return -1;
}
