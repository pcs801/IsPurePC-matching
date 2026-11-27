// FUNCTION: SLPM 0x0010A3D0  size 160
// sig: addiu ; addiu ; sd ; addiu ; sd ; and ; sd ; lui ; sd ; daddu ; sd ; addiu
// worker cracker-3; verified byte-exact

extern int D_1BA0D50[];
extern int FUN_001dfdc8(void *p, int n);
extern void FUN_001de1a8(int a, int b, void *c);

void FUN_0010a3d0(int a0)
{
    long long unknown;
    long long w;
    int pkt;
    int n;

    pkt = *(int *)D_1BA0D50[3];
    w = unknown & ~0x3;
    w &= ~0xC;
    n = FUN_001dfdc8((void *)pkt, 1);
    *(long long *)(pkt + 0x28) = 8;
    *(long long *)(pkt + 0x20) = w;
    FUN_001de1a8(D_1BA0D50[2], a0, (void *)pkt);
    *(int *)D_1BA0D50[3] = *(int *)D_1BA0D50[3] + (n << 4);
}
