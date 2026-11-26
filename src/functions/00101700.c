// FUNCTION: SLPM 0x00101700  size 88  core 84
extern int D_01B7423C;
extern int FUN_001fc8c0(void *);

int FUN_00101700(int idx) {
    char *p = (char *)&D_01B7423C + ((idx << 6) + idx) * 8;
    FUN_001fc8c0(p + 8);
    *(int *)(p + 4) = idx;
    *(int *)p = 1;
    return 1;
}
