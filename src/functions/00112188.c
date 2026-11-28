typedef struct { int a; int b; int c; int d; } S;

extern int FUN_00205c20(int a0);
extern int FUN_00208410(S *s, int a1);
extern int FUN_002057f0(int a0);

int FUN_00112188(int a0, int a1, int a2)
{
    S s;
    int r;

    if (a2 <= 0)
        return 0;
    s.a = a1;
    s.b = a0;
    s.c = a2;
    s.d = 0;
    FUN_00205c20(0);
    do {
        r = FUN_00208410(&s, 1);
    } while (FUN_002057f0(r) >= 0);
    return a2;
}
