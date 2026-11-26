// FUNCTION: SLPM 0x001E4068  size 40  core 40
// sig: lw ; dsll32 ; dsra32 ; dsra32 ; sw ; addiu ; addiu ; sw ; jr ; sw
// 64-bit arg split into two 32-bit words; the *p++ / *p walk (rather than p[0]/p[1])
// is what makes gcc emit dsll32/dsra32 and the addiu v1,v0,4 pair.
// verified byte-exact (attempt 2).

void FUN_001e4068(int **a0, long long a1) {
    int *p = *a0;
    *p++ = (int)a1;
    *p = (int)(a1 >> 32);
    *a0 = p + 1;
}
