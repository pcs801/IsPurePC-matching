// FUNCTION: SLPM 0x001B0498  size 96  core 88
// two guarded function-pointer callbacks (each passes the companion global as arg) around one call
extern char D_0226FE0[];
extern char D_0226FE4[];
extern char D_0226FE8[];
extern char D_0226FEC[];
extern void FUN_001c3fd8(void);

void FUN_001b0498(void)
{
    if (*(void (**)(int))D_0226FE0 != 0)
        (*(void (**)(int))D_0226FE0)(*(int *)D_0226FE4);
    FUN_001c3fd8();
    if (*(void (**)(int))D_0226FE8 != 0)
        (*(void (**)(int))D_0226FE8)(*(int *)D_0226FEC);
}
