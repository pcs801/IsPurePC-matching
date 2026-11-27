// FUNCTION: SLPM 0x0010A470  size 224  core 220
// sig: lw ; addiu ; srl ; sd ; sd ; andi ; daddu ; addiu ; sd ; sd ; sd ; sd
// worker cracker-3; verified byte-exact (g=8)

extern long long D_B25E80[];
extern int D_00270C34;
extern int D_1BA0D50[];
extern int FUN_001dfdc8(void *p, int n);
extern void FUN_001de1a8(int a, int b, void *c);

void FUN_0010a470(unsigned int a0, int a1)
{
    long long v;
    int pkt;
    int n;

    if (D_00270C34 == 0)
        v = D_B25E80[12];
    else
        v = D_B25E80[58];
    if (a0 != 0xFFFFFFFFu) {
        v &= ~0x1FF;
        v |= (a0 >> 13) & 0x1FF;
    }
    pkt = *(int *)D_1BA0D50[3];
    n = FUN_001dfdc8((void *)pkt, 1);
    *(long long *)(pkt + 0x28) = D_B25E80[13];
    *(long long *)(pkt + 0x20) = v;
    FUN_001de1a8(D_1BA0D50[2], a1, (void *)pkt);
    *(int *)D_1BA0D50[3] = *(int *)D_1BA0D50[3] + (n << 4);
}
