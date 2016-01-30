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

    loop do
      next_instr
      case @opc
      when OPCODES::CMV
        @registers[@a] = @registers[@b] if @registers[@c] != 0
      when OPCODES::AIND
        @registers[@a] = @memory[@registers[@b]][@registers[@c]]
      when OPCODES::AAMD
        @memory[@registers[@a]][@registers[@b]] = @registers[@c]
      when OPCODES::ADD
        @registers[@a] = (@registers[@b] + @registers[@c]) % 4294967296
      when OPCODES::MUL
        @registers[@a] = (@registers[@b] * @registers[@c]) % 4294967296
      when OPCODES::DIV
        @registers[@a] = @registers[@b] / @registers[@c] if @registers[@c] != 0
      when OPCODES::NAND
        @registers[@a] = ~(@registers[@b] & @registers[@c])
        @registers[@a] += 2**32 if @registers[@a] < 0
      when OPCODES::HALT
        return
      when OPCODES::ALLOC
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
        @memory[@registers[@c]] = nil
      when OPCODES::OUT
        if @registers[@c] > 255
          puts "Error out..."
          return
        end
        print @registers[@c].chr
      when OPCODES::IN
        input = getc
        if getc == nil
          @registers[@c] = 0xFFFFFFFF
        else
          @registers[@c] = input.ord
        end
      when OPCODES::LPROG
        if @registers[@b] != 0
          temp = @memory[@registers[@b]].dup
          @memory[0] = temp
        end
        @pc = @registers[@c]
      when OPCODES::ORTH
        @registers[(@val >> 25) & 0b111] = @val & 0x1FFFFFF
        @registers[(@val >> 25) & 0b111] += 2**32 if @registers[(@val >> 25) & 0b111] < 0
      end
    end
  end
end

vm = UniversalMachine.new
vm.exec_vm
