/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002057e0, 0x10

glabel FUN_002057e0
    /* 1067E0 002057E0 24000324 */  addiu      $v1, $zero, 0x24
    /* 1067E4 002057E4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067E8 002057E8 0800E003 */  jr         $ra
    /* 1067EC 002057EC 00000000 */   nop
endlabel FUN_002057e0
