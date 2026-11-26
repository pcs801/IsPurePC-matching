// FUNCTION: SLPM 0x00123788  size 12
// lw $v0, -0x6d40($gp) ; jr $ra ; sw $a0, 8($v0)
extern int *g_00123788;

void func_00123788(int x) {
    *(int *)((char *)g_00123788 + 8) = x;
}
