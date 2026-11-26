extern int FUN_0010b290(char *, void *, int);
extern int FUN_0010b6a8(char *);
extern int FUN_001fbad4(int, int, int);
extern int FUN_001aa478(char *, char *, int, int);
extern int FUN_0010be90();

extern int D_1B76300[];
extern int D_477C40[];
extern int D_46CC40[];
extern char D_00258908[];
extern char D_00258928[];

typedef struct { unsigned int lo, hi; } QW;
typedef struct { QW a, b, c; unsigned int d; } BIG28;

typedef struct {
    int f00;
    int f04;
    int f08;
    BIG28 f0C;
    int f28;
    int f2C;
    int f30;
    int f34;
} OUT;

int FUN_0010b858(char *p0, int a1, char *dst, OUT *out)
{
    char *start = dst;
    int total = 0;
    int cur = 0;
    int r;
    int ret;

    FUN_0010b290((char *)D_1B76300, p0, a1);
    do {
        r = FUN_0010b6a8((char *)D_1B76300);
        if (out == 0) {
            FUN_001fbad4((int)dst, D_1B76300[0x7EB4 / 4], D_1B76300[0x7EB8 / 4]);
            dst += D_1B76300[0x7EB8 / 4];
            total += D_1B76300[0x7EB8 / 4];
        } else {
            FUN_001fbad4((int)dst, (int)((char *)D_1B76300 + 0x100), D_1B76300[0x7E88 / 4]);
            if (D_1B76300[0x7EAC / 4] != 0)
                cur = D_1B76300[0x7EB0 / 4];
            dst += D_1B76300[0x7E88 / 4];
            total += D_1B76300[0x7E88 / 4];
        }
    } while (r == 0);

    ret = FUN_001aa478((char *)D_477C40, (char *)D_46CC40, D_1B76300[0x7E78 / 4], -1);
    if (ret < 0)
        FUN_0010be90(D_00258908, ret);
    else
        FUN_0010be90(D_00258928);

    if (out != 0) {        out->f00 = D_1B76300[0x7E84 / 4];
        out->f04 = total;
        out->f28 = (int)start;
        out->f08 = D_1B76300[0x7E8C / 4];
        out->f30 = (int)(start + cur);
        out->f0C = *(BIG28 *)((char *)D_1B76300 + 0x7E90);
        out->f2C = cur;
        out->f34 = total - cur;
    }
    return total;
}
