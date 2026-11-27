// FUNCTION: SLPM 0x00111528  size 304  core 300
extern void FUN_001fbad4(void *, void *, int);

int FUN_00111528(char *a0, int a1, char *a2, int a3, char *t0, int t1, char *t2, int t3)
{
    char *s7 = a0;
    int s1 = a1;
    char *s6 = a2;
    char *s2 = t0;
    int s0 = t1;
    char *s4 = t2;
    int s5 = t3;
    int fp = s0 + s5;
    int s3;

    if (s1 + a3 < fp)
        return 0;
    if (s0 >= s1) {
        FUN_001fbad4(s7, s2, s1);
        FUN_001fbad4(s6, s2 + s1, s0 - s1);
        FUN_001fbad4(s6 + s0 - s1, s4, s5);
    } else {
        s3 = s1 - s0;
        if (s5 >= s3) {
            FUN_001fbad4(s7, s2, s0);
            FUN_001fbad4(s7 + s0, s4, s3);
            FUN_001fbad4(s6, s4 + s1 - s0, s5 - s3);
        } else {
            FUN_001fbad4(s7, s2, s0);
            FUN_001fbad4(s7 + s0, s4, s5);
        }
    }
    return fp;
}
