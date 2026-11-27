// FUNCTION: SLPM 0x001CC2D8  size 8  core 8
// jr ra / sw a1,0x20(a0)  (the following 0x1CC2E0..0x1CC304 slots are sibling getters/setters
// that splat merges into this 0x30 block: lw/ swc1/ lwc1 at +0x20/+0x24/+0x28)
void FUN_001cc2d8(char *p, int v)
{
    *(int *)(p + 0x20) = v;
}
