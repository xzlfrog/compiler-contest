	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .data
	.global @a.scope0.id0
	.align 8
@a.scope0.id0:
	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .rodata
	.global @base
	.align 4
@base:
	.word 16
	.section .roda;.endmodule
;.module start
getMaxNum :
	; Function prologue
	STP X29, X30, [SP, #-16]!
	; Save FP and LR
	MOV X29, SP
	; Set new FP

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
	LDR X11, [SP, #-12]
	LDR X10, [SP, #-12]
	LDR X14, [SP, #-12]
	CMP X14, X15
CSET X12, LT
	ZEXT X19, X20
	TRUNC X21, X22
	CBZ X23, %label.tmp_label.1
	CBNZ X23, %label.tmp_label.2
%label.tmp_label.1:
	STR X9, [SP, #-4]
	LDR X24, [SP, #-16]
	LDR X9, [SP, #-16]
	STR X10, [SP, #-8]
	LDR X25, [SP, #-12]
	LDR X10, [SP, #-12]
	STR X1, [SP, #-20]
	LDR X26, [SP, #-20]
	LDR X27, [SP, #-24]
	LDR X26, [SP, #-24]
	STR X9, [SP, #-4]
	LDR X10, [SP, #-24]
	STR X10, [SP, #-8]
	LDR X11, [SP, #-16]
	STR X11, [SP, #-12]
	CMP X10, X11
CSET X28, GT
	STR X12, [SP, #-24]
	STR X13, [SP, #-28]
	ZEXT X12, X13
	STR X14, [SP, #-12]
	STR X15, [SP, #-32]
	TRUNC X14, X15
	STR X19, [SP, #-36]
	CBZ X19, %label.tmp_label.3
	CBNZ X19, %label.tmp_label.4
%label.tmp_label.3:
	STR X9, [SP, #-40]
	LDR X20, [SP, #-16]
	STR X20, [SP, #-24]
	LDR X9, [SP, #-16]
	STR X10, [SP, #-24]
	LDR X21, [SP, #-12]
	STR X21, [SP, #-40]
	LDR X10, [SP, #-12]
	STR X1, [SP, #-20]
	LDR X22, [SP, #-20]
	STR X22, [SP, #-36]
	LDR X23, [SP, #-44]
	STR X23, [SP, #-40]
	LDR X22, [SP, #-44]
	LDR X24, [SP, #-44]
	STR X24, [SP, #-16]
	STR X9, [SP, #-4]
	STR X24, [SP, #-4]
%label.tmp_label.4:
	STR X10, [SP, #-8]
	LDR X25, [SP, #-12]
	STR X25, [SP, #-12]
	LDR X10, [SP, #-12]
	STR X10, [SP, #-8]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-20]
	LDR X10, [SP, #-12]
	STR X27, [SP, #-24]
	LDR X28, [SP, #-12]
	STR X28, [SP, #-44]
	ADD X27, X28, #1
	STR X9, [SP, #-4]
	STR X10, [SP, #-8]
	STR X9, [SP, #-8]
	B %label.tmp_label.0
%label.tmp_label.2:
	STR X9, [SP, #-48]
	LDR X10, [SP, #-16]
	STR X10, [SP, #-8]
	LDR X9, [SP, #-16]
	LDR X11, [SP, #-16]
	STR X11, [SP, #-16]
	MOV X0, X11

	; Function epilogue
	ADD SP, SP, #48
	; Deallocate stac;.endmodule
;.module start
getNumPos :
	; Function prologue
	STP X29, X30, [SP, #-16]!
	; Save FP and LR
	MOV X29, SP
	; Set new FP
	SUB SP, SP, #48      // Allocate stack space

	STR X12, [SP, #-52]
	SUB SP, SP, #-56
	MOV X12, SP
	STR X12, [SP, #-56]
	STR #1, [SP, #-56]
	STR X13, [SP, #-44]
	SUB SP, SP, #-60
	MOV X13, SP
	STR X13, [SP, #-60]
	STR XZR, [SP, #-60]
%label.tmp_label.5:
	STR X13, [SP, #-60]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-60]
	LDR X13, [SP, #-12]
	STR X15, [SP, #-52]
	STR X19, [SP, #-60]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-16]
	STR X21, [SP, #-12]
	CMP X20, X21
CSET X15, LT
	STR X22, [SP, #-20]
	STR X23, [SP, #-44]
	ZEXT X22, X23
	STR X24, [SP, #-44]
	STR X25, [SP, #-12]
	TRUNC X24, X25
	STR X26, [SP, #-12]
	CBZ X26, %label.tmp_label.6
	CBNZ X26, %label.tmp_label.7
%label.tmp_label.6:
	STR X27, [SP, #-48]
	STR X28, [SP, #-12]
	SDIV X27, X28, #16
	STR X13, [SP, #-60]
	LDR X9, [SP, #-12]
	STR X9, [SP, #-4]
	LDR X13, [SP, #-12]
	STR X13, [SP, #-60]
	LDR X10, [SP, #-12]
	STR X10, [SP, #-16]
	LDR X13, [SP, #-12]
	STR X11, [SP, #-16]
	LDR X12, [SP, #-12]
	STR X12, [SP, #-56]
	ADD X11, X12, #1
	STR X13, [SP, #-60]
	STR X13, [SP, #-64]
	STR X13, [SP, #-60]
	B %label.tmp_label.5
%label.tmp_label.7:
	STR X14, [SP, #-12]
	STR X15, [SP, #-64]
	STR X19, [SP, #-68]
	SDIV X15, X19, #16
MUL X15, X15, #16
SUB X14, X14, X15
	STR X20, [SP, #-12]
	MOV X0, X20

	; Function epilogue
	ADD SP, SP, #80
	; Deallocate stac;.endmodule
;.module start
radixSort :
	; Function prologue
	STP X29, X30, [SP, #-16]!
	; Save FP and LR
	MOV X29, SP
	; Set new FP
	SUB SP, SP, #80      // Allocate stack space

	STR X21, [SP, #-72]
	SUB SP, SP, #-136
	MOV X21, SP
	STR X22, [SP, #-140]
	SUB SP, SP, #-204
	MOV X22, SP
	STR X23, [SP, #-64]
	SUB SP, SP, #-268
	MOV X23, SP
	STR X24, [SP, #-268]
	STR X25, [SP, #-140]
	ADD X24, X25, #1
	STR X26, [SP, #-268]
	STR X27, [SP, #-272]
	STR X28, [SP, #-276]
	STR X9, [SP, #-12]
	CMP X28, X9
CSET X26, GE
	STR X10, [SP, #-12]
	STR X11, [SP, #-64]
	ZEXT X10, X11
	STR X12, [SP, #-12]
	STR X13, [SP, #-60]
	STR X14, [SP, #-280]
	CMP X14, #-1
CSET X12, EQ
	STR X15, [SP, #-284]
	STR X19, [SP, #-276]
	ZEXT X15, X19
	STR X20, [SP, #-280]
	STR X21, [SP, #-136]
	STR X22, [SP, #-204]
	OR X20, X21, X22
	STR X23, [SP, #-268]
	STR X24, [SP, #-288]
	TRUNC X23, X24
	STR X25, [SP, #-292]
	CBZ X25, %label.tmp_label.8
	CBNZ X25, %label.tmp_label.9
%label.tmp_label.8:

	; Function epilogue
	ADD SP, SP, #304
	; Deallocate stack space
	LDP X29, X30, [SP], #16
	; Restore FP and LR

	RET
%label.tmp_label.9:
	STR X26, [SP, #-292]
	SUB SP, SP, #-296
	MOV X26, SP
	LDR X27, [SP, #-292]
	STR X27, [SP, #-300]
	STR X26, [SP, #-296]
	STR X27, [SP, #-296]
%label.tmp_label.10:
	STR X26, [SP, #-296]
	LDR X28, [SP, #-12]
	STR X28, [SP, #-288]
	LDR X26, [SP, #-12]
	STR X9, [SP, #-304]
	STR X10, [SP, #-308]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-292]
	LDR X12, [SP, #-304]
	STR X12, [SP, #-308]
	CMP X11, X12
CSET X9, LT
	STR X13, [SP, #-312]
	STR X14, [SP, #-316]
	ZEXT X13, X14
	STR X15, [SP, #-320]
	STR X19, [SP, #-308]
	TRUNC X15, X19
	STR X20, [SP, #-324]
	CBZ X20, %label.tmp_label.11
	CBNZ X20, %label.tmp_label.12
%label.tmp_label.11:
	STR X26, [SP, #-296]
	LDR X21, [SP, #-12]
	STR X21, [SP, #-320]
	LDR X26, [SP, #-12]
	STR X5, [SP, #-328]
	LDR X22, [SP, #-328]
	STR X22, [SP, #-308]
	LDR X23, [SP, #-332]
	STR X23, [SP, #-332]
	LDR X22, [SP, #-332]
	STR X24, [SP, #-324]
	LDR X0, [SP, #-332]
	STR X0, [SP, #-32]
	MOV X0, X1
	LDR X1, [SP, #-316]
	STR X1, [SP, #-20]
	MOV X1, X2
	BL getNumPos
	MOV X24, X0
	STR X23, [SP, #-332]
	LDR X25, [SP, #-268]
	STR X25, [SP, #-332]
	LDR X26, [SP, #-336]
	STR X26, [SP, #-296]
	LDR X25, [SP, #-336]
	STR X26, [SP, #-336]
	LDR X27, [SP, #-12]
	STR X27, [SP, #-292]
	LDR X26, [SP, #-12]
	STR X5, [SP, #-328]
	LDR X28, [SP, #-328]
	STR X28, [SP, #-12]
	LDR X9, [SP, #-340]
	STR X9, [SP, #-340]
	LDR X28, [SP, #-340]
	STR X10, [SP, #-344]
	LDR X2, [SP, #-340]
	STR X2, [SP, #-276]
	MOV X2, X1
	LDR X3, [SP, #-316]
	STR X3, [SP, #-72]
	MOV X3, X2
	BL getNumPos
	MOV X10, X0
	STR X23, [SP, #-268]
	LDR X11, [SP, #-268]
	STR X11, [SP, #-12]
	LDR X12, [SP, #-348]
	STR X12, [SP, #-304]
	LDR X11, [SP, #-348]
	STR X13, [SP, #-352]
	LDR X14, [SP, #-348]
	STR X14, [SP, #-340]
	ADD X13, X14, #1
	STR X15, [SP, #-352]
	STR X25, [SP, #-268]
	STR X15, [SP, #-268]
	STR X26, [SP, #-296]
	LDR X19, [SP, #-12]
	STR X19, [SP, #-352]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-352]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-12]
	LDR X22, [SP, #-12]
	STR X22, [SP, #-328]
	ADD X21, X22, #1
	STR X23, [SP, #-268]
	STR X26, [SP, #-296]
	STR X23, [SP, #-296]
	B %label.tmp_label.10
%label.tmp_label.12:
	STR X21, [SP, #-356]
	LDR X24, [SP, #-136]
	STR X24, [SP, #-360]
	LDR X25, [SP, #-364]
	STR X25, [SP, #-268]
	LDR X24, [SP, #-364]
	LDR X26, [SP, #-292]
	STR X26, [SP, #-296]
	STR X24, [SP, #-136]
	STR X26, [SP, #-136]
	STR X22, [SP, #-12]
	LDR X27, [SP, #-204]
	STR X27, [SP, #-12]
	LDR X28, [SP, #-368]
	STR X28, [SP, #-328]
	LDR X27, [SP, #-368]
	STR X23, [SP, #-356]
	LDR X9, [SP, #-268]
	STR X9, [SP, #-340]
	LDR X10, [SP, #-372]
	STR X10, [SP, #-376]
	LDR X9, [SP, #-372]
	STR X11, [SP, #-268]
	LDR X12, [SP, #-292]
	STR X12, [SP, #-348]
	LDR X13, [SP, #-372]
	STR X13, [SP, #-380]
	ADD X11, X12, X13
	STR X14, [SP, #-348]
	STR X27, [SP, #-204]
	STR X14, [SP, #-204]
	STR X26, [SP, #-292]
	LDR X15, [SP, #-12]
	STR X15, [SP, #-380]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	STR #1, [SP, #-296]
%label.tmp_label.13:
	STR X26, [SP, #-296]
	LDR X19, [SP, #-12]
	STR X19, [SP, #-12]
	LDR X26, [SP, #-12]
	STR X20, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X22, [SP, #-12]
	STR X22, [SP, #-204]
	CMP X22, #16
CSET X20, LT
	STR X23, [SP, #-268]
	STR X24, [SP, #-136]
	ZEXT X23, X24
	STR X25, [SP, #-364]
	STR X26, [SP, #-296]
	TRUNC X25, X26
	STR X27, [SP, #-204]
	CBZ X27, %label.tmp_label.14
	CBNZ X27, %label.tmp_label.15
%label.tmp_label.14:
	STR X26, [SP, #-384]
	LDR X28, [SP, #-12]
	STR X28, [SP, #-368]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-388]
	LDR X9, [SP, #-136]
	STR X9, [SP, #-268]
	LDR X10, [SP, #-392]
	STR X10, [SP, #-372]
	LDR X9, [SP, #-392]
	STR X26, [SP, #-296]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-396]
	LDR X26, [SP, #-12]
	STR X12, [SP, #-292]
	LDR X13, [SP, #-12]
	STR X13, [SP, #-372]
	SUB X12, X13, #1
	STR X22, [SP, #-12]
	LDR X14, [SP, #-204]
	STR X14, [SP, #-396]
	LDR X15, [SP, #-400]
	STR X15, [SP, #-12]
	LDR X14, [SP, #-400]
	LDR X19, [SP, #-400]
	STR X19, [SP, #-12]
	STR X9, [SP, #-136]
	STR X19, [SP, #-136]
	STR X26, [SP, #-296]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-400]
	LDR X26, [SP, #-12]
	STR X22, [SP, #-204]
	LDR X21, [SP, #-204]
	STR X21, [SP, #-136]
	LDR X22, [SP, #-404]
	STR X22, [SP, #-204]
	LDR X21, [SP, #-404]
	STR X26, [SP, #-296]
	LDR X23, [SP, #-12]
	STR X23, [SP, #-384]
	LDR X26, [SP, #-12]
	STR X23, [SP, #-12]
	LDR X24, [SP, #-268]
	STR X24, [SP, #-400]
	LDR X25, [SP, #-408]
	STR X25, [SP, #-408]
	LDR X24, [SP, #-408]
	STR X26, [SP, #-296]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-204]
	LDR X27, [SP, #-136]
	STR X27, [SP, #-408]
	LDR X28, [SP, #-412]
	STR X28, [SP, #-12]
	LDR X27, [SP, #-412]
	STR X9, [SP, #-136]
	LDR X10, [SP, #-412]
	STR X10, [SP, #-392]
	LDR X11, [SP, #-408]
	STR X11, [SP, #-12]
	ADD X9, X10, X11
	STR X12, [SP, #-416]
	STR X21, [SP, #-136]
	STR X12, [SP, #-204]
	STR X26, [SP, #-12]
	LDR X13, [SP, #-12]
	STR X13, [SP, #-12]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-204]
	LDR X26, [SP, #-12]
	STR X15, [SP, #-400]
	LDR X19, [SP, #-12]
	STR X19, [SP, #-400]
	ADD X15, X19, #1
	STR X20, [SP, #-12]
	STR X26, [SP, #-296]
	STR X20, [SP, #-296]
	B %label.tmp_label.13
%label.tmp_label.15:
	STR X26, [SP, #-296]
	LDR X21, [SP, #-12]
	STR X21, [SP, #-204]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	STR XZR, [SP, #-296]
%label.tmp_label.16:
	STR X26, [SP, #-296]
	LDR X22, [SP, #-12]
	STR X22, [SP, #-404]
	LDR X26, [SP, #-12]
	STR X23, [SP, #-268]
	STR X24, [SP, #-268]
	LDR X25, [SP, #-12]
	STR X25, [SP, #-408]
	CMP X25, #16
CSET X23, LT
	STR X26, [SP, #-296]
	STR X27, [SP, #-136]
	ZEXT X26, X27
	STR X28, [SP, #-412]
	STR X9, [SP, #-420]
	TRUNC X28, X9
	STR X10, [SP, #-412]
	CBZ X10, %label.tmp_label.17
	CBNZ X10, %label.tmp_label.18
%label.tmp_label.17:
%label.tmp_label.19:
	STR X26, [SP, #-424]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-408]
	LDR X26, [SP, #-12]
	STR X22, [SP, #-12]
	LDR X12, [SP, #-204]
	STR X12, [SP, #-420]
	LDR X13, [SP, #-428]
	STR X13, [SP, #-12]
	LDR X12, [SP, #-428]
	STR X26, [SP, #-296]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-12]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-12]
	LDR X15, [SP, #-136]
	STR X15, [SP, #-432]
	LDR X19, [SP, #-436]
	STR X19, [SP, #-12]
	LDR X15, [SP, #-436]
	STR X20, [SP, #-432]
	STR X21, [SP, #-136]
	LDR X22, [SP, #-436]
	STR X22, [SP, #-204]
	LDR X23, [SP, #-428]
	STR X23, [SP, #-436]
	CMP X22, X23
CSET X20, LT
	STR X24, [SP, #-440]
	STR X25, [SP, #-12]
	ZEXT X24, X25
	STR X26, [SP, #-296]
	STR X27, [SP, #-436]
	TRUNC X26, X27
	STR X28, [SP, #-440]
	CBZ X28, %label.tmp_label.20
	CBNZ X28, %label.tmp_label.21
%label.tmp_label.20:
	STR X9, [SP, #-424]
	SUB SP, SP, #-444
	MOV X9, SP
	STR X26, [SP, #-444]
	LDR X10, [SP, #-12]
	STR X10, [SP, #-440]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-448]
	LDR X11, [SP, #-136]
	STR X11, [SP, #-12]
	LDR X12, [SP, #-452]
	STR X12, [SP, #-204]
	LDR X11, [SP, #-452]
	STR X5, [SP, #-328]
	LDR X13, [SP, #-328]
	STR X13, [SP, #-428]
	LDR X14, [SP, #-456]
	STR X14, [SP, #-12]
	LDR X13, [SP, #-456]
	LDR X15, [SP, #-456]
	STR X15, [SP, #-136]
	STR X9, [SP, #-444]
	STR X15, [SP, #-444]
%label.tmp_label.22:
	STR X26, [SP, #-296]
	LDR X19, [SP, #-12]
	STR X19, [SP, #-436]
	LDR X26, [SP, #-12]
	STR X9, [SP, #-444]
	LDR X20, [SP, #-460]
	STR X20, [SP, #-460]
	LDR X9, [SP, #-460]
	STR X21, [SP, #-136]
	LDR X4, [SP, #-460]
	STR X4, [SP, #-316]
	MOV X4, X1
	LDR X5, [SP, #-316]
	STR X5, [SP, #-328]
	MOV X5, X2
	BL getNumPos
	MOV X21, X0
	STR X22, [SP, #-436]
	STR X23, [SP, #-428]
	STR X24, [SP, #-464]
	LDR X25, [SP, #-12]
	STR X25, [SP, #-460]
	CMP X24, X25
CSET X22, NE
	STR X26, [SP, #-296]
	STR X27, [SP, #-464]
	ZEXT X26, X27
	STR X28, [SP, #-444]
	STR X9, [SP, #-444]
	TRUNC X28, X9
	STR X10, [SP, #-12]
	CBZ X10, %label.tmp_label.23
	CBNZ X10, %label.tmp_label.24
%label.tmp_label.23:
	STR X11, [SP, #-136]
	SUB SP, SP, #-468
	MOV X11, SP
	STR X9, [SP, #-472]
	LDR X12, [SP, #-460]
	STR X12, [SP, #-452]
	LDR X9, [SP, #-460]
	LDR X13, [SP, #-460]
	STR X13, [SP, #-328]
	STR X11, [SP, #-468]
	STR X13, [SP, #-468]
	STR X9, [SP, #-444]
	LDR X14, [SP, #-460]
	STR X14, [SP, #-456]
	LDR X9, [SP, #-460]
	STR X11, [SP, #-468]
	LDR X15, [SP, #-476]
	STR X15, [SP, #-456]
	LDR X11, [SP, #-476]
	STR X19, [SP, #-12]
	LDR X6, [SP, #-476]
	STR X6, [SP, #-292]
	MOV X6, X1
	LDR X7, [SP, #-316]
	STR X7, [SP, #-304]
	MOV X7, X2
	BL getNumPos
	MOV X19, X0
	STR X21, [SP, #-480]
	LDR X20, [SP, #-136]
	STR X20, [SP, #-460]
	LDR X21, [SP, #-484]
	STR X21, [SP, #-136]
	LDR X20, [SP, #-484]
	STR X5, [SP, #-316]
	LDR X22, [SP, #-328]
	STR X22, [SP, #-484]
	LDR X23, [SP, #-488]
	STR X23, [SP, #-492]
	LDR X22, [SP, #-488]
	LDR X24, [SP, #-488]
	STR X24, [SP, #-480]
	STR X9, [SP, #-444]
	STR X24, [SP, #-444]
	STR X11, [SP, #-468]
	LDR X25, [SP, #-476]
	STR X25, [SP, #-12]
	LDR X11, [SP, #-476]
	STR X26, [SP, #-472]
	LDR X0, [SP, #-476]
	STR X0, [SP, #-332]
	MOV X0, X1
	LDR X1, [SP, #-316]
	STR X1, [SP, #-316]
	MOV X1, X2
	BL getNumPos
	MOV X26, X0
	STR X21, [SP, #-484]
	LDR X27, [SP, #-136]
	STR X27, [SP, #-484]
	LDR X28, [SP, #-496]
	STR X28, [SP, #-496]
	LDR X27, [SP, #-496]
	STR X5, [SP, #-328]
	LDR X9, [SP, #-328]
	STR X9, [SP, #-444]
	LDR X10, [SP, #-500]
	STR X10, [SP, #-496]
	LDR X9, [SP, #-500]
	STR X11, [SP, #-468]
	LDR X11, [SP, #-476]
	STR X11, [SP, #-468]
	LDR X11, [SP, #-476]
	LDR X12, [SP, #-476]
	STR X12, [SP, #-460]
	STR X9, [SP, #-328]
	STR X12, [SP, #-328]
	STR X11, [SP, #-476]
	LDR X13, [SP, #-476]
	STR X13, [SP, #-460]
	LDR X11, [SP, #-476]
	STR X14, [SP, #-460]
	LDR X2, [SP, #-476]
	STR X2, [SP, #-340]
	MOV X2, X1
	LDR X3, [SP, #-316]
	STR X3, [SP, #-316]
	MOV X3, X2
	BL getNumPos
	MOV X14, X0
	STR X21, [SP, #-136]
	LDR X15, [SP, #-136]
	STR X15, [SP, #-476]
	LDR X19, [SP, #-504]
	STR X19, [SP, #-508]
	LDR X15, [SP, #-504]
	STR X11, [SP, #-468]
	LDR X20, [SP, #-476]
	STR X20, [SP, #-136]
	LDR X11, [SP, #-476]
	STR X21, [SP, #-136]
	LDR X4, [SP, #-476]
	STR X4, [SP, #-460]
	MOV X4, X1
	LDR X5, [SP, #-316]
	STR X5, [SP, #-328]
	MOV X5, X2
	BL getNumPos
	MOV X21, X0
	STR X21, [SP, #-512]
	LDR X22, [SP, #-136]
	STR X22, [SP, #-328]
	LDR X23, [SP, #-516]
	STR X23, [SP, #-488]
	LDR X22, [SP, #-516]
	STR X24, [SP, #-488]
	LDR X25, [SP, #-516]
	STR X25, [SP, #-476]
	ADD X24, X25, #1
	STR X26, [SP, #-520]
	STR X15, [SP, #-136]
	STR X26, [SP, #-136]
	B %label.tmp_label.22
%label.tmp_label.24:
	STR X26, [SP, #-524]
	LDR X27, [SP, #-12]
	STR X27, [SP, #-136]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X28, [SP, #-136]
	STR X28, [SP, #-496]
	LDR X9, [SP, #-528]
	STR X9, [SP, #-328]
	LDR X28, [SP, #-528]
	STR X5, [SP, #-316]
	LDR X10, [SP, #-328]
	STR X10, [SP, #-500]
	LDR X11, [SP, #-532]
	STR X11, [SP, #-468]
	LDR X10, [SP, #-532]
	STR X9, [SP, #-528]
	LDR X12, [SP, #-460]
	STR X12, [SP, #-476]
	LDR X9, [SP, #-460]
	LDR X13, [SP, #-460]
	STR X13, [SP, #-476]
	STR X10, [SP, #-328]
	STR X13, [SP, #-328]
	STR X26, [SP, #-296]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-536]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X15, [SP, #-136]
	STR X15, [SP, #-136]
	LDR X19, [SP, #-540]
	STR X19, [SP, #-504]
	LDR X15, [SP, #-540]
	STR X26, [SP, #-296]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-476]
	LDR X26, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X21, [SP, #-136]
	STR X21, [SP, #-136]
	LDR X22, [SP, #-544]
	STR X22, [SP, #-136]
	LDR X21, [SP, #-544]
	STR X23, [SP, #-516]
	LDR X24, [SP, #-544]
	STR X24, [SP, #-524]
	ADD X23, X24, #1
	STR X25, [SP, #-516]
	STR X15, [SP, #-136]
	STR X25, [SP, #-136]
	B %label.tmp_label.19
%label.tmp_label.21:
	STR X26, [SP, #-296]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-296]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-12]
	LDR X27, [SP, #-12]
	STR X27, [SP, #-12]
	LDR X26, [SP, #-12]
	STR X28, [SP, #-136]
	LDR X9, [SP, #-12]
	STR X9, [SP, #-444]
	ADD X28, X9, #1
	STR X10, [SP, #-328]
	STR X26, [SP, #-296]
	STR X10, [SP, #-296]
	B %label.tmp_label.16
%label.tmp_label.18:
	STR X11, [SP, #-532]
	SUB SP, SP, #-548
	MOV X11, SP
	LDR X12, [SP, #-292]
	STR X12, [SP, #-460]
	STR X11, [SP, #-548]
	STR X12, [SP, #-548]
	STR X21, [SP, #-136]
	LDR X13, [SP, #-136]
	STR X13, [SP, #-460]
	LDR X14, [SP, #-552]
	STR X14, [SP, #-12]
	LDR X13, [SP, #-552]
	LDR X15, [SP, #-292]
	STR X15, [SP, #-136]
	STR X13, [SP, #-136]
	STR X15, [SP, #-136]
	STR X22, [SP, #-544]
	LDR X19, [SP, #-204]
	STR X19, [SP, #-540]
	LDR X20, [SP, #-556]
	STR X20, [SP, #-12]
	LDR X19, [SP, #-556]
	STR X23, [SP, #-560]
	LDR X21, [SP, #-268]
	STR X21, [SP, #-136]
	LDR X22, [SP, #-564]
	STR X22, [SP, #-204]
	LDR X21, [SP, #-564]
	STR X23, [SP, #-268]
	LDR X24, [SP, #-292]
	STR X24, [SP, #-544]
	LDR X25, [SP, #-564]
	STR X25, [SP, #-560]
	ADD X23, X24, X25
	STR X26, [SP, #-296]
	STR X19, [SP, #-204]
	STR X26, [SP, #-204]
	STR X11, [SP, #-548]
	LDR X27, [SP, #-12]
	STR X27, [SP, #-12]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-548]
	STR XZR, [SP, #-548]
%label.tmp_label.25:
	STR X11, [SP, #-548]
	LDR X28, [SP, #-12]
	STR X28, [SP, #-568]
	LDR X11, [SP, #-12]
	STR X9, [SP, #-12]
	STR X10, [SP, #-568]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-548]
	CMP X11, #16
CSET X9, LT
	STR X12, [SP, #-292]
	STR X13, [SP, #-136]
	ZEXT X12, X13
	STR X14, [SP, #-552]
	STR X15, [SP, #-292]
	TRUNC X14, X15
	STR X19, [SP, #-204]
	CBZ X19, %label.tmp_label.26
	CBNZ X19, %label.tmp_label.27
%label.tmp_label.26:
	STR X11, [SP, #-12]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-556]
	LDR X11, [SP, #-12]
	STR X21, [SP, #-268]
	STR X22, [SP, #-564]
	LDR X23, [SP, #-12]
	STR X23, [SP, #-572]
	CMP X23, XZR
CSET X21, GT
	STR X24, [SP, #-292]
	STR X25, [SP, #-564]
	ZEXT X24, X25
	STR X26, [SP, #-572]
	STR X27, [SP, #-12]
	TRUNC X26, X27
	STR X28, [SP, #-12]
	CBZ X28, %label.tmp_label.28
	CBNZ X28, %label.tmp_label.29
%label.tmp_label.28:
	STR X11, [SP, #-548]
	LDR X9, [SP, #-12]
	STR X9, [SP, #-572]
	LDR X11, [SP, #-12]
	STR X21, [SP, #-572]
	LDR X10, [SP, #-136]
	STR X10, [SP, #-576]
	LDR X11, [SP, #-580]
	STR X11, [SP, #-548]
	LDR X10, [SP, #-580]
	STR X11, [SP, #-580]
	LDR X12, [SP, #-12]
	STR X12, [SP, #-584]
	LDR X11, [SP, #-12]
	STR X13, [SP, #-572]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-584]
	SUB X13, X14, #1
	STR X22, [SP, #-588]
	LDR X15, [SP, #-204]
	STR X15, [SP, #-584]
	LDR X19, [SP, #-592]
	STR X19, [SP, #-584]
	LDR X15, [SP, #-592]
	LDR X20, [SP, #-592]
	STR X20, [SP, #-12]
	STR X10, [SP, #-136]
	STR X20, [SP, #-136]
	STR X11, [SP, #-548]
	LDR X21, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X11, [SP, #-12]
	STR X22, [SP, #-204]
	LDR X22, [SP, #-204]
	STR X22, [SP, #-204]
	LDR X23, [SP, #-596]
	STR X23, [SP, #-12]
	LDR X22, [SP, #-596]
	STR X11, [SP, #-548]
	LDR X24, [SP, #-12]
	STR X24, [SP, #-600]
	LDR X11, [SP, #-12]
	STR X23, [SP, #-596]
	LDR X25, [SP, #-268]
	STR X25, [SP, #-572]
	LDR X26, [SP, #-604]
	STR X26, [SP, #-604]
	LDR X25, [SP, #-604]
	STR X11, [SP, #-548]
	LDR X27, [SP, #-12]
	STR X27, [SP, #-600]
	LDR X11, [SP, #-12]
	STR X21, [SP, #-12]
	LDR X28, [SP, #-136]
	STR X28, [SP, #-604]
	LDR X9, [SP, #-608]
	STR X9, [SP, #-12]
	LDR X28, [SP, #-608]
	STR X10, [SP, #-136]
	LDR X11, [SP, #-608]
	STR X11, [SP, #-548]
	LDR X12, [SP, #-604]
	STR X12, [SP, #-12]
	ADD X10, X11, X12
	STR X13, [SP, #-612]
	STR X22, [SP, #-204]
	STR X13, [SP, #-204]
%label.tmp_label.29:
	STR X14, [SP, #-12]
	LDR X15, [SP, #-316]
	STR X15, [SP, #-204]
	SUB X14, X15, #1
	STR X11, [SP, #-608]
	LDR X19, [SP, #-12]
	STR X19, [SP, #-592]
	LDR X11, [SP, #-12]
	STR X21, [SP, #-136]
	LDR X20, [SP, #-136]
	STR X20, [SP, #-592]
	LDR X21, [SP, #-616]
	STR X21, [SP, #-136]
	LDR X20, [SP, #-616]
	STR X11, [SP, #-548]
	LDR X22, [SP, #-12]
	STR X22, [SP, #-204]
	LDR X11, [SP, #-12]
	STR X22, [SP, #-12]
	LDR X23, [SP, #-204]
	STR X23, [SP, #-268]
	LDR X24, [SP, #-620]
	STR X24, [SP, #-12]
	LDR X23, [SP, #-620]
	STR X6, [SP, #-476]
	MOV X6, X1
	LDR X7, [SP, #-616]
	STR X7, [SP, #-316]
	MOV X7, X2
	LDR X0, [SP, #-620]
	STR X0, [SP, #-476]
	MOV X0, X3
	BL radixSort
	STR X11, [SP, #-548]
	LDR X25, [SP, #-12]
	STR X25, [SP, #-268]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-548]
	LDR X26, [SP, #-12]
	STR X26, [SP, #-604]
	LDR X11, [SP, #-12]
	STR X27, [SP, #-12]
	LDR X28, [SP, #-12]
	STR X28, [S;.endmodule
;.module start
main :
	; Function prologue
	STP X29, X30, [SP, #-16]!
	; Save FP and LR
	MOV X29, SP
	; Set new FP
	SUB SP, SP, #624      // Allocate stack space

	STR X10, [SP, #-624]
	SUB SP, SP, #-628
	MOV X10, SP
	STR X10, [SP, #-628]
	STR #30000010, [SP, #-628]
	BL starttime
	STR X10, [SP, #-628]
	LDR X11, [SP, #-632]
	STR X11, [SP, #-548]
	LDR X10, [SP, #-632]
	LDR X1, [SP, #-632]
	STR X1, [SP, #-316]
	MOV X1, X1
	BL radixSort
	STR X12, [SP, #-604]
	SUB SP, SP, #-636
	MOV X12, SP
	STR X12, [SP, #-636]
	STR XZR, [SP, #-636]
%label.tmp_label.30:
	STR X10, [SP, #-628]
	LDR X13, [SP, #-632]
	STR X13, [SP, #-624]
	LDR X10, [SP, #-632]
	STR X12, [SP, #-636]
	LDR X14, [SP, #-12]
	STR X14, [SP, #-640]
	LDR X12, [SP, #-12]
	STR X15, [SP, #-316]
	STR X19, [SP, #-12]
	LDR X20, [SP, #-12]
	STR X20, [SP, #-136]
	LDR X21, [SP, #-632]
	STR X21, [SP, #-616]
	CMP X20, X21
CSET X15, LT
	STR X22, [SP, #-204]
	STR X23, [SP, #-204]
	ZEXT X22, X23
	STR X24, [SP, #-620]
	STR X25, [SP, #-12]
	TRUNC X24, X25
	STR X26, [SP, #-12]
	CBZ X26, %label.tmp_label.31
	CBNZ X26, %label.tmp_label.32
%label.tmp_label.31:
	STR X27, [SP, #-644]
	LDR X28, [SP, #-648]
	STR X28, [SP, #-12]
	LDR X27, [SP, #-648]
	STR X12, [SP, #-636]
	LDR X9, [SP, #-12]
	STR X9, [SP, #-644]
	LDR X12, [SP, #-12]
	STR X10, [SP, #-628]
	LDR X11, [SP, #-12]
	STR X11, [SP, #-632]
	ADD X10, #2, X11
	STR X12, [SP, #-636]
	LDR X12, [SP, #-12]
	STR X12, [SP, #-636]
	LDR X12, [SP, #-12]
	STR X13, [SP, #-632]
	LDR X14, [SP, #-120000688]
	STR X14, [SP, #-12]
	LDR X15, [SP, #-120000692]
	STR X15, [SP, #-120000692]
	LDR X14, [SP, #-120000692]
	STR X19, [SP, #-120000696]
	STR X20, [SP, #-12]
	LDR X21, [SP, #-120000692]
	STR X21, [SP, #-632]
	STR X22, [SP, #-120000700]
	SDIV X20, X21, X22
MUL X20, X20, X22
SUB X19, X19, X20
	STR X12, [SP, #-12]
	LDR X23, [SP, #-12]
	STR X23, [SP, #-120000692]
	LDR X12, [SP, #-12]
	STR X24, [SP, #-120000700]
	LDR X25, [SP, #-12]
	STR X25, [SP, #-120000700]
	STR X26, [SP, #-120000700]
	MUL X24, X25, X26
	STR X27, [SP, #-120000704]
	LDR X27, [SP, #-648]
	STR X27, [SP, #-120000704]
	LDR X27, [SP, #-648]
	STR X28, [SP, #-648]
	LDR X9, [SP, #-648]
	STR X9, [SP, #-12]
	STR X10, [SP, #-120000708]
	ADD X28, X9, X10
	STR X11, [SP, #-12]
	STR X27, [SP, #-648]
	STR X11, [SP, #-120000704]
	STR X12, [SP, #-636]
	LDR X12, [SP, #-12]
	STR X12, [SP, #-636]
	LDR X12, [SP, #-12]
	STR X12, [SP, #-12]
	LDR X13, [SP, #-12]
	STR X13, [SP, #-120000688]
	LDR X12, [SP, #-12]
	STR X14, [SP, #-120000688]
	LDR X15, [SP, #-12]
	STR X15, [SP, #-120000692]
	ADD X14, X15, #1
	STR X19, [SP, #-120000712]
	STR X12, [SP, #-636]
	STR X19, [SP, #-636]
	B %label.tmp_label.30
%label.tmp_label.32:
	STR X27, [SP, #-120000704]
	LDR X20, [SP, #-648]
	STR X20, [SP, #-120000716]
	LDR X27, [SP, #-648]
	STR X21, [SP, #-120000692]
	STR X22, [SP, #-120000708]
	LDR X23, [SP, #-648]
	STR X23, [SP, #-12]
	CMP X23, XZR
CSET X21, LT
	STR X24, [SP, #-120000720]
	STR X25, [SP, #-12]
	ZEXT X24, X25
	STR X26, [SP, #-120000712]
	STR X27, [SP, #-120000704]
	TRUNC X26, X27
	STR X28, [SP, #-120000724]
	CBZ X28, %label.tmp_label.33
	CBNZ X28, %label.tmp_label.34
%label.tmp_label.33:
	STR X27, [SP, #-120000728]
	LDR X9, [SP, #-648]
	STR X9, [SP, #-648]
	LDR X27, [SP, #-648]
	STR X10, [SP, #-120000720]
	LDR X11, [SP, #-648]
	STR X11, [SP, #-120000724]
	SUB X10, XZR, X11
	STR X12, [SP, #-636]
	STR X27, [SP, #-120000704]
	STR X12, [SP, #-120000704]
%label.tmp_label.34:
	BL stoptime
	STR X27, [SP, #-120000704]
	LDR X13, [SP, #-648]
	STR X13, [SP, #-12]
	LDR X27, [SP, #-648]
	LDR X2, [SP, #-648]
	STR X2, [SP, #-476]
	MOV X2, X1
	BL putint
	BL putch
	MOV X0, XZR
;.endmodule
 epilogue
	ADD SP, SP, #120000736
	; Deallocate stack space
	LDP X29, X30, [SP], #16
	; Restore FP and LR

	RET
