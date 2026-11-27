/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002058c0, 0x10

glabel FUN_002058c0
    /* 1068C0 002058C0 32000324 */  addiu      $v1, $zero, 0x32
    /* 1068C4 002058C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068C8 002058C8 0800E003 */  jr         $ra
    /* 1068CC 002058CC 00000000 */   nop
endlabel FUN_002058c0
