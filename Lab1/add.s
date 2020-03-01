	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 1
	.file	"add.c"
	.def	 _add;
	.scl	2;
	.type	32;
	.endef
	.globl	_add                    # -- Begin function add
	.p2align	4, 0x90
_add:                                   # @add
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	8(%ebp), %edx
	addl	12(%ebp), %edx
	movl	%eax, -4(%ebp)          # 4-byte Spill
	movl	%edx, %eax
	addl	$4, %esp
	popl	%ebp
	retl
                                        # -- End function

	.addrsig
