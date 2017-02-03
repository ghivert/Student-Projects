#lang racket

;;;;; Provide :
;;;; convert-binary : Take an instruction in binary form, and return the
;;;;                  correct assembly instruction corresponding.

;;;;; An instruction pattern is #xXX XX XX XX.

(provide convert-binary)

;;; Take an instruction and extract the section HHLL. System little-endian.
;; Instruction : #xXX XX LL HH.
;; instruction->HHLL : bytes -> integer
(define (instruction->HHLL instruction)
  (if (< (bytes-length instruction) 4)
      0
      (integer-bytes->integer (subbytes instruction 2
                                        (bytes-length instruction)) #t #f)))

;;; Take an integer and return the corresponding register flag associated.
;; integer->register : integer -> register flag.
;; If not 0 <= number <= 15, return void.
(define (integer->register number)
  (case number
    [(#x0) 'R0]
    [(#x1) 'R1]
    [(#x2) 'R2]
    [(#x3) 'R3]
    [(#x4) 'R4]
    [(#x5) 'R5]
    [(#x6) 'R6]
    [(#x7) 'R7]
    [(#x8) 'R8]
    [(#x9) 'R9]
    [(#xA) 'RA]
    [(#xB) 'RB]
    [(#xC) 'RC]
    [(#xD) 'RD]
    [(#xE) 'RE]
    [(#xF) 'RF]))

;;; Convert an instruction (bytes) into assembly instruction.
;; convert-binary : bytes -> list[assembly]
(define (convert-binary instruction)
  (if (eof-object? instruction)
      0
      (case (bitwise-and (bytes-ref instruction 0) #xF0)
        [(#x00) (instructions-0x instruction)]
        [(#x10) (instructions-1x instruction)]
        [(#x20) (instructions-2x instruction)]
        [(#x30) (instructions-3x instruction)]
        [(#x40) (instructions-4x instruction)]
        [(#x50) (instructions-5x instruction)]
        [(#x60) (instructions-6x instruction)]
        [(#x70) (instructions-7x instruction)]
        [(#x80) (instructions-8x instruction)]
        [(#x90) (instructions-9x instruction)]
        [(#xA0) (instructions-Ax instruction)]
        [(#xB0) (instructions-Bx instruction)]
        [(#xC0) (instructions-Cx instruction)]
        [(#xD0) (instructions-Dx instruction)]
        [(#xE0) (instructions-Ex instruction)]
        [else (printf "WTF ?~n")])))

;;; Take an instruction type #x0W YX 0Z 00 or #x0W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-0x : bytes -> list[assembly]
(define (instructions-0x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x00) (list 'NOP)]
      [(#x01) (list 'CLS)]
      [(#x02) (list 'VBLNK)]
      [(#x03) (list 'BGC (bitwise-and (bytes-ref instruction 2) #x0F))]
      [(#x04) (list 'SPR HHLL)]
      [(#x05) (list 'DRW RX RY HHLL)]
      [(#x06) (list 'DRW RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))]
      [(#x07) (list 'RND RX HHLL)]
      [(#x08) (case (bitwise-and (bytes-ref instruction 3) #x0F)
                [(#x0) (list 'FLIP 0 0)]
                [(#x1) (list 'FLIP 0 1)]
                [(#x2) (list 'FLIP 1 0)]
                [(#x3) (list 'FLIP 1 1)])]
      [(#x09) (list 'SND0)]
      [(#x0A) (list 'SND1 HHLL)]
      [(#x0B) (list 'SND2 HHLL)]
      [(#x0C) (list 'SND3 HHLL)]
      [(#x0D) (list 'SNP RX HHLL)]
      [(#x0E) (list 'SNG (integer-bytes->integer (subbytes instruction 2) #t #f)
                    HHLL)])))

;;; Take an instruction type #x1W YX 0Z 00 or #x1W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-1x : bytes -> list[assembly]
(define (instructions-1x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x10) (list 'JMP HHLL)]
      [(#x11) (list 'JMC HHLL)]
      [(#x12) (list 'Jx HHLL)]
      [(#x13) (list 'JME RX RY HHLL)]
      [(#x14) (list 'CALL HHLL)]
      [(#x15) (list 'RET)]
      [(#x16) (list 'JMP RX)]
      [(#x17) (list 'Cx HHLL)]
      [(#x18) (list 'CALL RX)])))

;;; Take an instruction type #x2W YX 0Z 00 or #x2W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-2x : bytes -> list[assembly]
(define (instructions-2x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x20) (list 'LDI RX HHLL)]
      [(#x21) (list 'LDI 'SP HHLL)]
      [(#x22) (list 'LDM RX HHLL)]
      [(#x23) (list 'LDM RX RY)]
      [(#x24) (list 'MOV RX RY)])))

;;; Take an instruction type #x3W YX 0Z 00 or #x3W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-3x : bytes -> list[assembly]
(define (instructions-3x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x30) (list 'STM RX HHLL)]
      [(#x31) (list 'STM RX RY)])))

;;; Take an instruction type #x4W YX 0Z 00 or #x4W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-4x : bytes -> list[assembly]
(define (instructions-4x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x40) (list 'ADDI RX HHLL)]
      [(#x41) (list 'ADD RX RY)]
      [(#x42) (list 'ADD RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))])))

;;; Take an instruction type #x5W YX 0Z 00 or #x5W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-5x : bytes -> list[assembly]
(define (instructions-5x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x50) (list 'SUBI RX HHLL)]
      [(#x51) (list 'SUB RX RY)]
      [(#x52) (list 'SUB RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))]
      [(#x53) (list 'CMPI RX HHLL)]
      [(#x54) (list 'CMP RX RY)])))

;;; Take an instruction type #x6W YX 0Z 00 or #x6W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-6x : bytes -> list[assembly]
(define (instructions-6x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x60) (list 'ANDI RX HHLL)]
      [(#x61) (list 'AND RX RY)]
      [(#x62) (list 'AND RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))]
      [(#x63) (list 'TSTI RX HHLL)]
      [(#x64) (list 'TST RX RY)])))

;;; Take an instruction type #x7W YX 0Z 00 or #x7W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-7x : bytes -> list[assembly]
(define (instructions-7x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x70) (list 'ORI RX HHLL)]
      [(#x71) (list 'OR RX RY)]
      [(#x72) (list 'OR RX RY (integer->register
                               (bitwise-and (bytes-ref instruction 2) #x0F)))])))

;;; Take an instruction type #x8W YX 0Z 00 or #x8W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-8x : bytes -> list[assembly]
(define (instructions-8x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x80) (list 'XORI RX HHLL)]
      [(#x81) (list 'XOR RX RY)]
      [(#x82) (list 'XOR RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))])))

;;; Take an instruction type #x9W YX 0Z 00 or #x9W YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-9x : bytes -> list[assembly]
(define (instructions-9x instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#x90) (list 'MULI RX HHLL)]
      [(#x91) (list 'MUL RX RY)]
      [(#x92) (list 'MUL RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))])))

;;; Take an instruction type #xAW YX 0Z 00 or #xAW YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-Ax : bytes -> list[assembly]
(define (instructions-Ax instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#xA0) (list 'DIVI RX HHLL)]
      [(#xA1) (list 'DIV RX RY)]
      [(#xA2) (list 'DIV RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))]
      [(#xA3) (list 'MODI RX HHLL)]
      [(#xA4) (list 'MOD RX RY)]
      [(#xA5) (list 'MOD RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))]
      [(#xA6) (list 'REMI RX HHLL)]
      [(#xA7) (list 'REM RX RY)]
      [(#xA8) (list 'REM RX RY (integer->register
                                (bitwise-and (bytes-ref instruction 2) #x0F)))])))

;;; Take an instruction type #xBW YX 0Z 00 or #xBW YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-Bx : bytes -> list[assembly]
(define (instructions-Bx instruction)
  (let ((RX (integer->register (arithmetic-shift
                                   (bitwise-and (bytes-ref instruction 1) #xF0) -4)))
        (RY (integer->register (bitwise-and (bytes-ref instruction 1) #x0F)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#xB0) (list 'SHL RX (bitwise-and (bytes-ref instruction 3) #x0F))]
      [(#xB1) (list 'SHR RX (bitwise-and (bytes-ref instruction 3) #x0F))]
      [(#xB2) (list 'SAR RX (bitwise-and (bytes-ref instruction 3) #x0F))]
      [(#xB3) (list 'SHL RX RY)]
      [(#xB4) (list 'SHR RX RY)]
      [(#xB5) (list 'SAR RX RY)])))

;;; Take an instruction type #xCW YX 0Z 00 or #xCW YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-Cx : bytes -> list[assembly]
(define (instructions-Cx instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#xC0) (list 'PUSH RX)]
      [(#xC1) (list 'POP RX)]
      [(#xC2) (list 'PUSHALL)]
      [(#xC3) (list 'POPALL)]
      [(#xC4) (list 'PUSHF)]
      [(#xC5) (list 'POPF)])))

;;; Take an instruction type #xDW YX 0Z 00 or #xDW YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-Dx : bytes -> list[assembly]
(define (instructions-Dx instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#xD0) (list 'PAL HHLL)]
      [(#xD1) (list 'PAL RX)])))

;;; Take an instruction type #xEW YX 0Z 00 or #xEW YX LL HH,
;;; and turn it into assembly.
;; RX : Address of register X.
;; RY : Address of register Y.
;; HHLL : Constant HHLL.
;; instructions-Ex : bytes -> list[assembly]
(define (instructions-Ex instruction)
  (let ((RX (integer->register
             (bitwise-bit-field (bytes-ref instruction 1) 0 4)))
        (RY (integer->register (bitwise-bit-field (bytes-ref instruction 1) 4 8)))
        (HHLL (instruction->HHLL instruction)))
    (case (bitwise-and (bytes-ref instruction 0) #xFF)
      [(#xE0) (list 'NOTI RX HHLL)]
      [(#xE1) (list 'NOT RX)]
      [(#xE2) (list 'NOT RX RY)]
      [(#xE3) (list 'NEGI RX HHLL)]
      [(#xE4) (list 'NEG RX)]
      [(#xE5) (list 'NEG RX RY)])))
