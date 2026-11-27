/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059b0, 0x10

glabel FUN_002059b0
    /* 1069B0 002059B0 41000324 */  addiu      $v1, $zero, 0x41
    /* 1069B4 002059B4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069B8 002059B8 0800E003 */  jr         $ra
    /* 1069BC 002059BC 00000000 */   nop
endlabel FUN_002059b0
