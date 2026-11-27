/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f3d8, 0x10

glabel FUN_0020f3d8
    /* 1103D8 0020F3D8 74000324 */  addiu      $v1, $zero, 0x74
    /* 1103DC 0020F3DC 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1103E0 0020F3E0 0800E003 */  jr         $ra
    /* 1103E4 0020F3E4 00000000 */   nop
endlabel FUN_0020f3d8
