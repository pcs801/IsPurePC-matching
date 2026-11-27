// FUNCTION: SLPM 0x002056D0  size 16  core 16
// The ROM is a RAW SYSCALL STUB:  addiu $v1,$zero,19 ; syscall ; jr $ra ; nop
// Plain C cannot emit the `syscall` instruction (asm is banned in this pipeline),
// so this function - and every other 16-byte syscall stub in the queue (361 entries
// flagged 'syscall', e.g. 0x001DBDC0, 0x002055E0, 0x00205680..0x00205700) - is
// unreachable for the byte-matching worker. Kept as a documented best-effort.

extern int syscall(int n);

int FUN_002056d0(void)
{
    return syscall(19);
}
