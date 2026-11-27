/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00211830, 0x10

glabel FUN_00211830
    /* 112830 00211830 56000324 */  addiu      $v1, $zero, 0x56
    /* 112834 00211834 0C000000 */  syscall    0 /* handwritten instruction */
    /* 112838 00211838 0800E003 */  jr         $ra
    /* 11283C 0021183C 00000000 */   nop
endlabel FUN_00211830
