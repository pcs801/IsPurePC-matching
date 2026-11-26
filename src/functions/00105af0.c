// FUNCTION: SLPM 0x00105AF0  size 160  core 156
extern char D_1B73FC0[];
extern char D_A94700[];
extern int D_00270C48;
extern int D_270C48;

void FUN_00105af0(void)
{
    unsigned char *p;
    unsigned int t;
    unsigned int x;

    p = D_1B73FC0;
    t = *(unsigned int *)(p + 0xEC);
    if (t + D_00270C48 <= 0xCDFE5FEu)
        x = t + D_270C48;
    else
        x = 0xCDFE5FFu;
    *(unsigned int *)(p + 0xEC) = x;

    p = D_A94700;
    t = *(unsigned int *)(p + 0x108E8);
    if (t + D_00270C48 <= 0xCDFE5FEu)
        *(unsigned int *)(p + 0x108E8) = t + D_270C48;
    else
        *(unsigned int *)(p + 0x108E8) = 0xCDFE5FFu;
}
