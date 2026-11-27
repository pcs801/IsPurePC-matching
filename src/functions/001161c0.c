// FUNCTION: SLPM 0x001161C0  size 1048  core 1044
extern unsigned char *D_00270CAC;
extern unsigned char D_A94700[];

typedef struct { unsigned char b[0x200]; } Blob;

void FUN_001161c0(void)
{
    Blob *src = (Blob *)D_00270CAC;
    Blob *dst = (Blob *)D_A94700;
    int i;

    *dst = *src;
    for (i = 0xF; i >= 0; i--)
        dst->b[0x40 + i] |= src->b[0x200 + i];
}
