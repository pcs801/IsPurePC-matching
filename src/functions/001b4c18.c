// FUNCTION: SLPM 0x001B4C18  size 16  core 24
// Target: bltzl $a1,$L / lw $v0,0x18($a0) / jr $ra / sw $a1,0x34($a0) / $L: jr ra / sw $v0,0x34($a0)
// i.e. p->f34 = (v >= 0) ? v : p->f18, written as an early return so both paths keep
// their own jr ra + sw (plain if/else or ternary collapse into a single 4-insn tail).
void FUN_001b4c18(char *p, int v)
{
    if (v >= 0) {
        *(int *)(p + 0x34) = v;
        return;
    }
    *(int *)(p + 0x34) = *(int *)(p + 0x18);
}
