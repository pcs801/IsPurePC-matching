/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205760, 0x10

glabel FUN_00205760
    /* 106760 00205760 E4FF0324 */  addiu      $v1, $zero, -0x1C
    /* 106764 00205764 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106768 00205768 0800E003 */  jr         $ra
    /* 10676C 0020576C 00000000 */   nop
endlabel FUN_00205760
