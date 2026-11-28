// FUNCTION: SLPM 0x001A0EE8  size 128  core 128  (MISS 128/128，21 词全是临时寄存器分配)
// 指令序列与 ROM 完全同序（lw 0x1C 先、随后 0x0,0x4,...），只差临时寄存器编号
// （ROM t5/t2/t4/t3/t1/t0/a3/v1）。判 local-alloc 置换墙。
extern void FUN_001a02a8(int *buf);

void FUN_001a0ee8(int *p)
{
    int buf[8];

    buf[0] = p[0] << 4;
    buf[1] = p[1] << 4;
    buf[2] = p[2] << 4;
    buf[3] = p[3] << 4;
    buf[4] = p[4] << 4;
    buf[5] = p[5] << 4;
    buf[6] = p[6] << 4;
    buf[7] = p[7] << 4;
    FUN_001a02a8(buf);
}
