	.file	1 "test_asm.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.globl	tab
	.data
	.align	2
	.type	tab, @object
	.size	tab, 28
tab:
	.word	23, 3
	.word	45
	.word	-6
	.word	120
	.word	2
	.word	11
	.word	23
	.text
	.align	2
	.globl	max2
	.set	nomips16
	.ent	max2
max2:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	lw	$2,16($fp)
	lw	$3,20($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L2
	nop

	lw	$2,20($fp)
	sw	$2,0($fp)
	j	$L3
	nop

$L2:
	lw	$2,16($fp)
	sw	$2,0($fp)
$L3:
	lw	$2,0($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	max2
	.size	max2, .-max2
	.align	2
	.globl	max
	.set	nomips16
	.ent	max
max:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	sw	$6,24($fp)
	lw	$2,16($fp)
	lw	$3,20($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L6
	nop

	lw	$2,20($fp)
	lw	$3,24($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L7
	nop

	lw	$2,24($fp)
	sw	$2,0($fp)
	j	$L8
	nop

$L7:
	lw	$2,20($fp)
	sw	$2,0($fp)
	j	$L8
	nop

$L6:
	lw	$2,16($fp)
	lw	$3,24($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L9
	nop

	lw	$2,24($fp)
	sw	$2,0($fp)
	j	$L8
	nop

$L9:
	lw	$2,16($fp)
	sw	$2,0($fp)
$L8:
	lw	$2,0($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	max
	.size	max, .-max
	.align	2
	.globl	max_tab
	.set	nomips16
	.ent	max_tab
max_tab:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,0($fp)
	sw	$0,4($fp)
	j	$L12
	nop

$L14:
	lw	$2,4($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$3,0($2)
	lw	$2,0($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L13
	nop

	lw	$2,4($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	sw	$2,0($fp)
$L13:
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
$L12:
	lw	$2,4($fp)
	lw	$3,20($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L14
	nop

	lw	$2,0($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	max_tab
	.size	max_tab, .-max_tab
	.rdata
	.align	2
$LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	li	$4,3			# 0x3
	li	$5,16			# 0x10
	li	$6,8			# 0x8
	jal	max
	nop

	move	$3,$2
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	move	$5,$3
	jal	printf
	nop

	lui	$2,%hi(tab)
	addiu	$4,$2,%lo(tab)
	li	$5,7			# 0x7
	jal	max_tab
	nop

	move	$3,$2
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	move	$5,$3
	jal	printf
	nop

	move	$2,$0
	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 4.3.2"
