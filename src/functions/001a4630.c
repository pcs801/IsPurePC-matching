// FUNCTION: SLPM 0x001A4630  size 128  core 128  (MISS 128/128，21 词全是临时寄存器分配)
// 与 0x001A0EE8 / 0x001A45B0 同族：lw 0x1C 先、随后 0x0,0x4,0x8,0xC,0x10,0x14,0x18，每条 sll 4；
// ROM 用 t6/t3/t5/t4/t2/t1/t0/v1，我们总差 2~3 号 → local-alloc 置换墙（同族三只一致）。
extern void FUN_001a3920(int a0, int *buf);

void FUN_001a4630(int a0, int *p)
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
    FUN_001a3920(a0, buf);
}
