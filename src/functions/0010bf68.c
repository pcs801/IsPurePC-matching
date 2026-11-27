// FUNCTION: SLPM 0x0010BF68  size 72  core 72 (96-byte queue range also covers 0x0010BFB0/BFB8/BFC0)
typedef int va_list;

void FUN_0010bf68(char *fmt, ...)
{
    va_list ap;
    __builtin_stdarg_start(&ap, fmt);
}

void FUN_0010bfb0(void) {}
void FUN_0010bfb8(void) {}
void FUN_0010bfc0(void) {}
