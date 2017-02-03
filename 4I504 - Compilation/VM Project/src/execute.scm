(load "utils.scm")
(load "registers_gestion.scm")
(load "universal-machine.scm")

; ArrayCode contient (contiendra) les instructions lues dans le fichier a executer.
(define ArrayCode (make-vector 50000 (create-register 32)))

; ArrayList contient la liste des tableau déjà déclarés.
(define ArrayList (cons '*ArrayList* '()))

; ArrayPointer contient la position du dernier tableau dans ArrayList.
(define ArrayPointer 1)

; Renvoie le registre general numero binary-num
(define (get-register binary-num)
  (if (integer? binary-num)
      (cond ((= binary-num 0) register0)
            ((= binary-num 1) register1)
            ((= binary-num 2) register2)
            ((= binary-num 3) register3)
            ((= binary-num 4) register4)
            ((= binary-num 5) register5)
            ((= binary-num 6) register6)
            ((= binary-num 7) register7)
            (else (error "numero incorrect")))
      (cond ((equal? binary-num '(0 0 0)) register0)
            ((equal? binary-num '(0 0 1)) register1)
            ((equal? binary-num '(0 1 0)) register2)
            ((equal? binary-num '(0 1 1)) register3)
            ((equal? binary-num '(1 0 0)) register4)
            ((equal? binary-num '(1 0 1)) register5)
            ((equal? binary-num '(1 1 0)) register6)
            ((equal? binary-num '(1 1 1)) register7)
            (else (error "erreur de num de registre")))))


; Renvoie le tableau numero num de la liste ArrayList
(define (get-array num)
  (if (integer? num)
      (get-array-aux num ArrayList)
      (get-array-aux (bin-to-integer num 31) (cdr ArrayList))))

(define (get-array-aux num liste-array)
  (if (= num 0)
      (car liste-array)
      (get-array-aux (- num 1) (cdr liste-array))))
          


;;; Conditional Move
(define (conditional-move-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 0 0 0)))

(define (conditional-move-execute instr)
  (let ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2))))
    (if (not (register-nil? c))
        (cpy-register b a))))



;;; Array Index
(define (array-index-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 0 0 1)))

(define (array-index-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
         (b (get-register (acces-seq instr 3 5)))
         (c (get-register (acces-seq instr 0 2)))
         (tab (get-array (bin-to-integer (cdr b) 31)))
         (value-array (vector-ref tab (bin-to-integer (cdr c) 31))))
    (cpy-register value-array a)))


;;; Array Amendment
(define (array-amend-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 0 1 0)))

(define (array-amend-execute instr)
  (let* ((a (get-array (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2))))
    (vector-set! a (bin-to-integer b 31) c)))
        

;;; Addition
(define (addition-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 0 1 1)))

(define (addition-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2)))
        (result (modulo (+ (bin-to-integer (cdr b) 31) (bin-to-integer (cdr c) 31)) (power 2 32))))
    (cpy-register (integer-to-bin result 31) a)))


;;; Multiplication
(define (multiplication-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 1 0 0)))

(define (multiplication-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2)))
        (result (modulo (* (bin-to-integer (cdr b) 31) (bin-to-integer (cdr c) 31)) (power 2 32))))
    (cpy-register (integer-to-bin result 31) a)))


;;; Division
(define (division-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 1 0 1)))

(define (division-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2))))
    (if (not (= 0 (bin-to-integer (cdr c) 31)))
        (let ((result (quotient (bin-to-integer (cdr b) 31) (bin-to-integer (cdr c) 31))))
          (cpy-register (integer-to-bin result 31) a)))))

;;; Not-And
(define (not-and-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 1 1 0)))


(define (not-and-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2))))
    (cpy-register (not-and-function (cdr b) (cdr c)) a)))

(define (not-and-function reg1 reg2)
  (if (pair? reg1)
      (if (or (= 0 (car reg1)) (= 0 (car reg2)))
          (cons 1 (not-and-function (cdr reg1) (cdr reg2)))
          (cons 0 (not-and-function (cdr reg1) (cdr reg2))))
      '()))


;;; Halt
(define (halt-instr? instr)
  (equal? (acces-seq instr 28 31) '(0 1 1 1)))

(define (halt-execute instr)
  (exit 1))


;;; Allocation
(define (allocation-instr? instr)
  (equal? (acces-seq instr 28 31) '(1 0 0 0)))

(define (allocation-execute instr)
  (let* ((a (get-register (acces-seq instr 6 8)))
        (b (get-register (acces-seq instr 3 5)))
        (c (get-register (acces-seq instr 0 2)))
        (tab (make-vector (bin-to-integer c 31) 0)))
    (add-array ArrayList tab)
    (set! ArrayPointer (+ ArrayPointer 1))
    (cpy-register (integer-to-bin ArrayPointer 31) b)))

(define (add-array array-list array)
  (if (pair? array-list)
      (if (pair? (cdr array-list))
          (add-array (cdr array-list) array)
          (set-cdr! array-list))
      (error "Array list empty")))




(define (execute instr)
  (cond ((conditional-move-instr? instr) (conditional-move-execute instr))
        ((array-index-instr? instr) (array-index-execute instr))
        ((array-amend-instr? instr) (array-amend-execute instr))
        ((addition-instr? instr) (addition-execute instr))
        ((multiplication-instr? instr) (multiplication-execute instr))
        ((division-instr? instr) (division-execute instr))
        ((not-and-instr? instr) (not-and-execute instr))
        ((halt-instr? instr) (halt-execute instr))
        ((allocation-instr? instr) (allocation-execute instr))))




(set-to-nil! register2)
(set-to-nil! register3)
(set-to-nil! register4)
(set-to-nil! register5)
'*************************************************
'CONDITIONAL-MOVE
(set-seq-register! register2 '(0 0 0 0) 28)
(set-seq-register! register2 '(0 1 1) 0)
(set-seq-register! register2 '(1 0 0) 3)
(set-seq-register! register2 '(1 0 1) 6)
(set-seq-register! register3 '(1 0 1 1 1 0 1 0 1) 6)
(set-seq-register! register4 '(1 0 1 0 1 1 0 1 0 1) 10)
(set-seq-register! register5 '(1 1 0 0 1 1 0 1 1 0 1 1 0 1 0 1) 14)
register2
register3
register4
register5
'AFTER
(conditional-move-instr? register2)
(execute register2)
register2
register3
register4
register5
'*************************************************
'*************************************************
(set-to-nil! register2)
(set-to-nil! register3)
(set-to-nil! register4)
(set-to-nil! register5)
'ARRAY-INDEX
(set-seq-register! register2 '(0 0 0 1) 28)
(set-seq-register! register2 '(0 1 1) 0)
(set-seq-register! register2 '(1 0 0) 3)
(set-seq-register! register2 '(1 0 1) 6)
(set-seq-register! register6 '(1 1 0 0 1 1 0 1 1 0 1 1 0 1 0 1) 14)
(set-seq-register! register3 '(0) 0)
(set-seq-register! register4 '(1) 0)
(set-seq-register! register5 '(1 0 1 0 1 1 0 1 0 1) 10)
(set-cdr! ArrayList (cons (make-vector 10 (create-register 32)) '()))
(vector-set! (cadr ArrayList) 0 (cdr register6))
ArrayList
register2
register3
register4
register5
(array-index-instr? register2)
(execute register2)
register2
register3
register4
register5
