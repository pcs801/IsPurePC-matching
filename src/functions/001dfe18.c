// FUNCTION: SLPM 0x001DFE18  size 40
// sig: lui ; ori ; lui ; sd ; addiu ; sd ; sd ; jr ; sd ; nop
// 4 个 64 位字段写入 + 返回 2。
// 目标字节 == ee-gcc 2.96 在 -O2 -fno-schedule-insns2 下的产物；但 check-one 固定 -O2，
// sched2 会把 addiu $v0,$zero,2 从 sd $v1,8($a0) 之前挪到之后（仅这 2 word 互换）。
// 已穷举 24 种 store 排列 × 4 种返回写法、16 种源码形态、9 组编译选项，全部同为该 2 word 互换。
int FUN_001dfe18(unsigned long long *p)
{
    p[0] = 0x30000000;
    p[1] = 0xA001;
    p[2] = 0x20000000;
    p[3] = 0;
    return 2;
}
