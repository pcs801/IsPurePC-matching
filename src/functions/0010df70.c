// FUNCTION: SLPM 0x0010DF70  size 152  core 152
// NOTE: target contains R5900 'sync' (0x0000000F) and 'ei' (0x42000038) at 0x0010DFF0/0x0010DFF4;
// plain C cannot emit them (no builtin available, and inline assembly is forbidden) so only the surrounding 144 bytes can match.

extern char D_B25E80[];
extern unsigned char D_A98DAD[];

extern int D_00270C08;
extern int D_00270C14;
extern int D_00270C2C;
extern int D_00270C34;
extern int D_00270C3C;
extern int D_00270C8C;

extern int FUN_001ddc08(void *, int);
extern int FUN_0010cac8(int, int);
extern int FUN_002059d0(int);
extern void FUN_00105af0(void);
extern void FUN_001b1ad8(int);

int FUN_0010df70(void)
{
    if (D_00270C14 == 1) {
        FUN_001ddc08(D_B25E80, D_00270C34);
        FUN_0010cac8(0xFF - D_A98DAD[0], D_00270C34);
        FUN_002059d0(D_00270C8C);
        D_00270C14 = 0;
    }
    D_00270C08 = D_00270C08 + 1;
    D_00270C2C = D_00270C2C + 1;
    D_00270C3C = D_00270C3C + 1;
    FUN_00105af0();
    FUN_001b1ad8(0);
    return 0;
}