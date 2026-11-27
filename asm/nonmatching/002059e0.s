/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059e0, 0x10

glabel FUN_002059e0
    /* 1069E0 002059E0 44000324 */  addiu      $v1, $zero, 0x44
    /* 1069E4 002059E4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069E8 002059E8 0800E003 */  jr         $ra
    /* 1069EC 002059EC 00000000 */   nop
endlabel FUN_002059e0
