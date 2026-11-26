// FUNCTION: SLPM 0x00101AA8  size 328  core 328
extern char D_1B75484[];
extern int D_1B755E0;
extern int D_1B7423C;
extern int D_1B74238;
extern int FUN_00100458;
extern int FUN_001006d8;
extern int FUN_00100940;
extern int FUN_00102020;

int FUN_00101aa8(int idx)
{
    return *(int *)((char *)&D_1B755E0 + idx * 0x16C);
}

int FUN_00101ac8(int idx, int a1, int a2)
{
    int i;
    int found = -1;
    char *slot;
    int state;

    for (i = 0; i < 10; i++) {
        char *p = D_1B75484 + i * 0x16C;
        if (*(int *)(p + 0x10C) == 0 && *(unsigned char *)(p + 0x119) == 0) {
            found = i;
            D_1B74238 = i;
            break;
        }
    }

    slot = D_1B75484 + found * 0x16C;
    state = *(int *)((char *)&D_1B7423C + idx * 0x208);

    *(int *)(slot + 0x108) = a1;
    *(char *)(slot + 0x119) = 1;
    *(char *)(slot + 0x5) = 0;
    *(char *)(slot + 0x4) = 0;
    *(int *)(slot + 0x160) = a2;
    *(int *)slot = (int)((char *)&D_1B7423C + idx * 0x208);
    *(int *)(slot + 0x15C) = a2;
    *(short *)(slot + 0x11C) = 0;
    *(int *)(slot + 0x150) = (int)slot;
    *(int *)(slot + 0x10C) = (int)((char *)&FUN_00102020 + 0x18);
    *(short *)(slot + 0x11E) = 0;

    switch (state) {
    case 0: *(int *)(slot + 0x10C) = (int)((char *)&FUN_00102020 + 0x18); break;
    case 1: *(int *)(slot + 0x10C) = (int)&FUN_00100458; break;
    case 2: *(int *)(slot + 0x10C) = (int)&FUN_001006d8; break;
    case 3: *(int *)(slot + 0x10C) = (int)&FUN_00100940; break;
    }
    return found;
}
