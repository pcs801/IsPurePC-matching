/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205690, 0x10

glabel FUN_00205690
    /* 106690 00205690 10000324 */  addiu      $v1, $zero, 0x10
    /* 106694 00205694 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106698 00205698 0800E003 */  jr         $ra
    /* 10669C 0020569C 00000000 */   nop
endlabel FUN_00205690
