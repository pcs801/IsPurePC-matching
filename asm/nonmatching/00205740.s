/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205740, 0x10

glabel FUN_00205740
    /* 106740 00205740 E6FF0324 */  addiu      $v1, $zero, -0x1A
    /* 106744 00205744 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106748 00205748 0800E003 */  jr         $ra
    /* 10674C 0020574C 00000000 */   nop
endlabel FUN_00205740
