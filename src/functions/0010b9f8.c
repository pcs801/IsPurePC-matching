// FUNCTION: SLPM 0x0010B9F8  size 176  core 172
extern char D_477C40[];
extern char D_46CC40[];
extern char D_00258748[];
extern char D_00258770[];
extern char D_002587A0[];
extern int FUN_001aacd0(void *, void *, int);
extern int FUN_001aaf60(void *, void *);
extern int FUN_001aaea0(void *);
extern void FUN_0010bf68(char *, int);

void FUN_0010b9f8(void)
{
    int r;

    r = FUN_001aacd0(D_477C40, D_46CC40, 0);
    if (r < 0) {
        FUN_0010bf68(D_00258748, r);
    }
    r = FUN_001aaf60(D_477C40, D_46CC40);
    if (r < 0) {
        FUN_0010bf68(D_00258770, r);
    }
    r = FUN_001aaea0(D_477C40);
    if (r < 0) {
        FUN_0010bf68(D_002587A0, r);
    }
}
