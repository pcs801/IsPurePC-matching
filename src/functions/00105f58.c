// FUNCTION: SLPM 0x00105F58  size 88
// sig: addiu ; daddu ; sd ; lui ; addiu ; addiu ; sd ; jal ; daddu ; jal ; nop ; lui

extern char D_1B73FC0[];
extern unsigned int D_00B1EC00[4];
extern int D_00270C54;
extern void FUN_001fbb84(char *, int, int);
extern void FUN_00114a48(void);

int FUN_00105f58(void)
{
    unsigned int v;

    FUN_001fbb84(D_1B73FC0, 0, 0x1EC);
    FUN_00114a48();
    v = D_00B1EC00[0];
    *(unsigned int *)(D_1B73FC0 + 0xCC) = *(unsigned short *)(v + 2);
    D_00270C54 = 1;
    return 1;
}
