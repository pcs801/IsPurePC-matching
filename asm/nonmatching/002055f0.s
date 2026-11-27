/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002055f0, 0x60

glabel FUN_002055f0
    /* 1065F0 002055F0 07000324 */  addiu      $v1, $zero, 0x7
    /* 1065F4 002055F4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065F8 002055F8 0800E003 */  jr         $ra
    /* 1065FC 002055FC 00000000 */   nop
    /* 106600 00205600 08000324 */  addiu      $v1, $zero, 0x8
    /* 106604 00205604 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106608 00205608 0800E003 */  jr         $ra
    /* 10660C 0020560C 00000000 */   nop
    /* 106610 00205610 09000324 */  addiu      $v1, $zero, 0x9
    /* 106614 00205614 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106618 00205618 0800E003 */  jr         $ra
    /* 10661C 0020561C 00000000 */   nop
    /* 106620 00205620 0A000324 */  addiu      $v1, $zero, 0xA
    /* 106624 00205624 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106628 00205628 0800E003 */  jr         $ra
    /* 10662C 0020562C 00000000 */   nop
    /* 106630 00205630 0B000324 */  addiu      $v1, $zero, 0xB
    /* 106634 00205634 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106638 00205638 0800E003 */  jr         $ra
    /* 10663C 0020563C 00000000 */   nop
    /* 106640 00205640 0C000324 */  addiu      $v1, $zero, 0xC
    /* 106644 00205644 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106648 00205648 0800E003 */  jr         $ra
    /* 10664C 0020564C 00000000 */   nop
endlabel FUN_002055f0
