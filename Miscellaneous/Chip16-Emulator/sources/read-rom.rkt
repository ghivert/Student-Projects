#lang racket

;;;;; Provide :
;;;; read-entire-file : Take the path to the file, open it, read it, store it
;;;;                    to a vector, convert it to assembly and close it.

(provide read-entire-file)
(require "convert-binary.rkt")

;;; Read a 32 bits instruction.
;; read-chunk : input-port 'binary -> bytes (4 byte).
(define (read-chunk port)
  (read-bytes 4 port))

;;; Consume header of a .c16 file. Print to debug.
;; read-header : input-port 'binary -> void.
(define (read-header port)
  (let ((magic (read-bytes 4 port))
        (reserved (read-byte port))
        (spec (read-byte port))
        (size (read-bytes 4 port))
        (start (read-bytes 2 port))
        (checksum (read-bytes 4 port)))
    (begin
      (printf "Magic Word    : ~a.~n" (bytes->string/utf-8 magic))
      (printf "Reserved is   : ~a.~n" reserved)
      (printf "Specification : ~a.~n" spec)
      (printf "Size of ROM   : ~a.~n" (integer-bytes->integer size #t #f))
      (printf "Start address : ~a.~n" (integer-bytes->integer start #t #f))
      (printf "And checksum  : ~a.~n~n" (integer-bytes->integer checksum #t #f))
      )))

;;; Read a file placed in path by instruction (4 bytes), store it to a vector.
;; store-file : String -> Vector[Instruction].
(define (store-file path)
  (letrec ((header #t)
           (read-file (lambda (port)
                        (if header
                            (begin
                              (read-header port)
                              (set! header #f)
                              (read-file port))
                            (let ((x (read-chunk port)))
                              (if (eof-object? x) '()
                                  (cons x (read-file port)))))))
           (read (lambda () 
                   (call-with-input-file
                       (if (regexp-match #rx"^.*\\.c16$" path) path
                           (begin (set! header #f) path))
                     read-file
                     #:mode 'binary))))
    (list->vector (read))))

;;; Take a vector of binary of instructions and return vector of
;;; assembly instructions.
;; instructions->assembly : Vctor[Instruction] -> Vector[List[Assembly]]
(define (instructions->assembly binary-codes)
  (vector-map convert-binary binary-codes))

;;; Take the path to the file, open it, read it, store it to a vector, convert
;;; it to assembly and close it.
;; read-entire-file : String -> Vector[List[Assembly]]
(define (read-entire-file path)
  (instructions->assembly (store-file path)))
