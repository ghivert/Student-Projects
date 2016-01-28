require_relative "reading"

module OPCODES
  CMV = 0
  AIND = 1
  AAMD = 2
  ADD = 3
  MUL = 4
  DIV = 5
  NAND = 6
  HALT = 7
  ALLOC = 8
  ABANDON = 9
  OUT = 10
  IN = 11
  LPROG = 12
  ORTH = 13
end

class UniversalMachine
  attr_accessor :val, :a, :b, :c, :registers, :pc, :opc
  attr_accessor :memory

  def get_opc(num)
    return (num >> 28) & 0b1111
  end

  def next_instr
    @val = @memory[0][@pc]
    @a = (@val >> 6) & 0b111
    @b = (@val >> 3) & 0b111
    @c = (@val >> 0) & 0b111
    @opc = get_opc(@memory[0][@pc])
    @pc = @pc + 1
  end

  def exec_vm
    @registers = [0, 0, 0, 0, 0, 0, 0, 0]
    @memory = []
    @memory << (read_prog ARGV[0])

    @pc = 0
    @val = 0
    @a = 0
    @b = 0
    @c = 0
    @opc = -1

    #File.open("vm.log", "w") do |stream|
      loop do
        stream.print "PC = " + @pc.to_s + " "
        next_instr
        case @opc
        when OPCODES::CMV
          #stream.puts "CMV     -- reg(c) = " + @registers[@c].to_s + " reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s
          if @registers[@c] != 0
            @registers[@a] = @registers[@b]
          end
        when OPCODES::AIND
          #stream.puts "AIND    -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @registers[@a] = @memory[@registers[@b]][@registers[@c]]
        when OPCODES::AAMD
          #stream.puts "AAMD    -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @memory[@registers[@a]][@registers[@b]] = @registers[@c]
        when OPCODES::ADD
          #stream.puts "ADD     -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @registers[@a] = (@registers[@b] + @registers[@c]) % 4294967296
        when OPCODES::MUL
          #stream.puts "MUL     -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @registers[@a] = (@registers[@b] * @registers[@c]) % 4294967296
        when OPCODES::DIV
          #stream.puts "DIV     -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          if @registers[@c] != 0
            @registers[@a] = @registers[@b] / @registers[@c]
          end
        when OPCODES::NAND
          #stream.puts "NAND    -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @registers[@a] = ~(@registers[@b] & @registers[@c])
          @registers[@a] += 2**32 if @registers[@a] < 0
        when OPCODES::HALT
          #stream.puts "HALT    -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          return
        when OPCODES::ALLOC
          #stream.puts "ALLOC   -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          temp = -1
          for i in 0...@memory.size
            if @memory[i] == nil
              temp = i
              break
            end
          end

          if temp == -1
            @memory << Array.new(@registers[@c], 0)
            @registers[@b] = @memory.size - 1
          else
            @memory[temp] = Array.new(@registers[@c], 0)
            @registers[@b] = temp
          end
        when OPCODES::ABANDON
          #stream.puts "ABANDON -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          @memory[@registers[@c]] = nil
        when OPCODES::OUT
          #stream.puts "OUT     -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          if @registers[@c] > 255
            puts "Error out..."
            return
          end
          print @registers[@c].chr
        when OPCODES::IN
          #stream.puts "IN      -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          input = getc
          if getc = nil
            @registers[@c] = 0xFFFFFFFF
          else
            @registers[@c] = input.ord
          end
        when OPCODES::LPROG
          #stream.puts "LPROG   -- reg(a) = " + @registers[@a].to_s + " reg(b) = " + @registers[@b].to_s + " reg(c) = " + @registers[@c].to_s
          if @registers[@b] != 0
            temp = @memory[@registers[@b]].dup
            @memory[0] = temp
          end
          @pc = @registers[@c]
        when OPCODES::ORTH
          #stream.puts "ORTH    -- " + "Value : " + (@val & 0x1FFFFFF).to_s(16) + " in reg(" + ((@val >> 25) & 0b111).to_s(16) + ")."
          @registers[(@val >> 25) & 0b111] = @val & 0x1FFFFFF
          @registers[(@val >> 25) & 0b111] += 2**32 if @registers[(@val >> 25) & 0b111] < 0
        end
      end
    #end
  end
end

vm = UniversalMachine.new
vm.exec_vm
