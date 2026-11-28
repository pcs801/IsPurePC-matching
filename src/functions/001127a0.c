// FUNCTION: SLPM 0x001127A0  size 48  core 48
extern char D_001B7E4F0[];
extern void FUN_00114770(void *a0, void *a1, int a2, int a3);

void FUN_001127a0(char *p, long long a1, long long a2, int a3, int t0)
{
    struct {
        long long a;
        long long b;
        int c;
        int d;
    } s;

    s.a = a1;
    s.b = a2;
    s.c = a3 - *(int *)(p + 72);
    s.d = t0;
    FUN_00114770(D_001B7E4F0, &s, a2, s.c);
}
