// FUNCTION: SLPM 0x00209A38  size 64  core 60
int FUN_00209a38(int *p)
{
    int *q;
    int r;

    r = 0;
    q = (int *)p[0];
    if (q != 0) {
        if (p[1] == q[6]) {
            if ((q[4] & 1) != 0)
                r = 1;
        }
    }
    return r;
}
