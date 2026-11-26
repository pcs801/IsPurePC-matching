// FUNCTION: SLPM 0x001067B8
extern void FUN_00205c20(int op);
extern unsigned int FUN_00208690(void *desc, int n);
extern int FUN_00205d40(unsigned int handle);
extern int FUN_0010bd80(unsigned int cmd, void *arg);
extern unsigned int D_00270A84;
extern unsigned int D_00270A88;
extern unsigned int D_00270A94;
extern unsigned int D_456500[8];
extern unsigned int D_456490[16];

struct DmaDesc {
    void *ptr;
    unsigned int taddr;
    unsigned int size;
    unsigned int flags;
};

void FUN_001067b8(unsigned int *p)
{
    struct DmaDesc d[2];
    unsigned int h;

    d[0].ptr = (void *)(((((p[0] * 4 + 0x13) >> 4) + p[1]) << 4) + (unsigned int)p);
    d[0].taddr = D_00270A84;
    d[0].size = 0xE000;
    d[0].flags = 0;
    d[1].ptr = (void *)(((((p[0] * 4 + 0x13) >> 4) + p[2]) << 4) + (unsigned int)p);
    d[1].taddr = D_00270A88;
    d[1].size = 0x2000;
    d[1].flags = 0;
    FUN_00205c20(0);
    while ((h = FUN_00208690(d, 2)) == 0)
        ;
    while (FUN_00205d40(h) >= 0)
        ;

    d[0].ptr = (void *)(((((p[0] * 4 + 0x13) >> 4) + p[3]) << 4) + (unsigned int)p);
    D_456500[1] = D_00270A94;
    d[0].size = 0x1000;
    d[0].flags = 0;
    D_456500[2] = 0x1000;
    D_456500[3] = 0xD6000;
    d[0].taddr = D_00270A94;

    do {
        FUN_00205c20(0);
        while ((h = FUN_00208690(d, 1)) == 0)
            ;
        while (FUN_00205d40(h) >= 0)
            ;
        while (FUN_0010bd80(0x90E0, D_456500) < 0) {
            D_456490[11]++;
            while (FUN_0010bd80(0x80F0, D_456500) != 1)
                ;
        }
        while (FUN_0010bd80(0x80F0, D_456500) != 1)
            ;
        D_456500[3] = D_456500[3] + 0x1000;
        d[0].ptr = (void *)((char *)d[0].ptr + 0x1000);
    } while (D_456500[3] <= 0x196000);

    D_456500[0] = D_00270A88;
    D_456500[1] = D_00270A94;
    D_456500[2] = 0xC0000;
    D_456500[3] = 0xD6000;
    FUN_00205c20(0);
    D_456490[6] = FUN_0010bd80(0x90B1, D_456500);
    FUN_0010bd80(0xC1, (void *)0x3010);
    FUN_0010bd80(0xD1, (void *)0x100);
    D_456490[7] = FUN_0010bd80(0x80A0, (void *)D_00270A84);
}
