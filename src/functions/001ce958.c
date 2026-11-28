// FUNCTION: SLPM 0x001CE958  size 48  core 44
// D_0242F10 -= 1; if (D_0242F10 == 0) D_0242F08 = 0;  (the field is re-read, not cached)
extern int D_0242F10;
extern int D_0242F08;

void FUN_001ce958(void)
{
    D_0242F10 = D_0242F10 - 1;
    if (D_0242F10 == 0)
        D_0242F08 = 0;
}
