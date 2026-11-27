// FUNCTION: SLPM 0x00112BF8  size 32
// ROM: lw v0,0xC(a0) ; blez v0,L ; nop ; lw v0,0xC(a0) ; addiu v0,-1 ; sw v0,0xC(a0) ; L: jr ra ; nop
// ee-gcc forwards the loaded field and never re-loads => 24/32 (6 words).
// Tried: int* temp, char* alias cast, -= 1, >= 1 - all single-load.

void FUN_00112bf8(int self)
{
    if (*(int *)(self + 0xC) > 0)
        *(int *)(self + 0xC) = *(int *)(self + 0xC) - 1;
}
