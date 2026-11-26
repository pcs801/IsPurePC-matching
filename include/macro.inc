.ifndef _MACRO_INC_GUARD
.set _MACRO_INC_GUARD, 1

.macro glabel label, visibility=global
    .global \label
    .type \label, @function
\label:
.endm

.macro endlabel label
    .size \label, . - \label
.endm

.macro alabel label, visibility=global
    .global \label
    .type \label, @function
\label:
.endm

.macro ehlabel label, visibility=global
    .global \label
\label:
.endm

.macro jlabel label, visibility=global
    .global \label
\label:
.endm

.macro dlabel label, visibility=global
    .global \label
    .type \label, @object
\label:
.endm

.macro enddlabel label
    .size \label, . - \label
.endm

.macro nonmatching label, size=1
.endm

.endif
