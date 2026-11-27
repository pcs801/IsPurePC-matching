extern int FUN_00209838(void *p, int a1, int a2, void *q, int a4, void *q2, int a6, int a7, int a8);
extern void FUN_001e61d0(int a0, int a1, int a2);
extern char D_866140[];

typedef struct {
    int cmd;
    int a;
    int b;
    int c;
    int d;
    int rsp;
    char pad[0x80 - 0x18];
} SifReq;

extern SifReq D_866380;

int FUN_001e6680(int a0, int a1, int a2, int a3)
{
    SifReq *q;

    q = &D_866380;
    q->cmd = 6;
    q->a = a0;
    q->b = a1;
    q->c = a2;
    q->d = a3;
    if (FUN_00209838(D_866140, 1, 0, q, 0x80, q, 0x80, 0, 0) < 0)
        return 0;
    if (q->rsp == 1)
        FUN_001e61d0(a0, a1, 2);
    return q->rsp;
}
