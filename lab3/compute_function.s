  .globl compute
compute:
  pushq   $-13
  pushq   $2
  popq    %r10
  popq    %r11
  addq    %r10,%r11
  pushq   %r11
  popq    %rax
  retq
