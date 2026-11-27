// FUNCTION: SLPM 0x002094F8  size 80 (core 76)
// Walks list->0x28 then each node->8, following ->0x38 links; returns node->0x38 as int
// on a key match. Status: 92/76, 11 words off (loop shape still approximate).
int FUN_002094f8(int key, char *list)
{
    char *n = *(char **)(list + 0x28);
    char *e;

    while (n != 0) {
        e = *(char **)(n + 8);
        while (e != 0) {
            if (*(int *)e == key)
                return *(int *)(e + 0x38);
            e = *(char **)(e + 0x38);
        }
        n = *(char **)(n + 0x14);
    }
    return 0;
}
