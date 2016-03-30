	.file	1 "test_asm3.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.text
	.align	2
	.globl	sum
	.set	nomips16
	.ent	sum
sum:
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
	sw	$7,28($fp)
	sw	$0,0($fp)
	j	$L2
	nop
	
$L3:
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$5,$2,$3
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$4,0($2)
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,20($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	addu	$2,$4,$2
	sw	$2,0($5)
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
	
$L2:
	lw	$2,0($fp)
	lw	$3,28($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L3
	nop

	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	sum

#-------------------------------------------
	.size	sum, .-sum
	.align	2
	.globl	max_min_tab
	.set	nomips16
	.ent	max_min_tab
max_min_tab:
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
	sw	$7,28($fp)
	sw	$0,0($fp)
	j	$L6
	nop

$L9:
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$4,0($2)
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,20($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	slt	$2,$4,$2
	beq	$2,$0,$L7
	nop

	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$4,$2,$3
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,20($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	sw	$2,0($4)
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,28($fp)
	addu	$4,$2,$3
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	sw	$2,0($4)
	j	$L8
	nop

$L7:
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$4,$2,$3
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,16($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	sw	$2,0($4)
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,28($fp)
	addu	$4,$2,$3
	lw	$2,0($fp)
	sll	$3,$2,2
	lw	$2,20($fp)
	addu	$2,$2,$3
	lw	$2,0($2)
	sw	$2,0($4)
$L8:
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
$L6:
	lw	$2,0($fp)
	lw	$3,32($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L9
	nop

	move	$2,$0
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	max_min_tab
	.size	max_min_tab, .-max_min_tab
	.align	2
	.globl	mat_mul
	.set	nomips16
	.ent	mat_mul
mat_mul:
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	sw	$6,32($fp)
	sw	$0,8($fp)
	j	$L12
	nop

$L15:
	sw	$0,4($fp)
	j	$L13
	nop

$L14:
	lw	$2,8($fp)
	sll	$3,$2,3
	sll	$2,$3,2
	addu	$3,$3,$2
	lw	$2,32($fp)
	addu	$3,$2,$3
	lw	$2,4($fp)
	sll	$2,$2,2
	addu	$2,$3,$2
	sw	$0,0($2)
	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L13:
	lw	$2,8($fp)
	slt	$2,$2,10
	bne	$2,$0,$L14
	nop

	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L12:
	lw	$2,8($fp)
	slt	$2,$2,10
	bne	$2,$0,$L15
	nop

	sw	$0,8($fp)
	j	$L16
	nop

$L21:
	sw	$0,4($fp)
	j	$L17
	nop

$L20:
	sw	$0,0($fp)
	j	$L18
	nop

$L19:
	lw	$2,8($fp)
	sll	$3,$2,3
	sll	$2,$3,2
	addu	$3,$3,$2
	lw	$2,32($fp)
	addu	$4,$2,$3
	lw	$5,4($fp)
	lw	$2,8($fp)
	sll	$3,$2,3
	sll	$2,$3,2
	addu	$3,$3,$2
	lw	$2,32($fp)
	addu	$3,$2,$3
	lw	$2,4($fp)
	sll	$2,$2,2
	addu	$2,$3,$2
	lw	$6,0($2)
	lw	$2,8($fp)
	sll	$3,$2,3
	sll	$2,$3,2
	addu	$3,$3,$2
	lw	$2,24($fp)
	addu	$3,$2,$3
	lw	$2,0($fp)
	sll	$2,$2,2
	addu	$2,$3,$2
	lw	$7,0($2)
	lw	$2,0($fp)
	sll	$3,$2,3
	sll	$2,$3,2
	addu	$3,$3,$2
	lw	$2,28($fp)
	addu	$3,$2,$3
	lw	$2,4($fp)
	sll	$2,$2,2
	addu	$2,$3,$2
	lw	$2,0($2)
	mul	$2,$7,$2
	addu	$3,$6,$2
	sll	$2,$5,2
	addu	$2,$4,$2
	sw	$3,0($2)
	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L18:
	lw	$2,8($fp)
	slt	$2,$2,10
	bne	$2,$0,$L19
	nop

	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L17:
	lw	$2,8($fp)
	slt	$2,$2,10
	bne	$2,$0,$L20
	nop

	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L16:
	lw	$2,8($fp)
	slt	$2,$2,10
	bne	$2,$0,$L21
	nop

	li	$2,1			# 0x1
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	mat_mul
	.size	mat_mul, .-mat_mul
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
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 24, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	lui	$2,%hi(A)
	addiu	$4,$2,%lo(A)
	lui	$2,%hi(B)
	addiu	$5,$2,%lo(B)
	lui	$2,%hi(C)
	addiu	$6,$2,%lo(C)
	li	$7,10			# 0xa
	jal	sum
	nop

	li	$2,10			# 0xa
	sw	$2,16($sp)
	lui	$2,%hi(A)
	addiu	$4,$2,%lo(A)
	lui	$2,%hi(B)
	addiu	$5,$2,%lo(B)
	lui	$2,%hi(C)
	addiu	$6,$2,%lo(C)
	lui	$2,%hi(D)
	addiu	$7,$2,%lo(D)
	jal	max_min_tab
	nop

	move	$3,$2
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	move	$5,$3
	jal	printf
	nop

	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

	.comm	C,40,4

	.comm	D,40,4
	.ident	"GCC: (GNU) 4.3.2"
