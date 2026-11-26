// FUNCTION: SLPM 0x001A8228
void FUN_001a8228(int *self, int step, int alpha) {
    int cur;
    int inc;

    cur = self[0] >> 12;
    inc = cur < step;
    self[2] = step;
    self[3] = alpha;
    self[1] = (step + inc) << 12;
}
