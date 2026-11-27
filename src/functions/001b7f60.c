// FUNCTION: SLPM 0x001B7F60  size 32  core 28
// ROM: addiu sp,-0x10 ; sd ra,0(sp) ; jal FUN_001b3f88 ; lw a0,4(a0) ; ld ra,0(sp) ; jr ra ; addiu sp,0x10
// do{...}while(0) blocks the sibling call (captain's t207 finding).

extern int FUN_001b3f88(int a0);

void FUN_001b7f60(int self)
{
    do {
        FUN_001b3f88(*(int *)(self + 4));
    } while (0);
}
