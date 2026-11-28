// FUNCTION: SLPM 0x001C0900  size 96  core 88  (splat merged two functions)
//  0x1C0900: if (p==0) return; if (*(u8*)(p+2) >= 2) FUN_001c0bd0(); *p = 0; FUN_001c0768();
//  0x1C0958: separate function (addiu sp,-0x10 / a3 = a0 / ...)
extern void FUN_001c0bd0(void);
extern void FUN_001c0768(void);

void FUN_001c0900(char *p)
{
    if (p == 0)
        return;
    if (*(unsigned char *)(p + 2) >= 2)
        FUN_001c0bd0();
    *p = 0;
    FUN_001c0768();
}
