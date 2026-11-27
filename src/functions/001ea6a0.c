// FUNCTION: SLPM 0x001EA6A0  size 56 (core 52)
// Indexes a 12-byte-stride array at *(char**)(p+0x40) and stores three words.
void FUN_001ea6a0(char *p, int i, int v, int w)
{
    char *e = *(char **)(p + 0x40) + i * 12;

    *(int *)(e + 12) = v;
    *(int *)(e + 16) = w;
    *(int *)(e + 20) = 0;
}
