// FUNCTION: SLPM 0x001241D0
extern int *D_00270CB0;

signed char FUN_001241d0(void) {
    int *a0 = D_00270CB0;
    int v0 = *a0;
    int v1 = v0 + v0;
    v1 = v1 + v0;
    v1 = v1 << 10;
    v1 = v1 - v0;
    v1 = v1 << 3;
    return *(signed char *)((char *)(v1 + (int)a0) + 0x18);
}
