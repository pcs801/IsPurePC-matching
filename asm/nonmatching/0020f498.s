/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f498, 0x10

glabel FUN_0020f498
    /* 110498 0020F498 5B000324 */  addiu      $v1, $zero, 0x5B
    /* 11049C 0020F49C 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1104A0 0020F4A0 0800E003 */  jr         $ra
    /* 1104A4 0020F4A4 00000000 */   nop
endlabel FUN_0020f498
