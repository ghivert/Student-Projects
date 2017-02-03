;;    C16PASCAL
;;    Tronix (c) 2011

MAIN:
      ldi   r0,0		; load const
      stm   r0,_Y		; store variable
      ldi   r0,63		; load const
      stm   r0,Lim_Y		; store variable WORD
L0:
      ldi   r0,0		; load const
      stm   r0,_X		; store variable
      ldi   r0,63		; load const
      stm   r0,Lim_X		; store variable WORD
L2:
      ldm   r0,_X		; load variable
      mov   r5,r0		; push to stack
      ldm   r0,_Y		; load variable
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      and   r0,r1
      mov   r5,r0		; push to stack
      ldi   r0,0		; load const
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      sub   r0,r1		; make substraction
      cmpi  r0,0		; logical true
      db    #c4,#00,#00,#00
      pop   r3
      shl   r3,13
      shr   r3,15
      ldi   r0,0
      sub   r0,r3
      or    r0,r0		; if NOT jump to
      jz    L4
      ldm   r0,_X		; load variable
      mov   r5,r0		; push to stack
      ldi   r0,2		; load const
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      mul   r0,r1
      mov   ra,r0
      ldm   r0,_Y		; load variable
      mov   r5,r0		; push to stack
      ldi   r0,2		; load const
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      mul   r0,r1
      mov   rb,r0
      ldi   r0,0		; load const
      ldi   rf,_PIXEL		; load pointer
      spr   513
      drw   ra,rb,rf
L4:
L5:
      ldm   r0,_X		; load variable
      mov   r5,r0		; push to stack
      ldm   r0,Lim_X		; load variable DWORD
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      sub   r0,r1		; logical less
      db    #c4,#00,#00,#00
      pop   r3
      shl   r3,14
      shr   r3,15
      ldi   r0,0
      sub   r0,r3
      or    r0,r0		; if NOT jump to
      jz    L3
      ldm   r0,_X		; increase var by 1
      addi  r0,1
      stm   r0,_X
      jmp   L2
L3:
      ldm   r0,_Y		; load variable
      mov   r5,r0		; push to stack
      ldm   r0,Lim_Y		; load variable DWORD
      mov   r1,r0		; save V0->V1, get V0 from stack
      mov   r0,r5
      sub   r0,r1		; logical less
      db    #c4,#00,#00,#00
      pop   r3
      shl   r3,14
      shr   r3,15
      ldi   r0,0
      sub   r0,r3
      or    r0,r0		; if NOT jump to
      jz    L1
      ldm   r0,_Y		; increase var by 1
      addi  r0,1
      stm   r0,_Y
      jmp   L0
L1:
_PEND:
      jmp  _PEND		; end program
; ***** Library Code ***** 
; ***** Library Ends *****
; Variable Area
_PIXEL:	DB	#AA,#AA
_Y:	DB	#00,#00
_X:	DB	#00,#00
Lim_Y:	DB	#00,#00
Lim_X:	DB	#00,#00
; String constants


_STACK:
      db      0
