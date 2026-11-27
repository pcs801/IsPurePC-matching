/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205770, 0x30

glabel FUN_00205770
    /* 106770 00205770 E3FF0324 */  addiu      $v1, $zero, -0x1D
    /* 106774 00205774 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106778 00205778 0800E003 */  jr         $ra
    /* 10677C 0020577C 00000000 */   nop
    /* 106780 00205780 02FF0324 */  addiu      $v1, $zero, -0xFE
    /* 106784 00205784 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106788 00205788 0800E003 */  jr         $ra
    /* 10678C 0020578C 00000000 */   nop
    /* 106790 00205790 01FF0324 */  addiu      $v1, $zero, -0xFF
    /* 106794 00205794 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106798 00205798 0800E003 */  jr         $ra
    /* 10679C 0020579C 00000000 */   nop
endlabel FUN_00205770
