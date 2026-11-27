/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002057b0, 0x10

glabel FUN_002057b0
    /* 1067B0 002057B0 21000324 */  addiu      $v1, $zero, 0x21
    /* 1067B4 002057B4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067B8 002057B8 0800E003 */  jr         $ra
    /* 1067BC 002057BC 00000000 */   nop
endlabel FUN_002057b0
