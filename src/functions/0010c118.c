// FUNCTION: SLPM 0x0010C118  size 216  core 212

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
extern char D_00258A50[];
extern char D_00258A60[];
extern unsigned char D_1B741FF[];

extern int FUN_001fe618(int);
extern int FUN_001fc2a8(char *, char *, int);
extern int FUN_001fcb10(int);
extern int FUN_00105b90(int);
extern void FUN_0010e910(void *, int, int, int);

void FUN_0010c118(int idx, int a, int b)
{
    char buf[0x100];

    idx &= 0xFFF;
    if (D_1B741FF[0] == 1) {
        FUN_001fe618(D_B25A30[idx].ptr);
        FUN_001fc2a8(buf, D_00258A50, D_B25A30[idx].ptr);
    } else {
        FUN_001fcb10(D_B25A30[idx].ptr);
        FUN_001fc2a8(buf, D_00258A60, D_B25A30[idx].ptr);
    }
    FUN_0010e910(buf, a, FUN_00105b90(D_B25A30[idx].bE), b);
}
