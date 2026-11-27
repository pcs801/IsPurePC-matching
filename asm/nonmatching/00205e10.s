/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205e10, 0x10

glabel FUN_00205e10
    /* 106E10 00205E10 82000324 */  addiu      $v1, $zero, 0x82
    /* 106E14 00205E14 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106E18 00205E18 0800E003 */  jr         $ra
    /* 106E1C 00205E1C 00000000 */   nop
endlabel FUN_00205e10
