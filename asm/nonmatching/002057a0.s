/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002057a0, 0x10

glabel FUN_002057a0
    /* 1067A0 002057A0 20000324 */  addiu      $v1, $zero, 0x20
    /* 1067A4 002057A4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067A8 002057A8 0800E003 */  jr         $ra
    /* 1067AC 002057AC 00000000 */   nop
endlabel FUN_002057a0
