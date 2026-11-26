// FUNCTION: SLPM 0x00107618
extern unsigned char D_281580[];
extern int FUN_001b64c8(int a0, void *a1, int a2);

void FUN_00107618(void) {
    int i;
    for (i = 0; i < 6; i++) {
        unsigned char *p = D_281580 + i * 0x4E280;
        unsigned char *q = D_281580 + 0x80 + i * 0x4E280;
        p[0] = 0;
        p[1] = 0x80;
        p[2] = 0;
        p[3] = 0;
        *(int *)(p + 4) = FUN_001b64c8(2, q, 0x4B1E4);
    }
}
