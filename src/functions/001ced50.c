// FUNCTION: SLPM 0x001CED50  size 128  core 128  (MISS 124/128, 27 词)
// ROM 是三条独立字节交换（第一处 or 后 andi 0xFFFF、第三处 sll 后 and 0xFF00），我们合成形不同。
// 留档：三段 swap 的掩码位置必须分别照 ROM 写，不能统一成一种。
int FUN_001ced50(unsigned short *p, int n, unsigned short *out)
{
    if (n < 0x12)
        return -1;
    if ((unsigned short)((*p << 8) | (*p >> 8)) != 0x8000)
        return -2;
    if ((short)(((p[1] << 8) & 0xFF00) | (p[1] >> 8)) < 0xE)
        return -1;
    *out = ((p[8] << 8) & 0xFF00) | (p[8] >> 8);
    return 0;
}
