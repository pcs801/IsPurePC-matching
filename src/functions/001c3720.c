// FUNCTION: SLPM 0x001C3720
extern void FUN_001c3578(int, int *);

int FUN_001c3720(int a0)
{
    int buf[2];

    FUN_001c3578(a0, buf);
    return 0u < (unsigned int)buf[1];
}
