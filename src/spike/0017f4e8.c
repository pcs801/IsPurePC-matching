// FUNCTION: SLPM 0x0017F4E8  size 28
// set byte fields 0x14..0x18
void func_0017F4E8(char *s, int a1, int a2, int a3) {
    *(char *)(s + 0x17) = a3;
    *(char *)(s + 0x18) = -0x80;
    *(char *)(s + 0x15) = a1;
    *(char *)(s + 0x16) = a2;
    *(char *)(s + 0x14) = 0;
}
