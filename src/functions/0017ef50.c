// FUNCTION: SLPM 0x0017EF50  size 48  (MISS 48/48, 3 words)
// ROM: addiu sp ; a0=640 ; sd ra ; jal FUN_0017f3f0 (a1=480) ; jal FUN_0017e488 ; ld ra ;
//      a0=0x8604D0 ; j FUN_0017f548 ; addiu sp
// ee-gcc hoists the `lui a0,0x86` of the tail call before `ld ra` (word 7).

extern int FUN_0017f3f0(int a0, int a1);
extern int FUN_0017e488(void);
extern int FUN_0017f548(char *p);

int FUN_0017ef50(void)
{
    FUN_0017f3f0(640, 480);
    do {
        FUN_0017e488();
    } while (0);
    return FUN_0017f548((char *)0x8604D0);
}
