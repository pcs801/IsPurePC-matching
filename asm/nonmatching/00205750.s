/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205750, 0x10

glabel FUN_00205750
    /* 106750 00205750 E5FF0324 */  addiu      $v1, $zero, -0x1B
    /* 106754 00205754 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106758 00205758 0800E003 */  jr         $ra
    /* 10675C 0020575C 00000000 */   nop
endlabel FUN_00205750
