/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205890, 0x10

glabel FUN_00205890
    /* 106890 00205890 2F000324 */  addiu      $v1, $zero, 0x2F
    /* 106894 00205894 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106898 00205898 0800E003 */  jr         $ra
    /* 10689C 0020589C 00000000 */   nop
endlabel FUN_00205890
