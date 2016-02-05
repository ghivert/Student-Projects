[
  SET x 22;
  WHILE (not (eq x 42))
  [
    IF (lt x 42)
      [ SET x (add x 1) ]
      [ SET x (sub x 1) ]
  ]
]
