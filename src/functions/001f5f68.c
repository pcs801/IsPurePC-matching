// FUNCTION: SLPM 0x001F5F68  size 40  (MISS 36/36, 4 words)
// ROM: addiu sp,-0x10 ; lui a0,0x27 ; sd ra,0(sp) ; jal FUN_00208450 ; addiu a0,a0,-0x1E40 ; ld ra ; v0=2 ; jr ra ; addiu sp
// ee-gcc hoists the `lui a0` before the frame setup (word 0 differs). Tried literal and local-return forms.

extern char D_0026E1C0[];
extern int FUN_00208450(char *p);

int FUN_001f5f68(void)
{
    do {
        FUN_00208450(D_0026E1C0);
    } while (0);
    return 2;
}
