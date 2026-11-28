// FUNCTION: SLPM 0x001C7AD8  size 52  core 52
// Region = tail thunk (20 B) + pad + the thunk at 0x001C7AF0 (28 B).
extern void FUN_001cae20(void);
extern char D_00269030[];
extern void FUN_001d3398(void *a0);

void FUN_001c7ad8(void)
{
    FUN_001cae20();
}

void FUN_001c7af0(void)
{
    FUN_001d3398(D_00269030);
}
