// FUNCTION: SLPM 0x00101700  size 88  core 84
// sig: addiu ; sd ; daddu ; sd ; sll ; addu ; sd ; sll ; lui ; addiu ; addu ; jal
// 未命中说明：目标在 sw s0,4(s1) 之后用同一条 addiu v0,zero,1 同时充当
// *(int*)p=1 的存储值与返回值；ee-gcc -O2 在本形状下把常量重物化两次
// （addiu v1,zero,1 存 + addiu v0,zero,1 返回），仅 -fno-schedule-insns 时才是单次。

extern int D_01B7423C;
extern int FUN_001fc8c0();

int FUN_00101700(int idx) {
    char *p = (char *)&D_01B7423C + ((idx << 6) + idx) * 8;
    FUN_001fc8c0(p + 8);
    *(int *)(p + 4) = idx;
    *(int *)p = 1;
    return 1;
}
