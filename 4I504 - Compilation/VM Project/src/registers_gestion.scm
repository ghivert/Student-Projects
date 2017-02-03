;;;; Fonctions de manipulations de registres.

;;; Fonctions de création de registres.
;; register-bits : int -> List[bit]
;; Crée un registre de numberOfBits bits.
(define (register-bits n)
  (if (= n 0)
      '()
      (cons 0 (create-register (- n 1)))))

;; create-register : -> Register
;; Crée un registre de 32 bits.
(define (create-register)
  (cons '*register* (register-bits 32)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; create-registers : int -> List[Register]
;; Crée une liste de integer registres.
(define (create-registers numberOfRegisters)
  (if (= numberOfRegisters 0)
      '()
      (cons (create-register) (create-registers (- numberOfRegisters 1)))))

;; Crée une liste de 8 registres.
(define (register-list) (create-registers 8))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Accès aux registres.
;; find-register : List[Register] * int -> Register
;; Accède au registre registerNumber de la liste registersList.
(define (find-register registersList registerNumber)
  (if (= registerNumber 0)
      (car registersList)
      (find-register (cdr registersList) (- registerNumber 1))))

;; register-number : int * List[Register] -> Register
;; Accède au registre registerNumber de la liste registersList.
(define (register-number registerNumber registersList)
  (find-register registersList registerNumber))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Accède à la liste de bits du registre.
(define (access-register-body register)
  (cdr register))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Accès aux bits d'un registre.
;; access-register-bit : List[bit] * int -> bit
;; Accède au bitNumber bit du registre register.
(define (access-bit-aux register-body bitNumber)
  (if (= bitNumber 0)
      (car register-body)
      (access-bit-aux (cdr register-body) (- bitNumber 1))))

(define (access-register-bit register bitNumber)
  (access-bit-aux (access-register-body register) bitNumber))

;; access-register-seq : Register * int * int -> List[bit]
;; Renvoie la séquence comprise entre les indices start et end.
(define (acces-seq-aux register-body start end)
  (if (= start 0)
      (if (= end 0)
          (list (car register-body))
          (cons (car register-body) (acces-seq-aux (cdr register-body) 0 (- end 1))))
      (acces-seq-aux (cdr register-body) (- start 1) (- end 1))))

(define (acces-register-seq register start end)
  (acces-seq-aux (access-register-body register) start end))


;;; Tests sur les bits d'un registre.
;; present-seq-register? : Register * List[bit] * int -> bool
;; Teste si la séquence sequence est présente, commençant à
;; l'emplacement position dans le registre register.
(define (present-seq-aux? register-body sequence position)
  (if (= position 0)
      (if (pair? sequence)
          (and (= (car sequence) (car register-body))
               (present-seq-aux? (cdr register-body) (cdr sequence) position))
          #t)
      (present-seq-aux? (cdr register-body) sequence (- position 1))))

(define (present-seq-register? register sequence position)
  (if (< 32 (+ position (length sequence)))
      (error "present-seq-register?"
             "Incohérence entre la longueur et la position de la séquence."
             position)
      (present-seq-aux? (access-register-body register) sequence position)))


;;; Vérification et réinitialisation des registres.
;; register-nil? : Register -> bool
;; Retourne vrai si le registre register vaut intégralement 0.
(define (register-nil-aux? register-body)
  (if (pair? register-body)
      (and (= 0 (car register-body)) (register-nil-aux? (cdr register-body)))
      #t))

(define (register-nil? register)
  (register-nil-aux? (access-register-body register)))
 
;; set-register-to-nil! : Register -> *undefined*
;; Réinitialise le registre register intégralement à 0.
(define (set-register-nil! register)
  (set-cdr! register (register-bits 32)))


;; copy-register : Register * Register -> *undefined*
;; Copie le contenu d'un registre dans un autre.
;; Met le contenu de reg-init dans reg-modify.
(define (copy-register reg-init reg-modify)
  (set-cdr! reg-modify (copy-register-aux (access-register-body reg-init))))

(define (copy-register-aux register-body)
  (if (pair? register-body)
      (if (= (car register-body) 1)
          (cons 1 (copy-register-aux (cdr register-body)))
          (cons 0 (copy-register-aux (cdr register-body))))
      '()))

;;; Modification de bits.
;; set-i-eme! : Register * int * bit -> Register
;; Met le i-ème bit à la valeur boolean.
(define (set-i-eme! register i boolean)
  (if (> i 31)
      (error "set-i-eme!"
             "Vous essayez de changer un bit inexistant !"
             i)
      (set-cdr! register (set-i-eme-aux! (access-register-body register) i boolean))))

(define (set-i-eme-aux! register i boolean)
  (if (= i 0)
      (cons boolean (cdr register))
      (append (list (car register)) (set-i-eme-aux! (cdr register) (- i 1) boolean))))

;; set-seq-register! : Register * List[bit] * int -> Register
;; Met la séquence en i-ème position à la valeur sequence.
(define (set-seq-register! register sequence i)
  (set-cdr! register (set-seq-register-aux! (cdr register) sequence i)))


(define (set-seq-register-aux! register sequence i)
  (if (= i 0)
      (if (pair? sequence)
          (cons (car sequence) (set-seq-register-aux! (cdr register) (cdr sequence) 0))
          register)
      (cons (car register) (set-seq-register-aux! (cdr register) sequence (- i 1)))))
