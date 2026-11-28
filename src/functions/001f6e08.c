// FUNCTION: SLPM 0x001F6E08  size 112  core 112  (MISS 116/112, 25 词)
// ROM 帧 -0x40：s0@0x0 / s1@0x10 / s2@0x20 / ra@0x30（16 字节一槽），我们压到 -0x20；
// 属"帧布局墙"（同 0x0020A1D0），按队长跳过规则本应跳过，留档备查。
extern char D_00255EA8[];
extern char D_0026E3F0[];
extern int FUN_0020ac78(char *path, int flags);
extern int FUN_0020b2c0(int fd, char *buf, int len);
extern int FUN_0020af08(int fd);

char *FUN_001f6e08(void)
{
    if (D_00255EA8[0] == 0) {
        int h = FUN_0020ac78(D_0026E3F0, 1);
        if (h >= 0) {
            FUN_0020b2c0(h, D_00255EA8, 0xE);
            FUN_0020af08(h);
        }
    }
    return D_00255EA8;
}
