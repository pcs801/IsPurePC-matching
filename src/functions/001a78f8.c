extern int FUN_001fc2a8(void *a0, int a1, int a2);
extern unsigned char *D_00270A10;

void FUN_001a78f8(int a0, unsigned char *out, int a2)
{
    unsigned char buf[0x100];
    unsigned char *p;
    unsigned char *q;
    unsigned char c;

    FUN_001fc2a8(buf, a2, a0);
    if (buf[0] == 0) {
        *out = 0;
        return;
    }
    p = buf;
    q = out;
    do {
        c = *p;
        if (c == 0x20) {
            q[0] = D_00270A10[0];
            q[1] = D_00270A10[1];
        } else if (c == 0x2B) {
            q[0] = D_00270A10[2];
            q[1] = D_00270A10[3];
        } else if (c == 0x2D) {
            q[0] = D_00270A10[4];
            q[1] = D_00270A10[5];
        } else {
            q[0] = 0x82;
            q[1] = c + 0x1F;
        }
        p++;
        q += 2;
    } while (*p != 0);
    *q = 0;
}
