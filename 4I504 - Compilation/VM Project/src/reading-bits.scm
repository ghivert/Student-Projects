(load "maths.scm")
(load "registers_gestion.scm")

;; reading-codex : -> binary-port
;; Ouverture du fichier Codex.
(define reading-codex (open-input-binary-file "../reference-implementation/codex.umz"))

;; read-4bytes : -> List[bit]
;; Lit 4 caractères du codex et les interprète pour les stocker dans un registre.
(define (read-4bytes)
   (let ((8bits (read-byte reading-codex)))
     (if (eof-object? 8bits)
         '()
         (let ((16bits (read-byte reading-codex))
               (24bits (read-byte reading-codex))
               (32bits (read-byte reading-codex)))
           (make-array (append
                        (int->8bits 8bits)
                        (int->8bits 16bits)
                        (int->8bits 24bits)
                        (int->8bits 32bits)))))))

(define (make-array register)
  (make-array-aux (access-register-body register) 32))

(define (make-array-aux register-body n)
  (

;; read-interpret : Register -> *undefined*
;; Lit les 32 prochains bits et les stocke dans un registre.
(define (read-interpret register)
  (set-cdr! register (read-4bytes)))

;; int->bin : int -> List[bit]
;; Transforme un octet en une liste de 32 bits.
(define (int->bin integer)
  (octet-interpretation integer 2147483648))

(define (int->8bits integer)
  (octet-interpretation integer 128))

(define (octet-interpretation integer mask)
   (if (< mask 1)
       '()
       (if (= (bit-and integer mask) mask)
	   (cons 1 (octet-interpretation integer (/ mask 2)))
	   (cons 0 (octet-interpretation integer (/ mask 2))))))

;; bin->int : List[bit] * int -> int
;; Convertis le binaire bin de 32 bits en un entier.
(define (bin->int binary)
  (bin->int-aux bin 2147483648))

(define (bin->int-aux bin mask)
  (if (< mask 1)
      0
      (if (= (car bin) 1)
          (+ mask (bin->int-aux (cdr bin) (/ mask 2)))
          (bin->int-aux (cdr bin) (/ mask 2)))))
