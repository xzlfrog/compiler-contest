.module start
.endmodule
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
