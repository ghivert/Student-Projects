; Starfield demo for chip16
; By tykel
; Store 64 stars - 3 * 64 values in memory (x, y, z)
; See http://freespace.virgin.net/hugo.elias/graphics/x_stars.htm
; star_x: #1000
; star_y: #2000
; star_z: #3000
; star_dir: #4000 -- on bits [0] && [1]
;-------------------------------------------------------------------------------
:init
	ldi r6, 1
	ldi r7, 2
	ldi rf, 0						; zero register
	ldi r8, 160						; center of screen x
	ldi r9, 120						; center of screen y
	spr #0101						; stars are 2*1 (1*1 w/ mask)
	ldi r2, #FF					; loop on all stars
	:init_loop
		subi r2, 1
		jc program
		ldi re, #1000
		ldi r3, 0
		call store_val
		ldi re, #2000
		ldi r3, 0
		call store_val
		ldi re, #3000
		ldi r3, 1
		call store_val
		ldi re, #4000
		ldi r3, 2
		call store_val
		jmp init_loop
	:store_val
		jme r3, rf, c_r_0
		jme r3, r6, c_r_1
		call random_dir
		:store_val2
		mov r4, r2
		shl r4, 2
		add re, r4
		stm r3, re
		ret
	:random_xy
		rnd r3, #FFFE
		addi r3,1
		ret
	:random_z
		rnd r3, 2399
		addi r3, 601
		ret
	:random_dir
		rnd r3, 2
		addi r3,1
		ret
	:c_r_0
		call random_xy
		jmp store_val2
	:c_r_1
		call random_z
		jmp store_val2
;-------------------------------------------------------------------------------
:program
	vblnk
	cls
	ldi r2, #FF
	:program_loop
		subi r2, 1
		jc program
		ldi r3, #1000				; address manipulation...
		mov r4, r2	
		muli r4, 4	
		add r3, r4
		ldm ra, r3					; this is star_x(i)
		addi r3, #1000
		ldm rb, r3					; this is star_y(i)
		addi r3, #1000
		ldm rc, r3					; this is star_z(i)
		subi rc, 15					; star_z(i) -= 15
		stm rc, r3					; STORE IT!
		jz star_z_0
		:screen_pos
		addi r3, #1000
		ldm rd, r3
		mov r0, ra
		div r0, rc
		add r0, r8					; this is star_scr_x(i)
		ldi r3, 800
		sub r3, r0
		jc off_scr
		mov r1, rb
		div r1, rc
		;muli r1, 5
		add r1, r9					; this is star_scr_y(i)
		ldi r3, 600
		sub r3, r1
		jc off_scr
		and rd, r6, r3
		jz maybe_y_swap
		call x_swap
		:maybe_y_swap
		and rd, r7, r3
		jz continue
		call y_swap
		:continue
		call draw
		jmp program_loop
	:off_scr
		call random_xy
		ldi r4, #1000
		mov r5, r2
		muli r5, 4 
		add r4, r5
		stm r3, r4
		call random_xy
		addi r4, #1000
		stm r3, r4
		call random_z
		addi r4, #1000
		stm r3, r4
		call random_dir
		addi r4, #1000
		stm r3, r4
		jmp program_loop
	:star_z_0
		ldi rc, 1
		jmp screen_pos
	:x_swap
		mov r3, r8
		shl r3, 1
		sub r3, r0, r0
		ret
	:y_swap
		mov r3, r9
		shl r3, 1
		sub r3, r1, r1
		ret
;-------------------------------------------------------------------------------
:draw
	mov rd, rc
	divi rd, 334
	subi rd, 1
	jz draw_w
	subi rd, 1
	jz draw_lg
	subi rd, 1
	jz draw_g
	jmp draw_b
:draw_w
	drw r0, r1, star_w
	ret
:draw_lg
	drw r0, r1, star_lg
	ret
:draw_g
	drw r0, r1, star_g
	ret
:draw_b
	ret
;-------------------------------------------------------------------------------
:star_w
	db #E0
	db #00
:star_lg
	db #D0
	db #00
:star_g
	db #C0
	db #00