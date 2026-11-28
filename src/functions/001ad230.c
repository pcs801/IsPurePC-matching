// FUNCTION: SLPM 0x001AD230  size 64  core 56
// FUN_001ae158(*D_0243898); *D_0243898 = 0; *D_0243894 = 0; *D_02241C4 = 0;
extern char D_0243898[];
extern char D_0243894[];
extern char D_02241C4[];
extern void FUN_001ae158(int);

void FUN_001ad230(void)
{
    FUN_001ae158(*(int *)D_0243898);
    *(int *)D_0243898 = 0;
    *(int *)D_0243894 = 0;
    *(int *)D_02241C4 = 0;
}
