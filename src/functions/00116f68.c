// FUNCTION: SLPM 0x00116F68  size 48  (MISS 52/48, 4 words)
// ROM: addiu sp ; v0=*(gp-0x6D44) ; sd ra ; a0<<=2 ; a0+=v0 ; jal FUN_0019d8d8 (a0=*(int*)(a0+0x444)) ;
//      v1=3 ; ld ra ; sb v1,0xD(v0) ; j FUN_00117738 ; addiu sp
// 4 bytes too long: ee-gcc materialises an extra register copy before the sb.

extern char *D_00270CAC;
extern char *FUN_0019d8d8(int a0);
extern int FUN_00117738(char *p);

int FUN_00116f68(int idx)
{
    char *p;

    p = FUN_0019d8d8(*(int *)(D_00270CAC + idx * 4 + 0x444));
    p[0xD] = 3;
    return FUN_00117738(p);
}
