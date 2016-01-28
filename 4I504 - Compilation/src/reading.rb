def read_prog(file)

  input = IO.binread file

  i = 0
  input_byte = []

  while i < input.size
    input_byte << (input.getbyte(i) << 24 |   input.getbyte(i + 1) << 16 | input.getbyte(i + 2) << 8 | input.getbyte(i + 3))
    i = i + 4
  end

  return input_byte
end
