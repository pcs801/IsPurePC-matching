/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d60, 0x10

glabel FUN_00205d60
    /* 106D60 00205D60 77000324 */  addiu      $v1, $zero, 0x77
    /* 106D64 00205D64 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D68 00205D68 0800E003 */  jr         $ra
    /* 106D6C 00205D6C 00000000 */   nop
endlabel FUN_00205d60
