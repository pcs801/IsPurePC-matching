// FUNCTION: SLPM 0x00208398  size 72  core 72
// ROM: buf[1] at sp+0, ra at sp+0x10, five 8-byte slots at sp+0x68..0x88 holding
// a3,t0,t1,t2,t3 (64-bit args in single registers), call FUN_00207550(D, buf, a1, a2, sp+0x68).
extern char D_0208268[];
extern void FUN_00207550(int a0, int *a1, int a2, int a3, int a4);

void FUN_00208398(int a0, int a1, int a2, long long a3, long long a4,
                  long long a5, long long a6, long long a7)
{
    int buf[1];
    long long arr[5];

    buf[0] = a0;
    arr[0] = a3;
    arr[1] = a4;
    arr[2] = a5;
    arr[3] = a6;
    arr[4] = a7;
    FUN_00207550((int)D_0208268, buf, a1, a2, (int)arr);
}
