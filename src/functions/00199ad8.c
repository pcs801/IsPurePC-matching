// FUNCTION: SLPM 0x00199AD8  size 88  core 88
extern int FUN_00190578(void *p, int v, int x);
extern int FUN_001903d0(void *p, int w, int x);

int FUN_00199ad8(char *p, int v, int w, int x)
{
    int r = FUN_00190578(p, v, x);

    FUN_001903d0(p, w, x);
    return r;
}
