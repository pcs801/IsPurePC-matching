/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056a0, 0x10

glabel FUN_002056a0
    /* 1066A0 002056A0 11000324 */  addiu      $v1, $zero, 0x11
    /* 1066A4 002056A4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066A8 002056A8 0800E003 */  jr         $ra
    /* 1066AC 002056AC 00000000 */   nop
endlabel FUN_002056a0
