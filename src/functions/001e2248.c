// FUNCTION: SLPM 0x001E2248  size 64  core 60
// FUN_001e1c68(p); *(int*)(p+0x20) = 0; *p = ((*p & ~0xC) | 4) & ~1 | 0x100;
extern void FUN_001e1c68(char *);

void FUN_001e2248(char *p)
{
    FUN_001e1c68(p);
    *(int *)(p + 0x20) = 0;
    *(int *)p = (*(int *)p & 0xFFFFFFF3 | 4) & 0xFFFFFFFE | 0x100;
}
