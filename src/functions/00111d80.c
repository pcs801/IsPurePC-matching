// FUNCTION: SLPM 0x00111D80  size 104  core 100
// 100/100 bytes, 3 words diff (word 20..22): target epilogue is
//   lw $a0,-0x7B4C($gp) ; ld $s0,0($sp) ; ld $ra,8($sp) ; j FUN_00112260 ; addiu $sp
// but ee-gcc 2.96 emits ld $ra ; lw $a0 ; ld $s0 ; j (restore order ra-before-s0).
extern int D_0026FEA4;
extern int FUN_001e9090(int, int, int, int, int, int, int);
extern void FUN_00112260(int);

void FUN_00111d80(char *p)
{
    FUN_001e9090(1, 0x80E0, 1, 0x13, *(int *)(p + 0x44),
                 *(int *)(p + 0x48) / 1024 * 1024,
                 *(int *)(p + 0x44) + *(int *)(p + 0x50));
    *(int *)p = 2;
    FUN_00112260(D_0026FEA4);
}
