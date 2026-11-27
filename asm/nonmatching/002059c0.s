/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059c0, 0x10

glabel FUN_002059c0
    /* 1069C0 002059C0 42000324 */  addiu      $v1, $zero, 0x42
    /* 1069C4 002059C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069C8 002059C8 0800E003 */  jr         $ra
    /* 1069CC 002059CC 00000000 */   nop
endlabel FUN_002059c0
