; Attempt at playing the Song Of Storms (LoZ:OoT)
;
; Melody: http://wiki.answers.com/Q/Piano_notes_for_legend_of_Zelda_song_of_storms
; Note frequencies: http://www.phy.mtu.edu/~suits/notefreqs.html
;
; tykel, 2012

S_WAIT equ 12
M_WAIT equ 20
L_WAIT equ 30

start:		sng 0x64, 0x4246		; Pulse, ADSR and volume
loop:		ldi r0, notes
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, L_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait
			addi r0, 2
			snp r0, 0
			ldi r1, S_WAIT
			call wait

			ldi r1, 45
			call wait
			jmp loop
			
wait:
wait_loop:	cmpi r1, 0
			jz wait_end
			vblnk
			subi r1, 1
			jmp wait_loop
wait_end:	snd0
			ret

; Will be used when refchip16 works properly!
notes:		db 146,0, 174,0, 0x25,1, 146,0, 174,0, 0x25,1, 0x49,1, 0x5D,1,
			db 0x49,1, 0x5D,1, 0x49,1, 0x05,1, 220,0, 220,0, 146,0, 146,0,
			db 174,0, 220,0, 220,0, 146,0, 174,0, 196,0, 164,0