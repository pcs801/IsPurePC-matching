/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00211728, 0x10

glabel FUN_00211728
    /* 112728 00211728 5B000324 */  addiu      $v1, $zero, 0x5B
    /* 11272C 0021172C 0C000000 */  syscall    0 /* handwritten instruction */
    /* 112730 00211730 0800E003 */  jr         $ra
    /* 112734 00211734 00000000 */   nop
endlabel FUN_00211728
