	.text
	.ent main
main:	
	lw $4, 0($6)
	ori $10, $6, 0
	sub $2, $8, $7
	add $5, $4, $2
	sw $5, 0($10)
	lw $2, -12($10)
	addi $5, $12, 4
	bne $5, $2, etiq
	add $0, $0, $0
etiq:
	sub $8, $10, $15 
	sll $10, $10, 4
	sw $8, 8($7)
	add $10, $8, $10
	sw $10, 12($7)
	.end main
	.set reorder
