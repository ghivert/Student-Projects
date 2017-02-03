; Bouncing ball game
; By tykel
;-INITIALISATION----------------------------------------------------------------
cls							; clear screen initially
spr #0201					; set sprite size to 2x2
bgc #01						; set bg colour to black
ldi ra, #20					; reg A is the x coordinate, initialise
ldi rb, #20					; reg B is the y coordinate, initialise
ldi r0, #01					; reg 0 is the hdir, initialise (0 = l, 1 = r)
ldi r1, #01					; reg 1 is the vdir, initialise (0 = u, 1 = d)
ldi r2, #00					; reg2 is a scratch reg, initialise
ldi r3, #00					; reg 3 is the min x, constant (0)
ldi r4, #13E				; reg 4 is the max x, constant (320-2)
ldi r5, #00					; reg 5 is the min y, constant (0)
ldi r6, #EE					; reg 6 is the max y, constant (240-2)
ldi rd, #01					; reg D is a 1 register
ldi re, #02					; reg E is the speed, initialise (2)
ldi rf, #00					; reg F is a 0 register
;-------------------------------------------------------------------------------
:move_h						; SUB - MOVE_H
sub r4, ra, r2				; check if ball is more right than max x
jz move_l
jc move_l
sub ra, r3, r2				; check if ball is more left than min x
jz move_r
jc move_r
jmp move_v					; if it's not boundary, skip
:move_l
mov ra, r4					; move ball x to max x
mov r0, rf					; move ball left now
jmp move_v
:move_r
mov ra, r3					; move ball x to min x
mov r0, rd					; move ball right now
;-------------------------------------------------------------------------------
:move_v						; SUB - MOVE_V
sub r6, rb, r2				; check if ball is more down than max y
jz move_u
jc move_u
sub rb, r5, r2				; check if ball is more up than min y
jz move_d
jc move_d
jmp move_update_h			; if it's not boundary, skip
:move_u
mov rb, r6					; move ball y to max y
mov r1, rf					; move ball upwards now
jmp move_update_h
:move_d
mov rb, r5					; move ball to min y
mov r1, rd					; move ball downwards now
;-------------------------------------------------------------------------------
:move_update_h				; SUB - MOVE_UPDATE_H
jme r0, rf, move_update_l	; if hdir is left...
jmp move_update_r			; otherwise it's right
:move_update_l
sub ra, re					; sub speed from x-coord
jmp move_update_v			; goto vertical pos update
:move_update_r
add ra, re					; add speed to x-coord
;-------------------------------------------------------------------------------
:move_update_v				; SUB - MOVE_UPDATE_V
jme r1, rf, move_update_u	; if vdir is up...
jmp move_update_d			; otherwise it's down
:move_update_u
sub rb, re					; sub speed from y-coord
jmp draw					; pos update over, draw!
:move_update_d
add rb, re					; add speed tp y-coord
;-------------------------------------------------------------------------------
:draw						; SUB - DRAW
cls							; clear screen
drw ra, rb, sprite			; draw the sprite
vblnk						; refresh
jmp move_h					; back to moving...
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
:sprite						; SPRITE - SPR (2x2)
db #FF
db #FF
db #FF
db #FF