// FUNCTION: SLPM 0x00110598  size 20
// lw v1,0x48(a0); lw v0,0x54(a0); slt v0,v0,v1; jr; xori v0,v0,1
int func_00110598(char *s) {
    return *(int *)(s + 0x54) >= *(int *)(s + 0x48);
}
