// five 8-byte leaf accessors that share one 40-byte region
int FUN_001cd158(void *self) { return *(int *)((char *)self + 0x18); }
int FUN_001cd160(void *self) { return *(short *)((char *)self + 0x1C); }
int FUN_001cd168(void *self) { return *(int *)((char *)self + 0x20); }
int FUN_001cd170(void *self) { return *(short *)((char *)self + 0x24); }
int FUN_001cd178(void *self) { return *(int *)((char *)self + 0x28); }
