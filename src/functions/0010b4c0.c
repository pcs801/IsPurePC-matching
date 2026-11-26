extern int FUN_001fd160(char *, void *);
extern int FUN_001fcde8(char *, int, int);
extern int FUN_001fad00(char *);

extern char D_002589C0[];
extern char D_00258970[];
extern char D_00258990[];

typedef struct { int a[7]; } T7;
typedef struct { int a[12]; } T12;

void FUN_0010b4c0(char *p)
{
    T7 l1;
    T12 l2;
    int *q;
    unsigned int i;
    char *s;

    *(int *)(p + 0x7E90) = -1;
    *(int *)(p + 0x7E94) = -1;
    *(int *)(p + 0x7E98) = -1;
    *(int *)(p + 0x7E9C) = -1;
    *(int *)(p + 0x7EA0) = -1;
    *(int *)(p + 0x7EA4) = -1;
    l1 = *(T7 *)D_00258970;
    l2 = *(T12 *)D_00258990;
    s = (char *)FUN_001fd160(p + 0x100, D_002589C0);
    if (s != 0) {
        s += 15;
        i = 0;
        q = l1.a;
        for (; i < 7; i++) {
            if (FUN_001fcde8(s, *q++, 3) == 0) {
                *(int *)(p + 0x7EA8) = i;
                break;
            }
        }
        s += 5;
        q = l2.a;
        *(int *)(p + 0x7E98) = FUN_001fad00(s);
        s += 3;
        for (i = 0; i < 12; i++) {
            if (FUN_001fcde8(s, *q++, 3) == 0) {
                *(int *)(p + 0x7E94) = i + 1;
                break;
            }
        }
        s += 4;
        *(int *)(p + 0x7E90) = FUN_001fad00(s);
        s += 5;
        *(int *)(p + 0x7E9C) = FUN_001fad00(s);
        s += 3;
        *(int *)(p + 0x7EA0) = FUN_001fad00(s);
        *(int *)(p + 0x7EA4) = FUN_001fad00(s + 3);
    }
}
