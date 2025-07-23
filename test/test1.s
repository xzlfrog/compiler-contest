	.section .rodata
	.global @base.scope0.id0
	.align 4
@base.scope0.id0:
	.word 16
	.section .rodata
	.global @base.scope0.id0
	.align 4
@base.scope0.id0:
	.word 16
	.section .rod.endmodule
.module start
@func.getMaxNum :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP

%label.entry.0:
SUB SP, SP, #-4
MOV X9, SP
STR X9, [SP, #-4]
STR XZR, [SP, #-4]
SUB SP, SP, #-8
MOV X10, SP
STR X10, [SP, #-8]
STR XZR, [SP, #-8]
%label.tmp_label.0:
LDR X12, [SP, #-8]
STR X11, [SP, #-8]
STR X12, [SP, #-8]
STR X13, [SP, #-8]
LDR X15, [SP, #-4]
STR X14, [SP, #-4]
STR X15, [SP, #-4]
STR X19, [SP, #-4]
LDR X21, [SP, #-8]
STR X20, [SP, #-8]
STR X21, [SP, #-8]
STR X22, [SP, #-8]
LDR X24, [SP, #-8]
STR X23, [SP, #-8]
STR X24, [SP, #-8]
LDR X25, [SP, #-12]
LDR X0, [SP, #-12]
LDR X28, [SP, #-12]
CMP X28, X9
CSET X26, LT
STR X11, [SP, #-16]
ZEXT X10, X11
STR X13, [SP, #-20]
TRUNC X12, X13
STR X14, [SP, #-24]
CBZ X14, %label.tmp_label.1
CBNZ X14, %label.tmp_label.2
%label.tmp_label.1:
LDR X15, [SP, #-4]
LDR X19, [SP, #-28]
STR X19, [SP, #-32]
LDR X15, [SP, #-28]
LDR X20, [SP, #-8]
STR X20, [SP, #-36]
LDR X21, [SP, #-40]
LDR X20, [SP, #-40]
STR X22, [SP, #-44]
STR X23, [SP, #-48]
LDR X25, [SP, #-28]
STR X25, [SP, #-12]
CMP X24, X25
CSET X22, GT
STR X26, [SP, #-48]
STR X27, [SP, #-52]
ZEXT X26, X27
STR X28, [SP, #-12]
STR X9, [SP, #-56]
TRUNC X28, X9
STR X10, [SP, #-60]
CBZ X10, %label.tmp_label.3
CBNZ X10, %label.tmp_label.4
%label.tmp_label.3:
STR X15, [SP, #-4]
LDR X11, [SP, #-64]
STR X11, [SP, #-48]
LDR X0, [SP, #-64]
STR X20, [SP, #-8]
LDR X12, [SP, #-68]
STR X12, [SP, #-68]
LDR X0, [SP, #-68]
STR X13, [SP, #-60]
LDR X14, [SP, #-4]
STR X14, [SP, #-68]
STR X13, [SP, #-4]
%label.tmp_label.4:
STR X14, [SP, #-4]
STR X15, [SP, #-4]
STR X19, [SP, #-28]
LDR X20, [SP, #-8]
STR X19, [SP, #-8]
STR X20, [SP, #-8]
LDR X21, [SP, #-72]
STR X21, [SP, #-40]
LDR X0, [SP, #-72]
LDR X22, [SP, #-8]
STR X22, [SP, #-72]
LDR X23, [SP, #-76]
STR X23, [SP, #-80]
LDR X22, [SP, #-76]
STR X24, [SP, #-84]
LDR X25, [SP, #-76]
STR X25, [SP, #-28]
ADD X24, X25, #1
STR X26, [SP, #-88]
STR X22, [SP, #-8]
STR X26, [SP, #-8]
B %label.tmp_label.0
%label.tmp_label.2:
LDR X27, [SP, #-4]
STR X27, [SP, #-72]
LDR X28, [SP, #-92]
STR X28, [SP, #-92]
LDR X27, [SP, #-92]
LDR X9, [SP, #-92]
STR X9, [SP, #-88]
MOV X0, X9
    // Function epilogue
    add sp, sp, #96      // Deallocate stack space
    ldp x29, x30, [sp], #16 // Re.endmodule
.module start
@func.getNumPos :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP
    sub sp, sp, #96      // Allocate stack space

%label.entry.1:
STR X10, [SP, #-92]
SUB SP, SP, #-96
MOV X10, SP
STR X10, [SP, #-96]
STR #1, [SP, #-96]
STR X11, [SP, #-64]
SUB SP, SP, #-100
MOV X11, SP
STR X11, [SP, #-100]
STR XZR, [SP, #-100]
%label.tmp_label.5:
STR X12, [SP, #-68]
LDR X13, [SP, #-100]
STR X13, [SP, #-104]
STR X12, [SP, #-100]
STR X13, [SP, #-100]
STR X14, [SP, #-100]
STR X15, [SP, #-108]
LDR X19, [SP, #-100]
STR X19, [SP, #-112]
STR X15, [SP, #-100]
STR X19, [SP, #-100]
LDR X20, [SP, #-116]
LDR X0, [SP, #-116]
STR X21, [SP, #-72]
LDR X23, [SP, #-116]
STR X23, [SP, #-76]
STR X24, [SP, #-120]
CMP X23, X24
CSET X21, LT
STR X25, [SP, #-76]
STR X26, [SP, #-120]
ZEXT X25, X26
STR X27, [SP, #-4]
STR X28, [SP, #-92]
TRUNC X27, X28
STR X9, [SP, #-92]
CBZ X9, %label.tmp_label.6
CBNZ X9, %label.tmp_label.7
%label.tmp_label.6:
SDIV X10, X11, #16
LDR X12, [SP, #-100]
STR X12, [SP, #-124]
LDR X13, [SP, #-128]
LDR X12, [SP, #-128]
STR X12, [SP, #-100]
LDR X14, [SP, #-132]
STR X14, [SP, #-136]
LDR X0, [SP, #-132]
STR X15, [SP, #-140]
LDR X19, [SP, #-132]
ADD X15, X19, #1
STR X20, [SP, #-116]
LDR X21, [SP, #-100]
STR X21, [SP, #-140]
STR X20, [SP, #-100]
B %label.tmp_label.5
%label.tmp_label.7:
STR X22, [SP, #-144]
STR X23, [SP, #-116]
STR X24, [SP, #-148]
SDIV X23, X24, #16
MUL X23, X23, #16
SUB X22, X22, X23
STR X25, [SP, #-152]
MOV X0, X25
    // Function epilogue
    add sp, sp, #160      // Deallocate stack space
    ldp x29, x30, [sp], #16 // Re.endmodule
.module start
@func.radixSort :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP
    sub sp, sp, #160      // Allocate stack space

%label.entry.2:
