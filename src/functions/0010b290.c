extern void FUN_001fbb84(void *, int, int);
extern int FUN_001aa1a0(void *, void *, int, void *, int, int, int);
extern int FUN_001aa260(void *, void *, void *, int, void *);
extern int FUN_001aa3c0(void *, void *, void *);
extern int FUN_001aa430(void *, void *, int, int);
extern int FUN_001aa698(void *, void *, int, void *, int, void *, int);
extern int FUN_001fc4c0(void *, void *);
extern int FUN_001fc9d4(void *);
extern int FUN_0010baa8(void *);
extern void FUN_0010bf68();
extern void FUN_0010be90();

extern char D_46CC40[];
extern char D_477C40[];
extern char D_002587C8[];
extern char D_0026FD60[];
extern char D_002586F8[];
extern char D_00258808[];
extern char D_00258828[];
extern char D_00258850[];
extern char D_00258870[];
extern char D_00258888[];
extern char D_0026FD68[];
extern char D_0026FD70[];

typedef struct {
    int d;
    unsigned short w;
} HDR;

int FUN_0010b290(char *p, int a1, int a2)
{
    int r;
    HDR *h;

    FUN_001fbb84(p, 0, 0x40);
    *(int *)p = 1;
    *(int *)(p + 4) = -1;
    r = FUN_001aa1a0(D_477C40, D_46CC40, 0, p + 8, a1, 0, 0);
    if (r < 0) {
        FUN_0010bf68(D_002587C8, D_0026FD60, 0x2E4, a1, r);
    }
    *(int *)(p + 0x18) = 0x50;
    r = FUN_001aa260(D_477C40, D_46CC40, p + 0x100, 0x80, p + 8);
    if (r < 0) {
        FUN_0010bf68(D_002586F8, r);
    }
    FUN_0010be90(D_00258808, a1, p + 0x100);
    r = FUN_001aa3c0(D_477C40, D_46CC40, p);
    *(int *)(p + 0x7E78) = r;
    if (r < 0) {
        FUN_0010bf68(D_00258828, D_0026FD60, 0x2F0, r);
    }
    r = FUN_001aa430(D_477C40, D_46CC40, *(int *)(p + 0x7E78), -1);
    if (r < 0) {
        FUN_0010be90(D_00258850, r);
        FUN_0010baa8(p);
        return 1;
    }
    h = (HDR *)D_0026FD68;
    *(int *)(p + 0x80) = h->d;
    *(unsigned short *)(p + 0x84) = h->w;
    FUN_001fc4c0(p + 0x80, a2);
    FUN_001fc4c0(p + 0x80, D_00258870);
    FUN_001fc4c0(p + 0x80, a1);
    FUN_001fc4c0(p + 0x80, D_0026FD70);
    *(int *)(p + 0x7E80) = 0;
    r = FUN_001fc9d4(p + 0x80);
    r = FUN_001aa698(D_477C40, D_46CC40, *(int *)(p + 0x7E78), p + 0x80, r, p + 0x7E80, -1);
    if (r < 0) {
        FUN_0010be90(D_00258888, r);
        FUN_0010baa8(p);
        return 1;
    }
    *(int *)(p + 0x7E7C) = 0;
    return 0;
}
