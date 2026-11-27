/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056b0, 0x10

glabel FUN_002056b0
    /* 1066B0 002056B0 12000324 */  addiu      $v1, $zero, 0x12
    /* 1066B4 002056B4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066B8 002056B8 0800E003 */  jr         $ra
    /* 1066BC 002056BC 00000000 */   nop
endlabel FUN_002056b0
