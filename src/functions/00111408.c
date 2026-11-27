// FUNCTION: SLPM 0x00111408  size 288  core 288
extern char D_1B7E4A8[];
extern char D_002591B8[];
extern void FUN_00112770(void *, int *, int *, int *, int *);
extern int FUN_00111528(void *, int, void *, int, void *, int, void *, int);
extern int FUN_001127a0(void *, long, long, int, int);
extern int FUN_00111218(void *);
extern void FUN_00112788(void *, int);

int FUN_00111408(int a0, char *a1, char *a2)
{
    int v0;
    int v1;
    int v2;
    int v3;
    unsigned int s3;
    unsigned int s1;
    unsigned int s0;
    int r;

    FUN_00112770(D_1B7E4A8, &v0, &v1, &v2, &v3);
    s3 = *(unsigned int *)(a1 + 8);
    s1 = *(unsigned int *)(a1 + 0xC);
    s0 = (unsigned int)a2 + *(unsigned int *)(a2 + 0x50008);
    s0 -= s3;
    if (s1 < s0)
        s0 = s1;
    s1 -= s0;
    r = FUN_00111528((void *)((v0 & 0x0FFFFFFF) | 0x20000000), v1,
                     (void *)((v2 & 0x0FFFFFFF) | 0x20000000), v3,
                     (void *)s3, (int)s0, a2, (int)s1);
    if (r > 0) {
        if (FUN_001127a0(D_1B7E4A8, *(long *)(a1 + 0x10), *(long *)(a1 + 0x18), v0, r) == 0)
            FUN_00111218(D_002591B8);
    }
    FUN_00112788(D_1B7E4A8, r);
    return r > 0;
}
