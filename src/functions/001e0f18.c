// FUNCTION: SLPM 0x001E0F18  size 56  core 56
// NEAR-MISS 3 words: register split only - target keeps the 0x70000000 mask in $v1
// (`lui v1,0x7000` / `and v0,a1,v1`) while ee-gcc uses $v0 for it. Length and
// semantics match exactly at 56/56.
void FUN_001e0f18(int *a0, int a1)
{
    int v;

    if ((a1 & 0x70000000) == 0x70000000)
        v = (a1 & 0x8FFFFFFF) | 0x80000000;
    else
        v = a1 & 0x1FFFFFFF;
    a0[1] = v;
}
