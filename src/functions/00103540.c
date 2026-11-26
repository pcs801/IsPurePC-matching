// FUNCTION: SLPM 0x00103540  size 152
typedef struct Rec {
    int ptr;
    unsigned short u4;
    unsigned short u6;
    unsigned short u8;
    unsigned short uA;
    unsigned char bC;
    unsigned char bD;
    unsigned char bE;
    unsigned char bF;
} Rec;

typedef struct GsW2 {
    char pad0[0x6B94];
    Rec *tbl;
    int cnt;
} GsW2;

extern GsW2 D_B1EC00;
extern Rec D_B25A30[];
void FUN_00103540(int delta)
{
    Rec *in;
    Rec *out;
    int i;
    int nv;
    in = D_B1EC00.tbl;
    i = 0;
    if (in->ptr != 0) {
        out = D_B25A30;
        for (i = 0; i < 0x40 && in->ptr != 0; i++) {
            nv = delta + in->ptr;
            out->ptr = nv;
            in->ptr = nv;
            out->u4 = in->u4;
            out->u6 = in->u6;
            out->u8 = in->u8;
            out->uA = in->uA;
            out->bC = in->bC;
            out->bD = in->bD;
            out->bE = in->bE;
            in++;
            out++;
        }
    }
    D_B1EC00.cnt = i;
}