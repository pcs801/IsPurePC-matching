// FUNCTION: SLPM 0x002037B0  size 48 (core 44)
// List unlink: slot = *(int*)(p + 0x4C) + node[1]*4; node[0] = *slot; *slot = node;
// Status: 44/44 bytes, 5 words off (register naming on the p+0x4C load).
void FUN_002037b0(int *p, int *node)
{
    int *slot;

    if (node == 0)
        return;
    slot = (int *)(p[19] + node[1] * 4);
    node[0] = *slot;
    *slot = (int)node;
}
