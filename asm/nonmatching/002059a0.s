/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059a0, 0x10

glabel FUN_002059a0
    /* 1069A0 002059A0 40000324 */  addiu      $v1, $zero, 0x40
    /* 1069A4 002059A4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069A8 002059A8 0800E003 */  jr         $ra
    /* 1069AC 002059AC 00000000 */   nop
endlabel FUN_002059a0
