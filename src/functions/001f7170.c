// FUNCTION: SLPM 0x001F7170  size 32  core 32
unsigned char FUN_001f7170(unsigned char a0)
{
    return a0 - (a0 >> 4) * 6;
}
