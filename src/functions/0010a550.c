extern long long D_B25E80[];
extern int D_1BA0D50[];
extern int FUN_001dfdc8(void *p, int n);
extern void FUN_001de1a8(int a, int b, void *c);

void FUN_0010a550(int a0)
{
    int pkt;
    int n;

    pkt = *(int *)D_1BA0D50[3];
    n = FUN_001dfdc8((void *)pkt, 1);
    *(long long *)(pkt + 0x28) = D_B25E80[27];
    *(long long *)(pkt + 0x20) = D_B25E80[26];
    FUN_001de1a8(D_1BA0D50[2], a0, (void *)pkt);
    *(int *)D_1BA0D50[3] = *(int *)D_1BA0D50[3] + (n << 4);
}
