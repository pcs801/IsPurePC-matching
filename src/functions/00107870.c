// FUNCTION: SLPM 0x00107870
extern void *FUN_00100fc8(int, void *, void *, void *);
extern void *FUN_00101aa8(void *);
extern void FUN_00107910(void);
extern void FUN_001067b8(void *);
extern void FUN_00106268(void);
extern int FUN_0010bd80(unsigned int cmd, void *arg);
extern void FUN_00107990(int code);
extern unsigned char D_00281502;
extern unsigned int D_456490[16];

void FUN_00107870(void *a0, void *a1)
{
    void *p;

    p = FUN_00101aa8(FUN_00100fc8(4, a0, (void *)0, a1));
    FUN_00107910();
    FUN_001067b8(p);
    FUN_00107910();
    D_00281502 = 1;
    FUN_00106268();
    D_456490[8] = FUN_0010bd80(0x8040, (void *)0);
    D_456490[9] = FUN_0010bd80(0x8030, (void *)0);
    D_456490[10] = FUN_0010bd80(0x8010, (void *)0);
    FUN_00107990(-1);
}
