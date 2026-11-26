// FUNCTION: SLPM 0x001C29F8
int FUN_001c29f8(unsigned char *self)
{
    unsigned long long limit = (unsigned long long)*(int *)(self + 0x28) << 11;
    unsigned long long value = *(unsigned long long *)(self + 8);
    if (value < limit)
        limit = value;
    return (int)(limit & 0xFFFFFFFF);
}
