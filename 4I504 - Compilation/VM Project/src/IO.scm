;;; fichier provisoir. Uniquement présent pour aller avec execute.scm

(load "register.scm")
(load "utils.scm")

;(define fichier (open-binary-input-file "../codex.umz"))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; read-instruction : register -> unit
; lit une instruction (32 bits) du fichier "fichier" et 
; la stock dans le registre passe en argument
; le register est mis a 0 si jamais la fin du fichier est atteinte
(define (read-instruction register fichier)
  (let ((c (read-byte fichier)))
    (if (eof-object? c)
        (set-to-nil! register)
        (set-cdr! register (append (integer-to-bin c 8)
                                   (integer-to-bin (read-byte fichier) 8)
                                   (integer-to-bin (read-byte fichier) 8)
                                   (integer-to-bin (read-byte fichier) 8))))))
 
