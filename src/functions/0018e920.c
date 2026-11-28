// FUNCTION: SLPM 0x0018E920  size 88  core 88
extern void FUN_001e49e0(void *p, int v, int w);
extern void FUN_001e4d90(void *p, void *q, int v);
extern void FUN_001e4768(void *p, void *q, int w);

void FUN_0018e920(char *p, int v, int w)
{
    FUN_001e49e0(p, v, w);
    FUN_001e4d90(p, p, v);
    FUN_001e4768(p, p, w);
}
