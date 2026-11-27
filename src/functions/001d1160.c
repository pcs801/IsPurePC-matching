// FUNCTION: SLPM 0x001D1160  size 32
// ROM: lb v1,0x1A5(a0) ; beqz v1,ret0 ; v0=0 ; lw v0,0x1E8(a0) ; jr ra ; nop
// then 0x001D1178: jr ra ; v0 = 0x10  (unreachable from the only path)
// The 32-byte symbol carries 8 bytes of dead code => 24/32.

int FUN_001d1160(int self)
{
    if (*(signed char *)(self + 0x1A5) == 0)
        return 0;
    return *(int *)(self + 0x1E8);
}
