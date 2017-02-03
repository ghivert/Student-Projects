;;; Fichier provisoir. Uniquement pour aller avec execute.scm .


;;;;;;;;; Fonctions utiles pour la manipulation de registres ;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; create-register : int -> register
; cree un registre de taille n initialise a 0
(define (create-register n)
  (if (= n 0)
      '()
      (cons 0 (create-register (- n 1)))))

(define register0 (cons '*register0* (create-register 32)))
(define PC register0)
(define register1 (cons '*register1* (create-register 32)))
(define register2 (cons '*register2* (create-register 32)))
(define register3 (cons '*register3* (create-register 32)))
(define register4 (cons '*register4* (create-register 32)))
(define register5 (cons '*register5* (create-register 32)))
(define register6 (cons '*register6* (create-register 32)))
(define register7 (cons '*register7* (create-register 32)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; acces : register*int -> 0 + 1
; renvoie la valeur du bit en i-eme position de register
(define (acces register i)
  (acces-aux (reverse register) i))

(define (acces-aux register i)
  (if (= i 0)
      (car register)
      (acces-aux (cdr register) (- i 1))))

;;; acces-seq : register*int*int -> List[0+1]
; renvoie la sequence comprise entre les indices start et end dans register
; peut se faire en utilisant la fonction acces, mais moins efficasse.
(define (acces-seq register start end)
  (reverse (acces-seq-aux (reverse (cdr register)) start end)))

(define (acces-seq-aux register start end)
  (if (= start 0)
      (if (= end 0)
          (list (car register))
          (cons (car register) (acces-seq-aux (cdr register) 0 (- end 1))))
      (acces-seq-aux (cdr register) (- start 1) (- end 1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; present-seq? register*List[1+0]*int -> bool
; teste si la sequence seq est presente position (debut) dans register
(define (present-seq? register seq position)
  (if (< 32 (+ position (length seq)))
      (error "incoherence entre la longueur et la position de la sequence")
      (present-seq-aux? (reverse register) (reverse seq) position)))

(define (present-seq-aux? register seq position)
  (if (= position 0)
      (if (pair? seq)
          (and (= (car seq) (car register))
               (present-seq-aux? (cdr register) (cdr seq) 0))
          #t)
      (present-seq-aux? (cdr register) seq (- position 1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; register-nil? : register -> bool
; rend vraie uniquement si register vaut 0
(define (register-nil? register)
  (register-nil-aux? (cdr register)))

(define (register-nil-aux? register)
  (if (pair? register)
      (and (= 0 (car register)) (register-nil-aux? (cdr register)))
      #t))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; set-to-nil! : register -> unit
; initialise le registre passe en argument a 0
; utilie la fonction set-to-nil-aux
(define (set-to-nil! register)
  (set-cdr! register (set-to-nil-aux! (cdr register))))


;;; set-to-nil-aux! register-> register
; voir set-to-nil!
(define (set-to-nil-aux! register)
  (if (pair? register)
      (cons 0 (set-to-nil-aux! (cdr register)))
      '()))

;;; set-i-eme! register*int*(0+1) -> register
; met le i-eme bit a la valeur val
(define (set-i-eme! register i val)
  (if (> i 31)
      (error "set-i-eme! :
              vous essayez de changer un bit inexistant")      
      (set-cdr! register (reverse (set-i-eme-aux! (reverse (cdr register)) i val)))))

(define (set-i-eme-aux! register i val)
  (if (= i 0)
      (cons val (cdr register))
      (append (list (car register)) (set-i-eme-aux! (cdr register) (- i 1) val))))

;;; set-seq-register! register*List[0+1]*int -> register
(define (set-seq-register! register seq i)
  (set-cdr! register (reverse (set-seq-register-aux! (reverse (cdr register)) (reverse seq) i))))


(define (set-seq-register-aux! register seq i)
  (if (= i 0)
      (if (pair? seq)
          (cons (car seq) (set-seq-register-aux! (cdr register) (cdr seq) 0))
          register)
      (cons (car register) (set-seq-register-aux! (cdr register) seq (- i 1)))))


;;; cpy-register : register*register -> unit
; met le contenu de reg-init dans reg-a-modif
(define (cpy-register reg-init reg-a-modif)
  (if (number? (car reg-init))
      (set-cdr! reg-a-modif (cpy-register-aux reg-init))
      (set-cdr! reg-a-modif (cpy-register-aux (cdr reg-init)))))

(define (cpy-register-aux reg)
  (if (pair? reg)
      (if (= (car reg) 1)
          (cons 1 (cpy-register-aux (cdr reg)))
          (cons 0 (cpy-register-aux (cdr reg))))
      '()))
  


PC
(set-i-eme! PC 2 1)
PC
(set-to-nil! PC)
PC
(register-nil? PC)
(set-seq-register! PC '(1 1 1 1) 2)
PC
(register-nil? PC)
(present-seq? PC '(1 1 1 1) 2)
(present-seq? PC '(1 1 1 1) 1)
(acces-seq PC 1 6)
(acces PC 4)
(acces PC 8)
(set-i-eme! PC 20 1)
PC
(set-i-eme! PC 31 1)
PC
(acces-seq PC 28 31)
(cpy-register PC register2)
register2
(set-i-eme! PC 0 1)
PC
register2
(set-to-nil! register2)
register2





(set-to-nil! register0)
(set-to-nil! register1)
(set-to-nil! register2)
(set-to-nil! register3)
(set-to-nil! register4)
(set-to-nil! register5)
(set-to-nil! register6)
(set-to-nil! register7)

      