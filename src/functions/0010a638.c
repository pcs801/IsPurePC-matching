extern void FUN_001dcd50(void *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern void FlushCache(int a);
extern void FUN_001dd010(void *p, void *dst);
extern void FUN_001dc850(int a, int b);

void FUN_0010a638(void *dst, int a1, int a2, int a3)
{
    int buf[28];
    int n;
    int cnt;
    int step;
    int i;
    int off;
    int t;

    n = 0x7FFF0 / (a2 * 4);
    cnt = a3 / n;
    step = n * a2 * 4;
    if (cnt > 0) {
        t = (a2 < 0) ? a2 : a2 + 63;
        off = 0;
        for (i = 0; i < a3 / n; i++) {
            FUN_001dcd50(buf, (short)a1, (short)(t >> 6), 0, 0, (short)off, (short)a2, (short)n);
            FlushCache(0);
            FUN_001dd010(buf, dst);
            off += n;
            dst = (char *)dst + step;
            FUN_001dc850(0, 0);
        }
    }
    t = (a2 < 0) ? a2 : a2 + 63;
    FUN_001dcd50(buf, (short)a1, (short)(t << 10), 0, 0, (short)(i * n), (short)a2, (short)(a3 % n));
    FlushCache(0);
    FUN_001dd010(buf, dst);
    FUN_001dc850(0, 0);
}
