// FUNCTION: SLPM 0x001C0570  size 120  core 120  (MISS 120/120 长度对，15 词)
// ROM 循环用 a0 当游标（addu a0,s0,i）、i 在循环头 i++，比较 sltu；我们把游标落在 v1、
// 且把 (u-'a') 的 andi 0xFF 多编了一条 → 需要更贴 ROM 的写法（i 先自增、地址重算）。
extern int FUN_001fc9d4(char *p);

void FUN_001c0570(char *p)
{
    int n = FUN_001fc9d4(p);
    int i;
    char c;
    unsigned char u;

    for (i = 0; i < n; i++) {
        c = p[i];
        if (c == '/')
            p[i] = '\\';
        u = p[i];
        if ((unsigned char)(u - 'a') < 26)
            p[i] = u - 0x20;
    }
}
