#lang racket/base
(require rackunit "../sources/cpu.rkt")

;;; Every register have to return 0. There have to be 16 registers labelled from
;;; R0 to RF.
(test-case
    "Every register is accesible and give a value."
    (let ((registers '(R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 RA RB RC RD RE RF)))
      (for-each
       (lambda (register)
         (check-equal? 0 (register-get register)) "Bad values !")
       registers)))

;;; Every register have to be set to a new number, and they can provide the new
;;; value. A value too high must return an error.
(test-case
    "Can modify register and value is permanently saved."
    (let ((x 1)
          (registers '(R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 RA RB RC RD RE RF)))
      (for-each
       (lambda (register)
         (begin
           (register-set! register x)
           (set! x (+ 1 x))))
       registers)
      (set! x 1)
      (for-each
       (lambda (register)
         (begin
           (check-equal? x (register-get register) "Value not saved !")
           (set! x (+ 1 x))))
       registers))
  (check-exn exn:fail? (lambda () (register-set! 'R0 76666))))

;;; If a register is not included in [R0-RF], must return an error.
(test-case
    "Inexistant register must fail."
    (let ((registers '(RG R10 R11 RH RI RJ)))
      (for-each
       (lambda (register)
         (check-exn exn:fail? (lambda () (register-get register))))
       registers)))

;;; It's possible to access to a number in range [0-255] from 0 to 65535 in RAM.
(test-case
    "Can access to entire RAM."
    (letrec ((loop (lambda (x)
                     (if (< x 65536)
                         (begin
                           (check-equal? 0 (memory-ref x))
                           (loop (+ 1 x)))
                         (check-exn exn:fail? (lambda () ((memory-ref x))))))))
      (loop 0)))

;;; It's possible to set the RAM to the desired value and it's correctly stored.
(test-case
    "Can address the RAM."
    (letrec ((loop (lambda (x y)
                     (if (< x 65536)
                         (begin
                           (check-not-exn (lambda () (memory-set! x y)))
                           (loop (+ 1 x) (if (= y 255)
                                             1
                                             (+ 1 y))))
                         (check-exn exn:fail? (lambda () (memory-set! x y)))))))
      (loop 0 1)
      (check-exn exn:fail? (lambda () (memory-set! 0 300)))))

;;; It's possible to access each field of FLAGS.
(test-case
    "Can access each field of FLAGS."
    (let ((bits '(carry zero overflow negative)))
      (for-each
       (lambda (bit)
         (check-equal? 0 (flags-operation bit 'get)))
       bits)
      (for-each
       (lambda (bit)
         (begin
           (check-not-exn (lambda () (flags-operation bit 'set)))
           (check-equal? (case bit
                           [(carry) #x40]
                           [(zero) #x20]
                           [(overflow) #x02]
                           [(negative) #x01])
                         (flags-operation bit 'get) "Bad value.")
           (check-not-exn (lambda () (flags-operation bit 'unset)))
           (check-equal? #x00 (flags-operation bit 'get) "Not zero.")))
       bits)
      (for-each
       (lambda (bit)
         (check-exn exn:fail? (lambda () (flags-operation bit 'wtf))))
       bits)))
