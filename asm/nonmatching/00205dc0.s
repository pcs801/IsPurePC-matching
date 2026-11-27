/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205dc0, 0x10

glabel FUN_00205dc0
    /* 106DC0 00205DC0 7B000324 */  addiu      $v1, $zero, 0x7B
    /* 106DC4 00205DC4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DC8 00205DC8 0800E003 */  jr         $ra
    /* 106DCC 00205DCC 00000000 */   nop
endlabel FUN_00205dc0
