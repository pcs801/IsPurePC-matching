// FUNCTION: SLPM 0x001A45B0  size 128  core 128  (MISS 128/128，21 词全是临时寄存器分配)
// 与 0x001A0EE8 同族（第二参是数据指针、第一参原样透传给 FUN_001a3478）。
extern void FUN_001a3478(int a0, int *buf);

void FUN_001a45b0(int a0, int *p)
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
    FUN_001a3478(a0, buf);
}
