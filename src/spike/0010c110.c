// FUNCTION: SLPM 0x0010C110  size 8
// jr $ra ; sw $a0, -0x6f30($gp)
extern int g_0010C110;

void func_0010C110(int x) {
    g_0010C110 = x;
}
