/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205830, 0x20

glabel FUN_00205830
    /* 106830 00205830 29000324 */  addiu      $v1, $zero, 0x29
    /* 106834 00205834 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106838 00205838 0800E003 */  jr         $ra
    /* 10683C 0020583C 00000000 */   nop
    /* 106840 00205840 D6FF0324 */  addiu      $v1, $zero, -0x2A
    /* 106844 00205844 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106848 00205848 0800E003 */  jr         $ra
    /* 10684C 0020584C 00000000 */   nop
endlabel FUN_00205830
