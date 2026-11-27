// FUNCTION: SLPM 0x00112700  size 80  core 76

extern int FUN_00114870(void *);
extern int FUN_001ea658(int **);

int FUN_00112700(int self)
{
    int r = 0;

    if (FUN_00114870((char *)self + 0x48) == 0)
        r = FUN_001ea658((int **)self) != 0;
    return r;
}
