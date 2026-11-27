// FUNCTION: SLPM 0x0010BFE0  size 304  core 304 (includes 0x0010C108 empty tail)

typedef struct Rec {
    int ptr;
    unsigned short u4;
    unsigned short u6;
    unsigned short u8;
    unsigned short uA;
    unsigned char bC;
    unsigned char bD;
    unsigned char bE;
    unsigned char bF;
} Rec;

extern Rec D_B25A30[];
extern char D_0026FE28[];
extern char D_0026FE30[];
extern char D_00258A28[];
extern char D_00258A40[];
extern unsigned char D_1B741FF[];
extern int D_00270AC0;

extern int FUN_001fbd78(void *, ...);
extern int FUN_001fe618(int);
extern int FUN_001fc2a8(char *, char *, int);
extern int FUN_001fcb10(int);
extern int FUN_00105b90(int);
extern void FUN_001dc850(int, int);
extern void FUN_00111270(void *, int, int, int);
extern void FUN_00106268(void);
extern void FUN_001dd6a0(void (*)(void));
extern void FUN_00107508(void);
extern void FUN_0010df70(void);

void FUN_0010bfe0(int idx, int val)
{
    char buf[0x100];
    int n;

    FUN_001fbd78(D_0026FE28, idx);
    if (D_1B741FF[0] == 1) {
        FUN_001fe618(D_B25A30[idx].ptr);
        FUN_001fc2a8(buf, D_00258A28, D_B25A30[idx].ptr);
    } else {
        FUN_001fcb10(D_B25A30[idx].ptr);
        FUN_001fc2a8(buf, D_00258A40, D_B25A30[idx].ptr);
    }
    n = FUN_00105b90(D_B25A30[idx].bE);
    FUN_001fbd78(D_0026FE30, buf);
    FUN_001dc850(0, 0);
    FUN_00111270(buf, n, D_00270AC0, val);
    FUN_00106268();
    FUN_001dd6a0(FUN_0010df70);
    FUN_00107508();
}

void FUN_0010c108(void) {}
