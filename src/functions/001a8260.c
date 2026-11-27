void FUN_001a8260(char *p)
{
    int c = *(int *)(p + 12);

    if (c == 0) {
        int a = *(int *)(p);
        *(int *)(p) = a + (*(int *)(p + 4) - a) / *(int *)(p + 16);
    } else {
        *(int *)(p + 12) = c - 1;
    }
}