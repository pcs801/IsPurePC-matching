// FUNCTION: SLPM 0x00108858  size 1176
extern char D_002583C8[];
extern char D_002583E8[];
extern char D_00258400[];
extern char D_00258410[];
extern int D_46CC08[];
extern int D_46C400[];
extern unsigned char D_1B741F8[];
extern void FUN_0010bf20(char *);
extern void FUN_001016b8(void);
extern void FUN_001fbb84(char *, int, int);
extern void FUN_001b5dc0(char *);

void FUN_00108858(void)
{
    int s6;
    int c;

    FUN_0010bf20(D_002583C8);
    FUN_001016b8();
    FUN_0010bf20(D_002583E8);
    FUN_001fbb84((char *)D_46CC08, 0, 0x10);
    D_46CC08[0] = (int)D_00258400;
    D_46CC08[1] = 0x20;
    D_46CC08[3] = 0x802;
    D_46CC08[2] = (int)D_46C400;
    FUN_001b5dc0((char *)D_46CC08);
    FUN_0010bf20(D_00258410);
    for (s6 = 0;; s6++) {
        c = D_1B741F8[s6];
        if (c >= 8)
            continue;
        switch (c) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        }
    }
}
