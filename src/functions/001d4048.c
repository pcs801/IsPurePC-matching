// FUNCTION: SLPM 0x001D4048  size 96  core 88
// if (FUN_001fba40(p, D_026A860, 4) != 0) { if (FUN_001fba40(p, D_026A868, 4) != 0) return 0; } return 1;
extern char D_026A860[];
extern char D_026A868[];
extern int FUN_001fba40(char *, char *, int);

int FUN_001d4048(char *p)
{
    if (FUN_001fba40(p, D_026A860, 4) != 0) {
        if (FUN_001fba40(p, D_026A868, 4) != 0)
            return 0;
    }
    return 1;
}
