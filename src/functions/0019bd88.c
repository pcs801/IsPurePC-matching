int FUN_0019bd88(unsigned short a0)
{
    unsigned int u = (0xDBDF + (unsigned int)a0) & 0xFFFF;

    if ((a0 & 0xFF00) != 0) {
        if (u >= 83) {
            a0 = 127;
            return a0 & 0xFF;
        }
        a0 = (0xDC5F + 127) & 0xFFFF;
    }
    return a0 & 0xFF;
}
