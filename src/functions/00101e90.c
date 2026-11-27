// FUNCTION: SLPM 0x00101E90  size 376
// MISS: 376/376 bytes, 16 words differ. Body/loop/switch all reproduce the target
// word-for-word; the only divergence is ee-gcc -O2 assigning the saved copy of idx
// to $a1 (target: $t0), which also moves the FUN_00102020+0x18 handler into $a0
// (target: $a1) and shifts the post-jal store order. 35+ source variants tried.
extern char D_1B75484[];
extern int D_1B74238;
extern int D_1B7423C;
extern int FUN_001fc8c0();
extern void FUN_00100458(void);
extern void FUN_001006d8(void);
extern void FUN_00100940(void);
extern void FUN_00102020(void);

int FUN_00101e90(int idx, int a1, int a2, int a3)
{
    int i = 0;
    int slot;
    char *p = D_1B75484;
    char *q;
    char *ref;

    for (;;) {
        if (*(int *)(p + 0x10C) == 0 && *(unsigned char *)(p + 0x119) == 0) {
            D_1B74238 = i;
            slot = i;
            break;
        }
        i++;
        if (i >= 10) {
            slot = -1;
            break;
        }
        p += 0x16C;
    }

    ref = (char *)&D_1B7423C + ((idx << 6) + idx) * 8;
    q = (char *)&D_1B7423C + 0x1248 + slot * 0x16C;
    FUN_001fc8c0(q + 6);
    *(int *)q = (int)ref;
    *(char *)(q + 4) = 0;
    *(char *)(q + 0x119) = 1;
    *(char *)(q + 5) = 1;
    *(int *)(q + 0x15C) = a2;
    *(int *)(q + 0x160) = a3;
    *(short *)(q + 0x11C) = 0;
    *(int *)(q + 0x150) = (int)q;
    *(int *)(q + 0x10C) = (int)((char *)FUN_00102020 + 0x18);
    *(short *)(q + 0x11E) = 0;
    switch (*(int *)ref) {
    case 0:
        *(int *)(q + 0x10C) = (int)((char *)FUN_00102020 + 0x18);
        break;
    case 1:
        *(int *)(q + 0x10C) = (int)FUN_00100458;
        break;
    case 2:
        *(int *)(q + 0x10C) = (int)FUN_001006d8;
        break;
    case 3:
        *(int *)(q + 0x10C) = (int)FUN_00100940;
        break;
    }
    return slot;
}
