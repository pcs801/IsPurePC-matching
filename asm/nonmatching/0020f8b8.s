/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f8b8, 0x10

glabel FUN_0020f8b8
    /* 1108B8 0020F8B8 5B000324 */  addiu      $v1, $zero, 0x5B
    /* 1108BC 0020F8BC 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1108C0 0020F8C0 0800E003 */  jr         $ra
    /* 1108C4 0020F8C4 00000000 */   nop
endlabel FUN_0020f8b8
