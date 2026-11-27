// FUNCTION: SLPM 0x00168A90  size 2536 (g=8, needs_G8) - block-by-block reconstruction
// Block 1 (0x168A90-0x168C28, prologue + dispatch) and block 2 (0x168C28-0x168DB0, case 0)
// are transcribed; blocks 3..10 still return early.
extern void *D_00270BF4;          /* gp-28156 global pointer */
extern int FUN_001a8250(void);
extern void FUN_0019f308(int a, int b);
extern void FUN_00176168(void *p, void *st, int c, int d);
extern void FUN_00176888(void *p, void *st, int c, int d);
extern void FUN_00173950(void *p, int a, void *b, int c, int d);

struct St {
    int x0;
    int x1;
    int pad0[10];
    int x30;
    int x34;
    int pad1[2];
    int x40;
    int pad2[13];
    int x60;
    int x64;
    int x68;
    int x6C;
};

int FUN_00168a90(int idx)
{
    struct St st;
    char *base = D_00270BF4;
    char *e = (char *)0x00218858 + idx * 0x1C;
    char *s6 = (char *)0x00218858 + idx * 0x1C;
    char buf[64];
    int n;
    int s2 = 0;
    int s3 = 0;
    int i;
    int a1;

    FUN_001a8250();
    FUN_0019f308(0, 0);
    st.x1 = 32;
    st.x68 = 0;
    st.x0 = (512 - *(int *)(base + 0x31380)) / 2 + 64;
    FUN_00176168(base + 0x31168, &st, 0, 10);
    n = *(int *)(e + 4);
    if (n >= 11) {
        st.x64 = 6;
        st.x68 = 1;
        s2 = *(int *)(base + 0x311E4);
    }
    if (n <= 0)
        return 0;
    for (;;) {
        int kind = *(int *)(*(int *)(s6 + 8) + s2 * 16);

        if (kind != 0)
            return 0;
        {
            int v1 = *(int *)(*(int *)(s6 + 8) + s2 * 16 + 4);
            int s0 = 1;
            char *p = buf + 32;

            if (v1 == 0) {
                s3 = 0;
            } else if (v1 > 0) {
                s3 = 1;
            } else {
                s3 = 2;
                v1 = -v1;
            }
            do {
                int q = v1 / s0;
                int d = q % 10;

                s0 = s0 * 10;
                *p++ = (char)d;
            } while (s0 < 10000);
            st.x30 = st.x0;
            st.x34 = st.x1;
            for (i = 0; i < 10; i++) {
                a1 = *(signed char *)(buf + 32 + i);
                if (a1 == -1) {
                    if (s3 == 1)
                        return 0;
                    FUN_00173950((void *)0x00218028, s3 + 10, &st.x30, 0, 10);
                    break;
                }
                FUN_00173950((void *)0x00218028, a1, &st.x30, 0, 10);
                st.x30 -= 20;
            }
            s2++;
        }
    }
}
