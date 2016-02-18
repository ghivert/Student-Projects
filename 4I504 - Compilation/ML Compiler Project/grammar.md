# Grammar for mini ML language

```
e ::= ()
    | b
    | n
    | x
    | fun x -> e
    | e e
    | if e then e else e
    | match e with bs
    | Nil
    | Cons (e, e)
    | e + e
    | e * e
    | e - e
    | e <= e
    | e >= e
    | let x = e in e
    | let rec f = e in e
    
bs ::= Nil -> e
     | Cons (x, x) -> e
```
