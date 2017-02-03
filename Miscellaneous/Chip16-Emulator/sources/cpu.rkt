#lang racket

;;;;; Provide :
;;;; Program-Counter : Counter of Code.
;;;; Stack-Pointer :   Pointer of the Stack..
;;;; register-get :    Get the desired register.
;;;; register-set! :   Set the desired register.
;;;; start-stack :     Beginning of stack.
;;;; start-IO :        Beginning of I/O ports.
;;;; start-memory :    Beginning of memory.
;;;; memory-ref :      Access to the desired position in memory.

(provide PC SP
         register-get register-set!
         start-stack start-I/O start-memory memory-ref memory-set!
         flags-operation)

;;; Program Counter and Stack Pointer.
;; Cannot be higher than 65 535 (16 bits).
(define PC 0)
(define SP 0)

;;; Array of registers.
;; Cannot be higher than 65 535 (16 bits).
(define registers (make-vector 16 0))

;;; Take vector-ref or vector-set! and apply the function to the register.
;; registers-manipulation : Function * RegisterName [* Int] -> Int or Void
(define (registers-manipulation function reg [value 0])
  (if (equal? function vector-ref)
      (function registers (register->id reg))
      (function registers (register->id reg) value)))
;;; Return the desired register.
;; register-get : RegisterName -> Int
;; Must take a register named R0 to RF.
(define (register-get reg)
  (registers-manipulation vector-ref reg))
;;; Set the desired register to the desired value.
;; register-set! : RegisterName * Int -> Void
;; Must take a register named R0 to RF.
(define (register-set! reg value)
  (if (< value 65535)
      (registers-manipulation vector-set! reg value)
      (error "Value exceeds 16 bits." value)))

;;; Convert identifier of register into number.
;; register->id : RegisterName -> integer
;; Must take a register named R0 to RF.

(define (register->id reg)
  (case reg
    [(R0) 0]
    [(R1) 1]
    [(R2) 2]
    [(R3) 3]
    [(R4) 4]
    [(R5) 5]
    [(R6) 6]
    [(R7) 7]
    [(R8) 8]
    [(R9) 9]
    [(RA) 10]
    [(RB) 11]
    [(RC) 12]
    [(RD) 13]
    [(RE) 14]
    [(RF) 15]
    [else (error "Register inexistant." reg)]
    ))

;;; FLAGS.
;; Cannot be higher than 255 (8 bits).
(define FLAGS 0)

;;; Allow to get respectively carry, zero, overflow and negative flag.
;;; Allow to set flags as wanted.
;;; bit must be carry, zero, overflow or negative. operation must be get or set.
;; x-flags-get : integer -> integer
;; x-flags-set! : integer -> void
(define (flags-operation bit operation)
  (case bit
    [(carry)    (if (equal? operation 'get)
                    (c-flags-get)
                    (if (equal? operation 'set)
                        (c-flags-set!)
                        (if (equal? operation 'unset)
                            (c-flags-unset!)
                            (error "Operation unknown." operation))))]
    [(zero)     (if (equal? operation 'get)
                    (z-flags-get)
                    (if (equal? operation 'set)
                        (z-flags-set!)
                        (if (equal? operation 'unset)
                            (z-flags-unset!)
                            (error "Operation unknown." operation))))]
    [(overflow) (if (equal? operation 'get)
                    (o-flags-get)
                    (if (equal? operation 'set)
                        (o-flags-set!)
                        (if (equal? operation 'unset)
                            (o-flags-unset!)
                            (error "Operation unknown." operation))))]
    [(negative) (if (equal? operation 'get)
                    (n-flags-get)
                    (if (equal? operation 'set)
                        (n-flags-set!)
                        (if (equal? operation 'unset)
                            (n-flags-unset!)
                            (error "Operation unknown." operation))))]))

(define (c-flags-get [flags FLAGS])
  (bitwise-and #x40 flags))
(define (c-flags-set! [flags FLAGS])
  (set! FLAGS (bitwise-ior #x40 flags)))
(define (c-flags-unset! [flags FLAGS])
  (set! FLAGS (bitwise-and #xBF flags)))

(define (z-flags-get [flags FLAGS])
  (bitwise-and #x20 flags))
(define (z-flags-set! [flags FLAGS])
  (set! FLAGS (bitwise-ior #x20 flags)))
(define (z-flags-unset! [flags FLAGS])
  (set! FLAGS (bitwise-and #xDF flags)))

(define (o-flags-get [flags FLAGS])
  (bitwise-and #x02 flags))
(define (o-flags-set! [flags FLAGS])
  (set! FLAGS (bitwise-ior #x02 flags)))
(define (o-flags-unset! [flags FLAGS])
  (set! FLAGS (bitwise-and #xFD flags)))

(define (n-flags-get [flags FLAGS])
  (bitwise-and #x01 flags))
(define (n-flags-set! [flags FLAGS])
  (set! FLAGS (bitwise-ior #x01 flags)))
(define (n-flags-unset! [flags FLAGS])
  (set! FLAGS (bitwise-and #xFE flags)))

;;; Memory.
;; 64 KB (65 536 B) of RAM/ROM.
;; Each unit of RAM/ROM can't be higher than 255 ! (8 bit)
;; memory-ref allows to get information from RAM.
;; memory-set! allows to stock information into the RAM.
;; memory-ref : integer -> integer
;; memory-set! : integer * integer -> void
(define memory (make-vector 65536 0))
(define (memory-ref address)
  (if (< address (vector-length memory))
      (vector-ref memory address)
      (error "Address out of range." address)))

(define (memory-set! address value)
  (if (> value 255)
      (error "A value can't be higher than 255 in RAM." value)
      (vector-set! memory address value)))

;;; Access to beginning of stack, of memory and to I/O ports.
;; start-x : void -> integer
(define (start-stack)
  (memory-ref #xFDF0))
(define (start-I/O)
  (memory-ref #xFFF0))
(define (start-memory)
  (memory-ref #x0000))
