// FUNCTION: SLPM 0x001b29d8  size 72  core 72
// ROM stores refcount then RELOADS it for the test (store-to-load not forwarded);
// -O2 forwards the value, so this is the closest expressible form (16 words off).
extern int D_0022E938;
extern char D_0022E950[];
extern void FUN_001fbb84(char *a0, int a1, int a2);

void FUN_001b29d8(void)
{
    D_0022E938 = D_0022E938 - 1;
    if (D_0022E938 == 0)
        FUN_001fbb84(D_0022E950, 0, 0xAC0);
}
