extern char D_A94700[];
extern int D_00270C74;
extern void FUN_0010da70(unsigned char);

void FUN_00104ed0(int v)
{
    char *p = D_A94700;
    *(unsigned char *)(p + 0x46B2) = v;
    if (D_00270C74 == v)
        return;
    FUN_0010da70(*(unsigned char *)(p + 0x46B2));
}
