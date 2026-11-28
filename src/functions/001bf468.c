// FUNCTION: SLPM 0x001BF468  size 76  core 76
extern char D_00230569[];
extern int FUN_001bf388(void);
extern int FUN_001bf3c8(void);

int FUN_001bf468(void)
{
    signed char v = *(signed char *)D_00230569;

    if (v == 1)
        return FUN_001bf388() << 1;
    if (v == 2)
        return FUN_001bf3c8();
    return 0;
}
