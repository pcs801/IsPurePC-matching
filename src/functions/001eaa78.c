// FUNCTION: SLPM 0x001EAA78  size 24
// sig: sw ; sw ; sw ; jr ; sw ; nop

void FUN_001eaa78(unsigned int *self, unsigned int a, unsigned int b) {
    self[0] = a;
    self[1] = b;
    self[2] = a;
    self[3] = a;
}
