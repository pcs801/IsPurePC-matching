// FUNCTION: SLPM 0x001C29D8
long long FUN_001c29d8(unsigned char *self)
{
    long long limit = (long long)*(int *)(self + 0x28) << 11;
    long long value = *(long long *)(self + 8);
    if ((unsigned long long)value < (unsigned long long)limit)
        limit = value;
    return limit >> 32;
}
