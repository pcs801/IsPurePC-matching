// FUNCTION: SLPM 0x00112450  size 256  core 256

extern void FUN_001e9888(int, int, int, int);
extern void FUN_001ea6a0(int, int, void (*)(void), int);
extern void FUN_00112448(int);
extern void FUN_001144d8(void *, int, int, int, int, int);
extern void FUN_00112850(void);
extern void FUN_00112878(void);
extern void FUN_001128a8(void);
extern void FUN_001128d0(void);
extern void FUN_001128f8(void);

int FUN_00112450(int self, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    FUN_001e9888(self, a1, a2, a3);
    FUN_001ea6a0(self, 0, FUN_00112850, 0);
    FUN_001ea6a0(self, 1, FUN_00112878, 0);
    FUN_001ea6a0(self, 2, FUN_001128a8, 0);
    FUN_001ea6a0(self, 3, FUN_001128d0, 0);
    FUN_001ea6a0(self, 5, FUN_001128f8, 0);
    FUN_00112448(self);
    FUN_001144d8((char *)self + 0x48, a3, a4, a5, a6, a7);
    return 1;
}
