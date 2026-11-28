// FUNCTION: SLPM 0x001C7A90  size 48 core 44
extern int D_0023BBF0[];
extern int D_0023BBE8[];

void FUN_001c7a90(void)
{
    D_0023BBF0[0] = D_0023BBF0[0] - 1;
    if (D_0023BBF0[0] == 0)
        D_0023BBE8[0] = 0;
}
