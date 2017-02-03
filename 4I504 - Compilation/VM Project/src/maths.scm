;;; power : int*int -> int
;; Calcule x^n. Complexité optimisée.
(define (power x n)
  (if (= n 0)
      1
      (if (= n 1)
          x
          (if (= (modulo n 2) 0)
              (let ((reste (power x (/ n 2))))
                (* reste reste))
              (let ((remainder (power x (/ (- n 1) 2))))
                (* remainder remainder x))))))
