	.text
	.ent main
main:
	add $4, $0, $0
	add $0, $0, $0
etiq:	
	lw $5, 0($4)                 # R5 <- MEM[R4 + 0]  
	lw $7, 4($4)                 # R7 <- MEM[R3 + 0]
	add $3, $5, $6             # $3 <- R5 + R6   
	add $8, $7, $3             # R8 <- R7 + R3   
	add $3, $2, $9             # R3 <- R2 * R9
	add $7, $3, $6             # R7 <- R3 +R8
	sw $7, 0($4)               # MEM[R4 + 0] <- R7  
	add $9, $8, $3	            # R9 <- R8 * R3
	sw $9, 0($11)		   # MEM[R11 + 0] <- R9
	addi $11, $11, 4
	addi $4, $4, 4             # R4 <- R4 + 1
        bne $4, $0, etiq          # saut si R4 différent de 0
	nop  
	jr $31
	add $0, $0, $0
	.end main
	.set reorder
