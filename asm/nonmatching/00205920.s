/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205920, 0x10

glabel FUN_00205920
    /* 106920 00205920 C8FF0324 */  addiu      $v1, $zero, -0x38
    /* 106924 00205924 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106928 00205928 0800E003 */  jr         $ra
    /* 10692C 0020592C 00000000 */   nop
endlabel FUN_00205920
