extern int D_0026FC58[];
extern int D_0026FC60[];
extern int D_0026FC68[];
extern int FUN_001a78f8(int, void *, void *);
extern int FUN_001fc8c0(void *, void *);
extern int FUN_001fc4c0(void *, void *);

void FUN_00105e38(int ticks, void *txt)
{
    char buf[0x100];
    int v;

    v = ticks / 216000;
    FUN_001a78f8(v % 100, buf, D_0026FC58);
    FUN_001fc8c0(txt, buf);
    FUN_001fc4c0(txt, D_0026FC60);
    v = ticks / 3600;
    FUN_001a78f8(v % 60, buf, D_0026FC68);
    FUN_001fc4c0(txt, buf);
    FUN_001fc4c0(txt, D_0026FC60);
    v = ticks / 60;
    FUN_001a78f8(v % 60, buf, D_0026FC68);
    FUN_001fc4c0(txt, buf);
}
