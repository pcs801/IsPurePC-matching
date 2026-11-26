// FUNCTION: SLPM 0x001F6718
void FUN_001f6718(unsigned int *p)
{
    p[4] = p[4] & 0xFFFFFFFEu;
    p[6] = 0;
}
