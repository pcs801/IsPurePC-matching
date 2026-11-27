/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f440, 0x10

glabel FUN_0020f440
    /* 110440 0020F440 74000324 */  addiu      $v1, $zero, 0x74
    /* 110444 0020F444 0C000000 */  syscall    0 /* handwritten instruction */
    /* 110448 0020F448 0800E003 */  jr         $ra
    /* 11044C 0020F44C 00000000 */   nop
endlabel FUN_0020f440
