/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205680, 0x10

glabel FUN_00205680
    /* 106680 00205680 10000324 */  addiu      $v1, $zero, 0x10
    /* 106684 00205684 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106688 00205688 0800E003 */  jr         $ra
    /* 10668C 0020568C 00000000 */   nop
endlabel FUN_00205680
