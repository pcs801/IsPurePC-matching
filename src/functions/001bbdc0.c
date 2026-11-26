// FUNCTION: SLPM 0x001BBDC0
signed char FUN_001bbdc0(void *self)
{
    return *(signed char *)((char *)self + 0x9);
}

signed char FUN_001bbdc0_b(void *self)
{
    return *(signed char *)((char *)self + 0xA);
}

void FUN_001bbdc0_c(void *self, int value)
{
    *(int *)((char *)self + 0x10) = value;
}

void FUN_001bbdc0_d(void *self, int index, int value)
{
    *(int *)((char *)self + index * 4 + 0x14) = value;
}

void FUN_001bbdc0_e(void *self, int value)
{
    *(int *)((char *)self + 0x2C) = value;
}
