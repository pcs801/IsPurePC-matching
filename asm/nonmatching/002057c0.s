/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002057c0, 0x20

glabel FUN_002057c0
    /* 1067C0 002057C0 22000324 */  addiu      $v1, $zero, 0x22
    /* 1067C4 002057C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067C8 002057C8 0800E003 */  jr         $ra
    /* 1067CC 002057CC 00000000 */   nop
    /* 1067D0 002057D0 23000324 */  addiu      $v1, $zero, 0x23
    /* 1067D4 002057D4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067D8 002057D8 0800E003 */  jr         $ra
    /* 1067DC 002057DC 00000000 */   nop
endlabel FUN_002057c0
