// FUNCTION: SLPM 0x001F6858  size 40  (MISS 36/36, 2 words)
// ROM: addiu sp ; a3=0x800 ; sd ra ; t0=0x2000 ; jal FUN_001f6880 ; t1=0x20 ; ld ra ; jr ra ; addiu sp
// ee-gcc groups the two constants before `sd ra` (word 2 differs).

extern int FUN_001f6880(int a0, int a1, int a2, int a3, int a4, int a5);

void FUN_001f6858(int a0, int a1, int a2)
{
    do {
        FUN_001f6880(a0, a1, a2, 0x800, 0x2000, 0x20);
    } while (0);
}
