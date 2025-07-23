	.section .rodata
	.global @base.scope0.id0
	.align 4
@base.scope0.id0:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
	.section .rodata
	.global @base.scope0.id0
	.align 4
@base.scope0.id0:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
	.section .rodata
	.global @base.scope0.id0
	.align 4
@base.scope0.id0:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
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
STR X10, [SP, #-8]
STR X11, [SP, #-8]
STR X10, [SP, #-8]
STR X12, [SP, #-8]
STR X9, [SP, #-4]
STR X13, [SP, #-4]
STR X9, [SP, #-4]
STR X14, [SP, #-4]
STR X10, [SP, #-8]
STR X15, [SP, #-8]
STR X10, [SP, #-8]
STR X19, [SP, #-8]
STR X10, [SP, #-8]
STR X20, [SP, #-8]
STR X10, [SP, #-8]
LDR X21, [SP, #-12]
LDR X10, [SP, #-12]
LDR X24, [SP, #-12]
CMP X24, X25
CSET X22, LT
ZEXT X26, X27
STR X9, [SP, #-4]
TRUNC X28, X9
STR X10, [SP, #-8]
CBZ X10, %label.tmp_label.1
CBNZ X10, %label.tmp_label.2
%label.tmp_label.1:
STR X9, [SP, #-16]
LDR X11, [SP, #-20]
STR X11, [SP, #-24]
LDR X9, [SP, #-20]
STR X10, [SP, #-24]
LDR X12, [SP, #-28]
STR X12, [SP, #-32]
LDR X10, [SP, #-28]
STR X13, [SP, #-36]
STR X14, [SP, #-40]
STR X15, [SP, #-44]
LDR X19, [SP, #-20]
STR X19, [SP, #-48]
CMP X15, X19
CSET X13, GT
STR X20, [SP, #-52]
STR X21, [SP, #-12]
ZEXT X20, X21
STR X22, [SP, #-52]
STR X23, [SP, #-56]
TRUNC X22, X23
STR X24, [SP, #-12]
CBZ X24, %label.tmp_label.3
CBNZ X24, %label.tmp_label.4
%label.tmp_label.3:
STR X9, [SP, #-4]
LDR X25, [SP, #-60]
STR X25, [SP, #-64]
LDR X9, [SP, #-60]
STR X10, [SP, #-8]
LDR X26, [SP, #-68]
STR X26, [SP, #-16]
LDR X10, [SP, #-68]
STR X27, [SP, #-52]
STR X9, [SP, #-4]
STR X27, [SP, #-4]
%label.tmp_label.4:
STR X28, [SP, #-24]
STR X9, [SP, #-4]
STR X28, [SP, #-4]
STR X9, [SP, #-4]
STR X10, [SP, #-8]
STR X9, [SP, #-8]
STR X10, [SP, #-8]
LDR X10, [SP, #-72]
STR X10, [SP, #-8]
LDR X10, [SP, #-72]
STR X10, [SP, #-72]
LDR X11, [SP, #-76]
STR X11, [SP, #-20]
LDR X10, [SP, #-76]
STR X12, [SP, #-28]
LDR X13, [SP, #-76]
STR X13, [SP, #-76]
ADD X12, X13, #1
STR X14, [SP, #-80]
STR X10, [SP, #-8]
STR X14, [SP, #-8]
B %label.tmp_label.0
%label.tmp_label.2:
STR X9, [SP, #-84]
LDR X15, [SP, #-88]
STR X15, [SP, #-92]
LDR X9, [SP, #-88]
LDR X19, [SP, #-88]
STR X19, [SP, #-20]
MOV X0, X19
    /; Function epilogue
    ADD sp, sp, #96
      ;.endmodule
.module start
@func.getNumPos :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP
    sub sp, sp, #96      // Allocate stack space

%label.entry.1:
STR X20, [SP, #-96]
SUB SP, SP, #-100
MOV X20, SP
STR X20, [SP, #-100]
STR #1, [SP, #-100]
STR X21, [SP, #-76]
SUB SP, SP, #-104
MOV X21, SP
STR X21, [SP, #-104]
STR XZR, [SP, #-104]
%label.tmp_label.5:
STR X22, [SP, #-104]
STR X21, [SP, #-104]
STR X22, [SP, #-104]
STR X23, [SP, #-96]
STR X21, [SP, #-104]
STR X23, [SP, #-104]
STR X24, [SP, #-104]
STR X21, [SP, #-104]
STR X24, [SP, #-104]
STR X21, [SP, #-104]
LDR X25, [SP, #-108]
STR X25, [SP, #-60]
LDR X21, [SP, #-108]
STR X26, [SP, #-68]
STR X27, [SP, #-112]
LDR X28, [SP, #-108]
STR X28, [SP, #-116]
STR X9, [SP, #-4]
CMP X28, X9
CSET X26, LT
STR X10, [SP, #-8]
STR X11, [SP, #-76]
ZEXT X10, X11
STR X12, [SP, #-120]
STR X13, [SP, #-76]
TRUNC X12, X13
STR X14, [SP, #-120]
CBZ X14, %label.tmp_label.6
CBNZ X14, %label.tmp_label.7
%label.tmp_label.6:
STR X15, [SP, #-88]
STR X19, [SP, #-88]
SDIV X15, X19, #16
STR X21, [SP, #-104]
LDR X20, [SP, #-124]
STR X20, [SP, #-100]
LDR X21, [SP, #-124]
STR X21, [SP, #-104]
LDR X21, [SP, #-128]
STR X21, [SP, #-104]
LDR X21, [SP, #-128]
STR X22, [SP, #-132]
LDR X23, [SP, #-128]
STR X23, [SP, #-136]
ADD X22, X23, #1
STR X24, [SP, #-140]
STR X21, [SP, #-128]
STR X24, [SP, #-104]
B %label.tmp_label.5
%label.tmp_label.7:
STR X25, [SP, #-108]
STR X26, [SP, #-140]
STR X27, [SP, #-144]
SDIV X26, X27, #16
MUL X26, X26, #16
SUB X25, X25, X26
STR X28, [SP, #-108]
MOV X0, X28
    /; Function epilogue
    ADD sp, sp, #144
      ;.endmodule
.module start
@func.radixSort :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP
    sub sp, sp, #144      // Allocate stack space

%label.entry.2:
STR X9, [SP, #-148]
SUB SP, SP, #-212
MOV X9, SP
STR X10, [SP, #-216]
SUB SP, SP, #-280
MOV X10, SP
STR X11, [SP, #-140]
SUB SP, SP, #-344
MOV X11, SP
STR X12, [SP, #-344]
STR X13, [SP, #-216]
ADD X12, X13, #1
STR X14, [SP, #-344]
STR X15, [SP, #-348]
STR X19, [SP, #-352]
STR X20, [SP, #-124]
CMP X19, X20
CSET X14, GE
STR X21, [SP, #-104]
STR X22, [SP, #-356]
ZEXT X21, X22
STR X23, [SP, #-128]
STR X24, [SP, #-356]
STR X25, [SP, #-360]
CMP X25, #-1
CSET X23, EQ
STR X26, [SP, #-364]
STR X27, [SP, #-352]
ZEXT X26, X27
STR X28, [SP, #-360]
STR X9, [SP, #-212]
STR X10, [SP, #-280]
OR X28, X9, X10
STR X11, [SP, #-344]
STR X12, [SP, #-368]
TRUNC X11, X12
STR X13, [SP, #-372]
CBZ X13, %label.tmp_label.8
CBNZ X13, %label.tmp_label.9
%label.tmp_label.8:
    /; Function epilogue
    ADD sp, sp, #384
      ;Deallocate stack space
    LDP x29, x30, [sp], #16
      ;Restore FP and LR

RET

%label.tmp_label.9:
SUB SP, SP, #-376
MOV , SP
LDR X14, [SP, #-372]
STR X14, [SP, #-376]
STR X14, [SP, #-376]
%label.tmp_label.10:
STR X15, [SP, #-380]
STR X15, [SP, #-376]
STR X19, [SP, #-368]
STR X19, [SP, #-376]
STR X20, [SP, #-384]
STR X20, [SP, #-376]
STR X21, [SP, #-388]
STR X21, [SP, #-376]
STR X22, [SP, #-376]
LDR X23, [SP, #-392]
STR X23, [SP, #-392]
STR X22, [SP, #-392]
STR X24, [SP, #-396]
LDR X25, [SP, #-400]
STR X25, [SP, #-404]
STR X24, [SP, #-400]
STR X26, [SP, #-408]
STR X26, [SP, #-376]
LDR X27, [SP, #-412]
STR X27, [SP, #-392]
LDR , [SP, #-412]
STR X28, [SP, #-416]
STR X9, [SP, #-420]
LDR X10, [SP, #-412]
STR X10, [SP, #-424]
LDR X11, [SP, #-384]
STR X11, [SP, #-424]
CMP X10, X11
CSET X28, LT
STR X12, [SP, #-428]
STR X13, [SP, #-424]
ZEXT X12, X13
STR X14, [SP, #-372]
STR X15, [SP, #-432]
TRUNC X14, X15
STR X19, [SP, #-436]
CBZ X19, %label.tmp_label.11
CBNZ X19, %label.tmp_label.12
%label.tmp_label.11:
LDR X20, [SP, #-440]
STR X20, [SP, #-444]
LDR , [SP, #-440]
STR X21, [SP, #-448]
STR X0, [SP, #-64]
MOV X0, X1
LDR X1, [SP, #-404]
STR X1, [SP, #-452]
MOV X1, X2
BL @func.getNumPos
MOV X21, X0
STR X11, [SP, #-384]
STR X25, [SP, #-400]
LDR X22, [SP, #-456]
STR X22, [SP, #-460]
LDR X25, [SP, #-456]
LDR X23, [SP, #-464]
STR X23, [SP, #-392]
LDR , [SP, #-464]
STR X24, [SP, #-468]
STR X2, [SP, #-352]
MOV X2, X1
LDR X3, [SP, #-404]
STR X3, [SP, #-148]
MOV X3, X2
BL @func.getNumPos
MOV X24, X0
STR X11, [SP, #-344]
STR X23, [SP, #-464]
LDR X25, [SP, #-472]
STR X25, [SP, #-400]
LDR X23, [SP, #-472]
STR X26, [SP, #-476]
LDR X27, [SP, #-472]
STR X27, [SP, #-412]
ADD X26, X27, #1
STR X28, [SP, #-476]
STR X25, [SP, #-472]
STR X28, [SP, #-400]
LDR X9, [SP, #-480]
STR X9, [SP, #-484]
LDR , [SP, #-480]
LDR X10, [SP, #-488]
STR X10, [SP, #-412]
LDR , [SP, #-488]
STR X11, [SP, #-344]
LDR X12, [SP, #-488]
STR X12, [SP, #-492]
ADD X11, X12, #1
STR X13, [SP, #-476]
STR X13, [SP, #-376]
B %label.tmp_label.10
%label.tmp_label.12:
STR X9, [SP, #-480]
LDR X14, [SP, #-212]
STR X14, [SP, #-492]
LDR X15, [SP, #-496]
STR X15, [SP, #-492]
LDR X14, [SP, #-496]
LDR X19, [SP, #-372]
STR X19, [SP, #-492]
STR X14, [SP, #-212]
STR X19, [SP, #-212]
STR X10, [SP, #-488]
LDR X20, [SP, #-280]
STR X20, [SP, #-440]
LDR X21, [SP, #-500]
STR X21, [SP, #-504]
LDR X20, [SP, #-500]
STR X11, [SP, #-508]
LDR X22, [SP, #-344]
STR X22, [SP, #-456]
LDR X23, [SP, #-512]
STR X23, [SP, #-392]
LDR X22, [SP, #-512]
STR X24, [SP, #-516]
LDR X25, [SP, #-372]
STR X25, [SP, #-400]
LDR X26, [SP, #-512]
STR X26, [SP, #-520]
ADD X24, X25, X26
STR X27, [SP, #-472]
STR X20, [SP, #-280]
STR X27, [SP, #-280]
LDR X28, [SP, #-524]
STR X28, [SP, #-520]
LDR , [SP, #-524]
STR #1, [SP, #-376]
%label.tmp_label.13:
STR X9, [SP, #-212]
STR X9, [SP, #-376]
STR X10, [SP, #-280]
STR X10, [SP, #-376]
STR X11, [SP, #-344]
STR X11, [SP, #-376]
STR X12, [SP, #-488]
STR X12, [SP, #-376]
STR X13, [SP, #-508]
LDR X14, [SP, #-528]
STR X14, [SP, #-212]
STR X13, [SP, #-528]
STR X15, [SP, #-496]
LDR X19, [SP, #-532]
STR X19, [SP, #-372]
STR X15, [SP, #-532]
STR X20, [SP, #-280]
STR X20, [SP, #-376]
STR X21, [SP, #-500]
LDR X22, [SP, #-536]
STR X22, [SP, #-344]
STR X21, [SP, #-536]
STR X23, [SP, #-512]
LDR X24, [SP, #-540]
STR X24, [SP, #-544]
STR X23, [SP, #-540]
STR X25, [SP, #-372]
STR X25, [SP, #-376]
STR X26, [SP, #-512]
STR X26, [SP, #-376]
STR X27, [SP, #-544]
STR X27, [SP, #-376]
STR X28, [SP, #-524]
LDR X9, [SP, #-548]
STR X9, [SP, #-552]
STR X28, [SP, #-548]
LDR X10, [SP, #-556]
STR X10, [SP, #-560]
LDR , [SP, #-556]
STR X11, [SP, #-564]
STR X12, [SP, #-568]
LDR X13, [SP, #-556]
STR X13, [SP, #-572]
CMP X13, #16
CSET X11, LT
STR X14, [SP, #-528]
STR X15, [SP, #-576]
ZEXT X14, X15
STR X19, [SP, #-532]
STR X20, [SP, #-580]
TRUNC X19, X20
STR X21, [SP, #-584]
CBZ X21, %label.tmp_label.14
CBNZ X21, %label.tmp_label.15
%label.tmp_label.14:
LDR X22, [SP, #-588]
STR X22, [SP, #-536]
LDR , [SP, #-588]
STR X9, [SP, #-548]
STR X9, [SP, #-212]
LDR X23, [SP, #-592]
STR X23, [SP, #-596]
LDR X9, [SP, #-592]
LDR X24, [SP, #-600]
STR X24, [SP, #-540]
LDR , [SP, #-600]
STR X25, [SP, #-604]
LDR X26, [SP, #-600]
STR X26, [SP, #-608]
SUB X25, X26, #1
STR X10, [SP, #-556]
STR X14, [SP, #-612]
LDR X27, [SP, #-616]
STR X27, [SP, #-620]
LDR X14, [SP, #-616]
LDR X28, [SP, #-616]
STR X28, [SP, #-624]
STR X9, [SP, #-548]
STR X28, [SP, #-548]
LDR X9, [SP, #-628]
STR X9, [SP, #-548]
LDR , [SP, #-628]
STR X10, [SP, #-280]
STR X19, [SP, #-628]
LDR X10, [SP, #-632]
STR X10, [SP, #-280]
LDR X19, [SP, #-632]
LDR X11, [SP, #-636]
STR X11, [SP, #-636]
LDR , [SP, #-636]
STR X11, [SP, #-636]
STR X22, [SP, #-588]
LDR X12, [SP, #-640]
STR X12, [SP, #-644]
LDR X22, [SP, #-640]
LDR X13, [SP, #-648]
STR X13, [SP, #-556]
LDR , [SP, #-648]
STR X9, [SP, #-628]
STR X24, [SP, #-600]
LDR X14, [SP, #-652]
STR X14, [SP, #-528]
LDR X24, [SP, #-652]
STR X15, [SP, #-636]
LDR X19, [SP, #-652]
STR X19, [SP, #-532]
LDR X20, [SP, #-640]
STR X20, [SP, #-612]
ADD X15, X19, X20
STR X21, [SP, #-628]
STR X19, [SP, #-652]
STR X21, [SP, #-532]
LDR X22, [SP, #-656]
STR X22, [SP, #-536]
LDR , [SP, #-656]
LDR X23, [SP, #-660]
STR X23, [SP, #-592]
LDR , [SP, #-660]
STR X24, [SP, #-540]
LDR X25, [SP, #-660]
STR X25, [SP, #-664]
ADD X24, X25, #1
STR X26, [SP, #-600]
STR X26, [SP, #-376]
B %label.tmp_label.13
%label.tmp_label.15:
LDR X27, [SP, #-668]
STR X27, [SP, #-616]
LDR , [SP, #-668]
STR XZR, [SP, #-376]
%label.tmp_label.16:
STR X28, [SP, #-616]
STR X28, [SP, #-376]
STR X9, [SP, #-212]
STR X9, [SP, #-376]
LDR X10, [SP, #-672]
STR X10, [SP, #-632]
LDR , [SP, #-672]
STR X11, [SP, #-344]
STR X12, [SP, #-640]
LDR X13, [SP, #-672]
STR X13, [SP, #-648]
CMP X13, #16
CSET X11, LT
STR X14, [SP, #-652]
STR X15, [SP, #-676]
ZEXT X14, X15
STR X19, [SP, #-532]
STR X20, [SP, #-640]
TRUNC X19, X20
STR X21, [SP, #-676]
CBZ X21, %label.tmp_label.17
CBNZ X21, %label.tmp_label.18
%label.tmp_label.17:
%label.tmp_label.18:
SUB SP, SP, #-680
MOV , SP
LDR X22, [SP, #-372]
STR X22, [SP, #-656]
STR X22, [SP, #-680]
STR X9, [SP, #-684]
LDR X23, [SP, #-212]
STR X23, [SP, #-660]
LDR X24, [SP, #-688]
STR X24, [SP, #-692]
LDR X23, [SP, #-688]
LDR X25, [SP, #-372]
STR X25, [SP, #-660]
STR X23, [SP, #-212]
STR X25, [SP, #-212]
STR X10, [SP, #-672]
LDR X26, [SP, #-280]
STR X26, [SP, #-692]
LDR X27, [SP, #-696]
STR X27, [SP, #-668]
LDR X26, [SP, #-696]
STR X11, [SP, #-696]
LDR X28, [SP, #-344]
STR X28, [SP, #-700]
LDR X9, [SP, #-704]
STR X9, [SP, #-212]
LDR X28, [SP, #-704]
STR X10, [SP, #-280]
LDR X11, [SP, #-372]
STR X11, [SP, #-344]
LDR X12, [SP, #-704]
STR X12, [SP, #-708]
ADD X10, X11, X12
STR X13, [SP, #-672]
STR X26, [SP, #-280]
STR X13, [SP, #-280]
LDR X14, [SP, #-712]
STR X14, [SP, #-716]
LDR , [SP, #-712]
STR XZR, [SP, #-680]
%label.tmp_label.25:
STR X15, [SP, #-696]
STR X15, [SP, #-680]
STR X19, [SP, #-716]
LDR X20, [SP, #-720]
STR X20, [SP, #-716]
STR X19, [SP, #-720]
STR X21, [SP, #-716]
STR X21, [SP, #-680]
STR X22, [SP, #-372]
STR X22, [SP, #-680]
STR X23, [SP, #-212]
STR X23, [SP, #-680]
STR X24, [SP, #-688]
STR X24, [SP, #-680]
STR X25, [SP, #-372]
STR X25, [SP, #-680]
STR X26, [SP, #-280]
STR X26, [SP, #-680]
STR X27, [SP, #-696]
STR X27, [SP, #-680]
STR X28, [SP, #-344]
STR X28, [SP, #-680]
STR X9, [SP, #-704]
LDR X10, [SP, #-724]
STR X10, [SP, #-728]
STR X9, [SP, #-724]
STR X11, [SP, #-372]
STR X11, [SP, #-680]
STR X12, [SP, #-704]
LDR X13, [SP, #-732]
STR X13, [SP, #-728]
STR X12, [SP, #-732]
STR X14, [SP, #-712]
LDR X15, [SP, #-736]
STR X15, [SP, #-740]
STR X14, [SP, #-736]
STR X19, [SP, #-744]
LDR X20, [SP, #-748]
STR X20, [SP, #-720]
STR X19, [SP, #-748]
STR X21, [SP, #-752]
LDR X22, [SP, #-756]
STR X22, [SP, #-760]
STR X21, [SP, #-756]
STR X23, [SP, #-764]
LDR X24, [SP, #-768]
STR X24, [SP, #-772]
STR X23, [SP, #-768]
STR X25, [SP, #-776]
STR X25, [SP, #-680]
LDR X26, [SP, #-780]
STR X26, [SP, #-784]
LDR , [SP, #-780]
STR X27, [SP, #-788]
STR X28, [SP, #-792]
LDR X9, [SP, #-780]
STR X9, [SP, #-796]
CMP X9, #16
CSET X27, LT
STR X10, [SP, #-724]
STR X11, [SP, #-800]
ZEXT X10, X11
STR X12, [SP, #-804]
STR X13, [SP, #-732]
TRUNC X12, X13
STR X14, [SP, #-808]
CBZ X14, %label.tmp_label.26
CBNZ X14, %label.tmp_label.27
%label.tmp_label.26:
LDR X15, [SP, #-812]
STR X15, [SP, #-736]
LDR , [SP, #-812]
STR X19, [SP, #-816]
STR X20, [SP, #-748]
LDR X21, [SP, #-812]
STR X21, [SP, #-820]
CMP X21, XZR
CSET X19, GT
STR X22, [SP, #-756]
STR X23, [SP, #-824]
ZEXT X22, X23
STR X24, [SP, #-768]
STR X25, [SP, #-828]
TRUNC X24, X25
STR X26, [SP, #-780]
CBZ X26, %label.tmp_label.28
CBNZ X26, %label.tmp_label.29
%label.tmp_label.28:
LDR X27, [SP, #-832]
STR X27, [SP, #-832]
LDR , [SP, #-832]
STR X9, [SP, #-780]
STR X20, [SP, #-836]
LDR X28, [SP, #-840]
STR X28, [SP, #-844]
LDR X20, [SP, #-840]
LDR X9, [SP, #-848]
STR X9, [SP, #-212]
LDR , [SP, #-848]
STR X10, [SP, #-852]
LDR X11, [SP, #-848]
STR X11, [SP, #-832]
SUB X10, X11, #1
STR X10, [SP, #-856]
STR X10, [SP, #-280]
LDR X12, [SP, #-860]
STR X12, [SP, #-860]
LDR X10, [SP, #-860]
LDR X13, [SP, #-860]
STR X13, [SP, #-852]
STR X20, [SP, #-720]
STR X13, [SP, #-720]
LDR X14, [SP, #-864]
STR X14, [SP, #-860]
LDR , [SP, #-864]
STR X10, [SP, #-724]
STR X13, [SP, #-860]
LDR X15, [SP, #-868]
STR X15, [SP, #-812]
LDR X13, [SP, #-868]
LDR X19, [SP, #-872]
STR X19, [SP, #-872]
LDR , [SP, #-872]
STR X11, [SP, #-848]
STR X15, [SP, #-868]
LDR X20, [SP, #-876]
STR X20, [SP, #-720]
LDR X15, [SP, #-876]
LDR X21, [SP, #-880]
STR X21, [SP, #-812]
LDR , [SP, #-880]
STR X9, [SP, #-848]
STR X20, [SP, #-876]
LDR X22, [SP, #-884]
STR X22, [SP, #-888]
LDR X20, [SP, #-884]
STR X23, [SP, #-872]
LDR X24, [SP, #-884]
STR X24, [SP, #-888]
LDR X25, [SP, #-876]
STR X25, [SP, #-888]
ADD X23, X24, X25
STR X26, [SP, #-888]
STR X13, [SP, #-732]
STR X26, [SP, #-732]
%label.tmp_label.29:
STR X27, [SP, #-832]
STR X20, [SP, #-748]
STR X27, [SP, #-720]
STR X28, [SP, #-840]
STR X28, [SP, #-680]
STR X9, [SP, #-212]
STR X9, [SP, #-680]
STR X10, [SP, #-280]
STR X10, [SP, #-680]
STR X11, [SP, #-344]
STR X11, [SP, #-680]
STR X12, [SP, #-860]
STR X10, [SP, #-892]
STR X12, [SP, #-724]
STR X13, [SP, #-732]
STR X13, [SP, #-680]
STR X14, [SP, #-864]
STR X13, [SP, #-896]
STR X14, [SP, #-732]
STR X15, [SP, #-736]
STR X15, [SP, #-900]
STR X15, [SP, #-736]
STR X19, [SP, #-872]
STR X20, [SP, #-720]
STR X19, [SP, #-748]
STR X20, [SP, #-748]
LDR X21, [SP, #-404]
STR X21, [SP, #-880]
SUB X20, X21, #1
LDR X22, [SP, #-904]
STR X22, [SP, #-884]
LDR , [SP, #-904]
STR X9, [SP, #-908]
STR X22, [SP, #-904]
LDR X23, [SP, #-912]
STR X23, [SP, #-916]
LDR X22, [SP, #-912]
LDR X24, [SP, #-920]
STR X24, [SP, #-884]
LDR , [SP, #-920]
STR X10, [SP, #-724]
STR X24, [SP, #-920]
LDR X25, [SP, #-924]
STR X25, [SP, #-876]
LDR X24, [SP, #-924]
STR X4, [SP, #-404]
MOV X4, X1
LDR X5, [SP, #-912]
STR X5, [SP, #-928]
MOV X5, X2
LDR X6, [SP, #-924]
STR X6, [SP, #-372]
MOV X6, X3
BL @func.radixSort
LDR X26, [SP, #-932]
STR X26, [SP, #-916]
LDR , [SP, #-932]
LDR X27, [SP, #-936]
STR X27, [SP.endmodule
.module start
@func.main :
    ;Function prologue
    stp x29, x30, [sp, #-16]!  // Save FP and LR
    mov x29, sp                                    // Set new FP
    sub sp, sp, #944      // Allocate stack space

%label.entry.3:
STR X11, [SP, #-948]
SUB SP, SP, #-952
MOV X11, SP
STR X11, [SP, #-952]
STR #30000010, [SP, #-952]
STR X11, [SP, #-952]
LDR X12, [SP, #-956]
STR X12, [SP, #-960]
LDR X11, [SP, #-956]
LDR X7, [SP, #-956]
STR X7, [SP, #-384]
MOV X7, X1
BL @func.radixSort
STR X13, [SP, #-732]
SUB SP, SP, #-964
MOV X13, SP
STR X13, [SP, #-964]
STR XZR, [SP, #-964]
%label.tmp_label.30:
STR X14, [SP, #-968]
STR X11, [SP, #-952]
STR X14, [SP, #-952]
STR X15, [SP, #-736]
STR X13, [SP, #-964]
STR X15, [SP, #-964]
STR X19, [SP, #-972]
STR X19, [SP, #-976]
STR X20, [SP, #-980]
LDR X21, [SP, #-984]
STR X21, [SP, #-404]
STR X20, [SP, #-984]
STR X22, [SP, #-756]
STR X13, [SP, #-964]
STR X22, [SP, #-964]
STR X23, [SP, #-912]
STR X13, [SP, #-964]
STR X23, [SP, #-964]
STR X24, [SP, #-768]
STR X24, [SP, #-976]
STR X25, [SP, #-924]
STR X13, [SP, #-964]
STR X25, [SP, #-964]
STR X26, [SP, #-932]
STR X13, [SP, #-964]
STR X26, [SP, #-964]
STR X27, [SP, #-936]
STR X13, [SP, #-964]
STR X27, [SP, #-964]
STR X11, [SP, #-952]
LDR X28, [SP, #-988]
STR X28, [SP, #-992]
LDR X11, [SP, #-988]
STR X13, [SP, #-964]
LDR X9, [SP, #-996]
STR X9, [SP, #-936]
LDR X13, [SP, #-996]
STR X10, [SP, #-992]
STR X11, [SP, #-952]
LDR X12, [SP, #-996]
STR X12, [SP, #-956]
LDR X13, [SP, #-988]
STR X13, [SP, #-964]
CMP X12, X13
CSET X10, LT
STR X14, [SP, #-1000]
STR X15, [SP, #-1004]
ZEXT X14, X15
STR X19, [SP, #-1008]
STR X20, [SP, #-1012]
TRUNC X19, X20
STR X21, [SP, #-984]
CBZ X21, %label.tmp_label.31
CBNZ X21, %label.tmp_label.32
%label.tmp_label.31:
LDR X22, [SP, #-1016]
STR X22, [SP, #-1020]
LDR , [SP, #-1016]
STR X13, [SP, #-988]
LDR X23, [SP, #-1024]
STR X23, [SP, #-1028]
LDR X13, [SP, #-1024]
STR X24, [SP, #-1032]
LDR X25, [SP, #-1024]
STR X25, [SP, #-1036]
ADD X24, #2, X25
STR X13, [SP, #-964]
LDR X26, [SP, #-1040]
STR X26, [SP, #-1044]
LDR X13, [SP, #-1040]
STR X27, [SP, #-1048]
STR X21, [SP, #-120001088]
LDR X28, [SP, #-120001092]
STR X28, [SP, #-988]
LDR X21, [SP, #-120001092]
STR X9, [SP, #-996]
STR X10, [SP, #-120001092]
LDR X11, [SP, #-120001092]
STR X11, [SP, #-120001096]
STR X12, [SP, #-996]
SDIV X10, X11, X12
MUL X10, X10, X12
SUB X9, X9, X10
STR X13, [SP, #-964]
LDR X13, [SP, #-120001100]
STR X13, [SP, #-964]
LDR X13, [SP, #-120001100]
STR X14, [SP, #-120001104]
LDR X15, [SP, #-120001100]
STR X15, [SP, #-120001092]
STR X19, [SP, #-120001088]
MUL X14, X15, X19
LDR X20, [SP, #-120001108]
STR X20, [SP, #-120001104]
LDR , [SP, #-120001108]
STR X21, [SP, #-984]
LDR X22, [SP, #-120001108]
STR X22, [SP, #-1016]
STR X23, [SP, #-1024]
ADD X21, X22, X23
STR X24, [SP, #-120001112]
STR X24, [SP, #-976]
STR X13, [SP, #-120001100]
LDR X25, [SP, #-120001116]
STR X25, [SP, #-1024]
LDR X13, [SP, #-120001116]
STR X13, [SP, #-964]
LDR X26, [SP, #-120001120]
STR X26, [SP, #-1040]
LDR X13, [SP, #-120001120]
STR X27, [SP, #-120001088]
LDR X28, [SP, #-120001120]
STR X28, [SP, #-120001092]
ADD X27, X28, #1
STR X9, [SP, #-120001124]
STR X13, [SP, #-964]
STR X9, [SP, #-964]
B %label.tmp_label.30
%label.tmp_label.32:
LDR X10, [SP, #-120001128]
STR X10, [SP, #-120001132]
LDR , [SP, #-120001128]
STR X11, [SP, #-120001092]
STR X12, [SP, #-120001112]
LDR X13, [SP, #-120001128]
STR X13, [SP, #-964]
CMP X13, XZR
CSET X11, LT
STR X14, [SP, #-120001136]
STR X15, [SP, #-120001100]
ZEXT X14, X15
STR X19, [SP, #-120001124]
STR X20, [SP, #-120001108]
TRUNC X19, X20
STR X21, [SP, #-120001140]
CBZ X21, %label.tmp_label.33
CBNZ X21, %label.tmp_label.34
%label.tmp_label.33:
LDR X22, [SP, #-120001144]
STR X22, [SP, #-120001108]
LDR , [SP, #-120001144]
STR X23, [SP, #-120001136]
STR X24, [SP, #-120001140]
SUB X23, XZR, X24
STR X25, [SP, #-120001116]
STR X25, [SP, #-976]
%label.tmp_label.34:
STR X26, [SP, #-120001120]
STR X26, [SP, #-976]
MOV X0,.endmodule
 Function epilogue
    ADD sp, sp, #120001152
      ;Deallocate stack space
    LDP x29, x30, [sp], #16
      ;Restore FP and LR

RET

