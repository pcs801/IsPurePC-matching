/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205e00, 0x10

glabel FUN_00205e00
    /* 106E00 00205E00 7F000324 */  addiu      $v1, $zero, 0x7F
    /* 106E04 00205E04 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106E08 00205E08 0800E003 */  jr         $ra
    /* 106E0C 00205E0C 00000000 */   nop
endlabel FUN_00205e00
