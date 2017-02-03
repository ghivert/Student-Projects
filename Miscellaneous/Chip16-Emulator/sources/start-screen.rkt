#lang racket/base
(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-display (ffi-lib "../lib/libdisplay"))

(define _palette-pointer          (_cpointer 'palette))
(define _hidden_registers-pointer (_cpointer 'hidden_registers))
(define _display_window-pointer   (_cpointer 'display_window))
(define _SDL_Display-pointer      (_cpointer 'SDL_Display))
(define-cstruct _SDL_Rect ([x _uint] [y _uint] [w _uint] [h _uint]))

(define-display create_registers (_fun -> _hidden_registers-pointer))
(define-display create_screen    (_fun _uint -> _display_window-pointer))
(define-display registers_deallocation (_fun _hidden_registers-pointer -> _void))
(define-display screen_deallocation (_fun _display_window-pointer -> _void))

(define-display initialize_palette (_fun -> _palette-pointer))
(define-display palette_deallocation (_fun _palette-pointer -> _void))

(define-display create_rectangle (_fun _uint _uint _uint -> _SDL_Rect))

(define-display init_SDL (_fun -> _void))
(define-display create_SDL_Display (_fun _uint _uint -> _SDL_Display-pointer))
(define-display SDL_Display_deallocation (_fun _SDL_Display-pointer -> _void))

(define-display SDL_ForceRender (_fun _SDL_Display-pointer -> _void))
(define-display SDL_SetBrush (_fun _SDL_Display-pointer _palette-pointer _uint ->
                                  _void))
(define-display SDL_RenderRectangle (_fun _SDL_Display-pointer _SDL_Rect -> _void))
(define-display SDL_Exit (_fun _SDL_Display-pointer -> _void))

(init_SDL)
;;(define truc (create_screen 320))
(define thing (create_SDL_Display 640 320))
(sleep 10)
(SDL_Exit thing)
