// FUNCTION: SLPM 0x00101E90  size 376
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
    int slot = -1;
    int i;
    char *p = D_1B75484;
    char *ref;

    for (i = 0; i < 10; i++, p += 0x16C) {
        if (*(int *)(p + 0x10C) != 0)
            continue;
        if (*(unsigned char *)(p + 0x119) != 0)
            continue;
        D_1B74238 = i;
        slot = i;
        break;
    }

    ref = (char *)&D_1B7423C + ((idx << 6) + idx) * 8;
    p = (char *)&D_1B7423C + 0x1248 + slot * 0x16C;
    FUN_001fc8c0(p + 6);
    *(int *)p = (int)ref;
    *(char *)(p + 4) = 0;
    *(char *)(p + 0x119) = 1;
    *(char *)(p + 5) = 1;
    *(int *)(p + 0x15C) = a2;
    *(int *)(p + 0x160) = a3;
    *(short *)(p + 0x11C) = 0;
    *(int *)(p + 0x150) = (int)p;
    *(int *)(p + 0x10C) = (int)((char *)FUN_00102020 + 0x18);
    *(short *)(p + 0x11E) = 0;
    switch (*(int *)ref) {
    case 0:
        *(int *)(p + 0x10C) = (int)((char *)FUN_00102020 + 0x18);
        break;
    case 1:
        *(int *)(p + 0x10C) = (int)FUN_00100458;
        break;
    case 2:
        *(int *)(p + 0x10C) = (int)FUN_001006d8;
        break;
    case 3:
        *(int *)(p + 0x10C) = (int)FUN_00100940;
        break;
    }
    return slot;
}
