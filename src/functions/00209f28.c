// FUNCTION: SLPM 0x00209F28  size 56  core 56
extern int FUN_00209d08(void *p);
extern void FUN_00209d60(int r);
extern void FUN_002058c0(void);

void FUN_00209f28(char *p)
{
    for (;;) {
        int r = FUN_00209d08(p);

        if (r != 0)
            FUN_00209d60(r);
        else
            FUN_002058c0();
    }
}
