// FUNCTION: SLPM 0x001ADE60  size 152  core 148  (MISS 132/148, 33 词)
// 7 参转发（第 4~7 参是栈上 int buf[4] 的 &buf[0..3]）。ROM 帧 -0x30：buf@0x0-0xF、s0@0x10、
// s1@0x18、ra@0x20；我们只出 -0x20 且 s0/s1 绑定对调（ROM s1=a0/s0=a1）→ 未过。
extern int FUN_001af250(int a0, int a1, int a2, int *a3, int *a4, int *a5, int *a6);
extern int FUN_001af428(void);
extern void FUN_001b4568(int a0, int a1, int a2, int a3);

int FUN_001ade60(int a0, int a1, int a2)
{
    int buf[4];
    int r;

    if (FUN_001af250(a1, a2, 0, &buf[0], &buf[1], &buf[2], &buf[3]) < 0)
        return -3;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x30) = buf[0];
    *(int *)(a0 + 0x2C) = buf[1];
    r = FUN_001af428();
    *(int *)(a0 + 0xC) = buf[2];
    FUN_001b4568(*(int *)(a0 + 4), r, *(int *)(a0 + 0x30), buf[1]);
    return 0;
}
