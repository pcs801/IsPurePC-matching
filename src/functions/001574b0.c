// FUNCTION: SLPM 0x001574B0  size 80  core 80
// Region = this function (68 B) + pad + an empty function at 0x001574F8 (8 B).
extern int FUN_00105818(void *p);
extern int FUN_00105660(void *p);

int FUN_001574b0(char *p)
{
    if (FUN_00105818(p) == 1) {
        if (FUN_00105660(p) == 0)
            return 0;
    }
    return 1;
}

void FUN_001574f8(void)
{
}
