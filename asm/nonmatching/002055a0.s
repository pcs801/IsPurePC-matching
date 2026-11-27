/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002055a0, 0x20

glabel FUN_002055a0
    /* 1065A0 002055A0 02000324 */  addiu      $v1, $zero, 0x2
    /* 1065A4 002055A4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065A8 002055A8 0800E003 */  jr         $ra
    /* 1065AC 002055AC 00000000 */   nop
    /* 1065B0 002055B0 03000324 */  addiu      $v1, $zero, 0x3
    /* 1065B4 002055B4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065B8 002055B8 0800E003 */  jr         $ra
    /* 1065BC 002055BC 00000000 */   nop
endlabel FUN_002055a0
