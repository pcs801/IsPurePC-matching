// FUNCTION: SLPM 0x00107AF8  size 32  core 32
// p = D_00281580 + idx * 0x4E280; p[0] = a1; p[2] = a2;  (ascending source -> descending emit)
extern char D_00281580[];

void FUN_00107af8(int idx, char a1, char a2)
{
    char *p;

    p = D_00281580 + idx * 0x4E280;
    p[0] = a1;
    p[2] = a2;
}
