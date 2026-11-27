extern char D_0026DA10[];
extern char D_0026DA50[];
extern char D_0026DA90[];
extern int FUN_001eeec8(char *a0, char *a1);
extern int FUN_00208450(char *a0);
extern int FUN_001f3908(char *a0);
extern int FUN_001eb4f8(int a0);
extern int FUN_001ea810(int a0, int a1, int a2);

int FUN_001e9c88(int obj)
{
    char *ctx;
    int s2;
    int s3;

    s3 = 0;
    s2 = 1;
    ctx = *(char **)(obj + 0x40);
    if ((*(int *)(ctx + 0xEC) & 0x3F) != 0) {
        *(int *)(ctx + 0) = 0;
        FUN_001eeec8(ctx, D_0026DA10);
        return -1;
    }
    if (*(int *)(ctx + 0x878) != 0) {
        FUN_00208450(D_0026DA50);
        return -1;
    }
    *(int *)(ctx + 0x834) = 0;
    for (;;) {
        if (s3 != -1) {
            s2 = FUN_001f3908(ctx);
            if (s2 < 0)
                return -1;
            if (s2 != 0 && *(int *)(ctx + 0x184) != *(int *)(ctx + 0xE8) && *(int *)(ctx + 0x858) != 0)
                continue;
        }
        if ((unsigned int)s2 < 5) {
            switch (s2) {
            case 0:
                FUN_001eb4f8(obj);
                *(int *)(ctx + 0) = 1;
                break;
            case 1:
                *(int *)(ctx + 0xB4) = 0;
                *(int *)(ctx + 0xB8) = 0;
                *(int *)(ctx + 0xBC) = 0;
                s3 = FUN_001ea810(obj, 0, *(int *)(ctx + 0xA8));
                (*(int *)(ctx + 0xB4))++;
                break;
            case 2:
                s3 = FUN_001ea810(obj, *(int *)(ctx + 0xB8), *(int *)(ctx + 0xAC));
                (*(int *)(ctx + 0xB8))++;
                break;
            case 3:
            case 4:
                s3 = FUN_001ea810(obj, *(int *)(ctx + 0xBC), *(int *)(ctx + 0xB0));
                (*(int *)(ctx + 0xBC))++;
                break;
            }
        }
        if (*(int *)(ctx + 0x878) != 0) {
            FUN_00208450(D_0026DA90);
            return -1;
        }
        if (*(int *)(ctx + 0x834) != 0)
            return 1;
        if (*(int *)(ctx + 0) != 0)
            return 1;
    }
}
