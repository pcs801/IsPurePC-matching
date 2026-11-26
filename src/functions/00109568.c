// FUNCTION: SLPM 0x00109568  size 376
extern char D_C56680[];
extern int D_00270C34;

extern void FUN_001dc850(int a, int b);
extern void FUN_001dcd50(void *buf, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern void FUN_001dd010(void *buf, void *dst);
extern void FUN_00205c20(int op);

void FUN_00109568(void)
{
    int buf[28];
    int i;
    char *prev = 0;
    char *cur;
    int off = 0;
    int s4;
    int j;

    FUN_001dc850(0, 0);
    s4 = (D_00270C34 * 35) << 23;
    cur = D_C56680;
    for (i = 3; i >= 0; i--) {
        FUN_001dcd50(buf, s4 >> 16, 10, 0, 0, (off << 20) >> 16, 0x280, 0x70);
        FUN_00205c20(0);
        FUN_001dd010(buf, cur);
        if (prev) {
            for (j = 0; j < 0x70; j++) {
                int n = 0x280;
                signed char *p = prev + j * 0xA00 + 3;
                do {
                    *p = -128;
                    p += 4;
                } while (--n >= 0);
            }
        }
        prev = cur;
        FUN_001dc850(0, 0);
        cur = prev + 0x46000;
        off += 7;
    }
}
