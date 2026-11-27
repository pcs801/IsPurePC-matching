// FUNCTION: SLPM 0x001FAC30  size 24 (symbol appears TRUNCATED)
// ROM: addiu sp,-0x10 ; sd ra,0(sp) ; jal FUN_001fc120(a0=6) ; jal FUN_001002c8(a0=1)
// then 0x001FAC48 starts a NEW function (addiu sp,-0x20), so the 24-byte symbol has
// no epilogue - which a normal C function must have. Best effort below is 32/24
// (the extra ld ra / jr ra / addiu sp).

extern int FUN_001fc120(int a0);
extern int FUN_001002c8(int a0);

int FUN_001fac30(void)
{
    FUN_001fc120(6);
    return FUN_001002c8(1);
}
