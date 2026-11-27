// FUNCTION: SLPM 0x00110D30  size 656  core 652

typedef struct {
    int status;
    int func;
    int stack;
    int stack_size;
    int gp;
    int priority;
    int pad[3];
} Frame;

extern int D_00270CA0;
extern int D_00270C90;
extern int D_00270CA4;
extern int D_00270C94;
extern int D_00270C98;
extern int D_0026FEA0;
extern char D_1B7E448[];
extern char D_1B7E430[];
extern char D_1B7E560[];
extern char D_00259190[];
extern char D_2779F0[];

extern void FUN_00111730(void *);
extern void FUN_001ea430(void);
extern void FUN_00112450(void *, void *, int, void *, void *, int, void *, int);
extern void FUN_001118a0(void *, void *, int, int);
extern int FUN_00112750(void *, int, int, void (*)(void), void *);
extern void FUN_00112a70(void *, int, void *, int);
extern int FUN_002057a0(Frame *);
extern int FUN_00206ae0(int, int);
extern int FUN_001134c8(void *, int);
extern int FUN_001fbd78(void *, ...);
extern void FUN_001dd6a0(void (*)(void));
extern int FUN_002056b0(int, void (*)(void), int);
extern int FUN_002065b8(int);
extern void FUN_00113268(void);
extern void FUN_00113490(void);
extern void FUN_001113b8(void);
extern void FUN_001127e0(void);
extern void FUN_00111408(void);
extern void FUN_00111658(void);
extern struct Dmac_s { char pad[0xB0]; int h; } D_1B7E4A8;

void FUN_00110d30(int arg0)
{
    Frame f;
    int th;
    char *tbl;

    tbl = (char *)&D_1B7E4A8;
    D_00270C90 = *(int *)0x1000E000;
    D_00270CA4 = *(int *)0x1000E010;
    *(int *)0x1000E000 |= 3;
    *(int *)0x1000E010 = 4;
    FUN_00111730((void *)(D_00270CA0 + 0x622800));
    FUN_001ea430();
    FUN_00112450(tbl, (void *)(D_00270CA0 + 0x3C4D00), 0x1CA200,
                 (void *)(D_00270CA0 + 0x59B700), (void *)(D_00270CA0 + 0x3C3C80),
                 0x100, (void *)(D_00270CA0 + 0x61F700), 0x200);
    FUN_001118a0(D_1B7E448, (void *)(D_00270CA0 + 0x58F700), 0xC000, 0x6000);
    FUN_00112750(tbl, 0, 0, FUN_00111408, (void *)(D_00270CA0 + 0x622800));
    if (D_0026FEA0)
        FUN_00112750(tbl, 2, 0, FUN_00111658, (void *)(D_00270CA0 + 0x622800));
    FUN_00112a70(D_1B7E430, (D_00270CA0 & 0x0FFFFFFF) | 0x20000000,
                 (void *)(D_00270CA0 + 0x32A000), 2);
    f.func = (int)FUN_001113b8;
    f.stack = D_00270CA0 + 0x58EF00;
    f.stack_size = 0x800;
    f.gp = (int)D_2779F0;
    f.priority = 1;
    f.pad[2] = 0;
    th = FUN_002057a0(&f);
    D_00270C94 = th;
    FUN_00206ae0(th, 0);
    f.func = (int)FUN_001127e0;
    f.stack = D_00270CA0 + 0x61B700;
    f.stack_size = 0x4000;
    f.gp = (int)D_2779F0;
    f.priority = 1;
    f.pad[2] = 0;
    th = FUN_002057a0(&f);
    D_00270C98 = th;
    FUN_00206ae0(th, (int)&D_1B7E4A8);
    while (FUN_001134c8(D_1B7E560, arg0) == 0)
        FUN_001fbd78(D_00259190, arg0);
    FUN_001dd6a0(FUN_00113268);
    D_1B7E4A8.h = FUN_002056b0(2, FUN_00113490, 0);
    FUN_002065b8(2);
}