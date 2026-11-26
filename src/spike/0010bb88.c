// FUNCTION: SLPM 0x0010BB88  size 12
// lui $v0, 0x47 ; jr $ra ; addiu $v0, $v0, 0x7d10
// NOTE: addiu (not ori) means this is the address of a symbol at 0x00477D10.
extern int g_0010BB88;

int func_0010BB88(void) {
    return (int)&g_0010BB88;
}
