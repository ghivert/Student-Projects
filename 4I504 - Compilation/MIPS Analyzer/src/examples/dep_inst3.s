	.text
	.ent main
main:	
	lw $4, 0($6)
	lw  $2, 0($4)
	add $5, $14, $2
	ori $10, $6, 0
	sw $5, 0($10)
	lw $2, -12($10)
	addi $5, $2, 4
	bne $5, $2, $L5
	add $0, $0, $0

	lw $4, 0($6)
	lw $2, 0($7)
	add $5,	$4, $2
	sw $5, 0($6)
	addiu $12, $8, 2
	addiu $7, $12, 1
	bne $7, $0, $L5
	add $0, $0, $0
	
	sub $6, $0, $5
	sll $6, $3, 4
	addiu $5, $6, -2
	sw $15, 12($7)	
	sw $10, -4($6)
$L5:
	sub $8, $10, $15 	
	sll $10, $10, 4	
	sw $8, 8($7)	
	add $10, $8, $10	
	sw $10, 12($7)
	jr $31
	add $0, $0, $0

	.end main
	.set reorder

