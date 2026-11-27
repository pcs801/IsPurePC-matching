// FUNCTION: SLPM 0x00111070  size 424  core 420

extern int D_1BA0D50[];

extern int FUN_001dfc38(void *, int);
extern int FUN_001e0300(void *, void *, int, int);
extern int FUN_001dfa58(void *);
extern int FUN_001dfe68(void *, void *, void *, int);
extern void FUN_001de1a8(int, int, void *);

typedef struct {
    unsigned short f0;
    unsigned short f2;
    unsigned short f4;
    unsigned short f6;
    unsigned short f8;
    unsigned short fA;
    unsigned short fC;
    unsigned short fE;
    unsigned short f10;
    unsigned short pad[7];
    int f20;
} Pkt;

void FUN_00111070(int a0, int a1, int a2, int a3)
{
    Pkt p;
    int pkt;
    int n;
    int i;

    pkt = *(int *)D_1BA0D50[3];
    p.f0 = 0x2BC0;
    p.f2 = 0xA;
    p.f4 = 0;
    p.f6 = 0;
    p.f8 = 0;
    p.fA = 0x280;
    p.fC = 0x1E0;
    p.fE = 0;
    p.f10 = 0;
    p.f20 = a2 >> 4;
    FUN_001dfc38((void *)pkt, 0);
    n = FUN_001e0300((void *)pkt, &p, D_1BA0D50[11], D_1BA0D50[12]);
    FUN_001de1a8(D_1BA0D50[2], a3, (void *)pkt);
    *(int *)D_1BA0D50[3] = *(int *)D_1BA0D50[3] + (n << 4);

    p.f0 = 0x2BC0;
    p.f2 = 0xA;
    p.f4 = 0;
    p.f6 = 0;
    p.f8 = 0;
    p.fA = 0x10;
    p.fC = a2;
    p.fE = 0;
    p.f10 = 0;

    for (i = 0; i < (a1 >> 4); i++) {
        p.f6 = i * 16;
        pkt = *(int *)D_1BA0D50[3];
        FUN_001dfa58((void *)pkt);
        n = FUN_001dfe68((void *)pkt, &p, (void *)a0, 0);
        FUN_001de1a8(D_1BA0D50[2], a3, (void *)pkt);
        *(int *)D_1BA0D50[3] = *(int *)D_1BA0D50[3] + (n << 4);
        a0 += p.f20 << 10;
    }
}
