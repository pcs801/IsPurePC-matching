// FUNCTION: SLPM 0x00101800  size 352  core 348 (multi-function slice: 0x1800, 0x1870, 0x18C0)
// 未命中说明：首函数 0x00101800 与 0x00101700 同因——存储值 3 与返回值 3 在目标里共用
// 一条 addiu v0,zero,3，ee-gcc -O2 在 store+return 形状下会重物化两次（多 4 字节）。

extern int D_01B7423C;
extern int D_01B75484;
extern int FUN_001fc8c0();
extern void FUN_00100458(void);
extern void FUN_001006d8(void);
extern void FUN_00100940(void);
extern void FUN_00102020(void);

int FUN_00101800(int idx, int a1, void *a2) {
    char *p = (char *)&D_01B7423C + ((idx << 6) + idx) * 8;
    FUN_001fc8c0(p + 0x108);
    FUN_001fc8c0(p + 8, a2);
    *(int *)(p + 4) = idx;
    *(int *)p = 3;
    return 3;
}

int FUN_00101870(void) {
    int i;
    char *p = (char *)&D_01B75484;
    char *q = p - 0x1254;
    for (i = 0; i < 10; i++, p += 0x16C) {
        if (*(int *)(p + 0x10C) != 0)
            continue;
        if (*(unsigned char *)(p + 0x119) != 0)
            continue;
        *(int *)(q + 8) = i;
        return i;
    }
    return -1;
}

void FUN_001018c0(int *src, char *a1) {
    char *h = (char *)FUN_00102020 + 0x18;
    *(char *)(a1 + 4) = 0;
    *(char *)(a1 + 0x119) = 1;
    *(short *)(a1 + 0x11C) = 0;
    *(char **)(a1 + 0x150) = a1;
    *(char **)(a1 + 0x10C) = h;
    *(short *)(a1 + 0x11E) = 0;
    switch (*(int *)src) {
    case 0:
        *(char **)(a1 + 0x10C) = h;
        break;
    case 1:
        *(char **)(a1 + 0x10C) = (char *)FUN_00100458;
        break;
    case 2:
        *(char **)(a1 + 0x10C) = (char *)FUN_001006d8;
        break;
    case 3:
        *(char **)(a1 + 0x10C) = (char *)FUN_00100940;
        break;
    }
}
