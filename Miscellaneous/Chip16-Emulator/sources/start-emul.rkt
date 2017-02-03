#lang racket

(require "read-rom.rkt")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;; Start Emulator ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (execute-vm)
  (display (read-entire-file "C:\\Users\\Guillaume\\Workspace\\Chip16-Emulator\\roms\\Demos\\AdsrDemo.c16"))
  ; Executes instructions.
  (begin
    ; (display "Test.\n")
    ; Wait for cycle.
    (sleep 0.000001)
    ;(execute-vm)))
    ))

(execute-vm)
