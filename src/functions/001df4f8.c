// FUNCTION: SLPM 0x001DF4F8  size 32  core 28
// ROM: addiu sp,-0x10 ; sd ra,0(sp) ; jal FUN_001df538 ; ori a1,a1,0x2000 ; ld ra,0(sp) ; jr ra ; addiu sp,0x10
// do{...}while(0) blocks the sibling call (captain's t207 finding).

extern int FUN_001df538(int a0, int a1);

void FUN_001df4f8(int a0, int a1)
{
    do {
        FUN_001df538(a0, a1 | 0x2000);
    } while (0);
}
