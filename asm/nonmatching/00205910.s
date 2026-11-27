/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205910, 0x10

glabel FUN_00205910
    /* 106910 00205910 37000324 */  addiu      $v1, $zero, 0x37
    /* 106914 00205914 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106918 00205918 0800E003 */  jr         $ra
    /* 10691C 0020591C 00000000 */   nop
endlabel FUN_00205910
