let null = function l -> if l = [] then true else false;;

let rec g = function x -> x = [];;

let rec h = function x -> function y ->  x::y;;

let q = function x -> (hd x), (tl x);;

let v = function x -> [];;

let rec w = function l -> function x -> if l = [] then [] else x :: [];;


let rec map = function f -> function l -> 
    if null l then [] else (f (hd l))::(map f (tl l))
;;

let rec iter = function f -> function l -> 
    if null l then [] else  iter (f (tl l))
;;

let rec inter = function a -> function b -> 
    if a > b then [] else a::(inter (a+1) b)
;;

let mult  = function x -> function y -> x * y;; 

let i = inter 1 10;;

let l = map ( mult 5) i;;

let fd = map;;

let ig = map (mult 5);;

let bi = ig  l;;

let ik = map mult;;

let b = ik i;;

let rec umap = function l -> function x -> 
  if null l then [] else ((hd l) x)::(umap (tl l) x);;

umap b 10;;


