// FUNCTION: SLPM 0x0010A818  size 520  core 516
extern int FUN_001dcd50(void *, short, short, int, int, short, short, short);
extern void FlushCache(int);
extern int FUN_001dd010(void *, void *);
extern int FUN_001dc850(int, int);
extern void FUN_001093d0(int, void *, int, int, int);

void FUN_0010a818(int id, void *data, int a2, int width, int height)
{
    char st[0x70];
    int w;
    int chunk;
    int i;
    int pos;

    w = 0x7FFF0 / (width * 4);
    chunk = w * width * 4;
    pos = 0;
    for (i = 0; i < height / w; i++) {
        FUN_001dcd50(st, (short)a2, (short)(width / 64), 0, 0, (short)pos, (short)width, (short)w);
        FlushCache(0);
        FUN_001dd010(st, data);
        data = (char *)data + chunk;
        FUN_001dc850(0, 0);
        pos += w;
    }
    FUN_001dcd50(st, (short)a2, (short)((width << 10) / 65536), 0, 0, (short)(i * w), (short)width, (short)(height % w));
    FlushCache(0);
    FUN_001dd010(st, data);
    FUN_001dc850(0, 0);
    FUN_001093d0(id, data, width, height, 0);
}
