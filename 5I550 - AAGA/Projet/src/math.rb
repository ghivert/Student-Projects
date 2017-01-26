class Factorial
  @computed = []

  def self.fact(n)
    return 1 if n < 2
    (1..n).to_a.reduce(:*)
  end

  def self.calc(n)
    @computed[n] = fact(n) if @computed[n].nil?
    @computed[n]
  end
end

class G
  @computed = []

  def self.g(n)
    return 1.0 if (n - 1) <= 0
    (1..n - 1).to_a.reduce(1.0) { |prod, m| prod * (0.5 - m) } * (-2)**(n - 1)
  end

  def self.calc(n)
    @computed[n] = g(n) if @computed[n].nil?
    @computed[n]
  end
end

class Composition
  @computed = []

  def self.composition(n)
    result = []
    a = Array.new(n + 1, 0)
    k = 1
    a[0] = 0
    a[1] = n
    while k != 0
      x = a[k - 1] + 1
      y = a[k] - 1
      k = k - 1
      while 1 <= y do
        a[k] = x
        x = 1
        y -= x
        k += 1
      end
      a[k] = x + y
      result << a[0..k]
    end
    result
  end

    def self.calc(n, length = nil)
      @computed[n] = composition(n) if @computed[n].nil?
      @computed[n].select { |branch| length.nil? ? branch : branch.size == length }
    end
end

class Multinomial
  @computed = {}

  def self.multinomial(n, coeffs)
    Factorial.calc(n) / coeffs.reduce(1.0) { |prod, coeff| prod * Factorial.calc(coeff) }
  end

  def self.calc(n, coeffs)
    coeffs = coeffs.sort
    @computed[coeffs] = {} if @computed[coeffs].nil?
    @computed[coeffs][n] = multinomial(n, coeffs) if @computed[coeffs][n].nil?
    @computed[coeffs][n]
  end
end

class CompoProduct
  @computed = {}

  def self.compo_product(compo, n)
    compo.reduce(Multinomial.calc(n, compo)) { |total, i| total * G.calc(i) }
  end

  def self.calc(compo, n)
    compo = compo.sort
    @computed[compo] = {} if @computed[compo].nil?
    @computed[compo][n] = compo_product(compo, n) if @computed[compo][n].nil?
    @computed[compo][n]
  end
end

class InnerSum
  @computed = {}

  def self.inner_sum(size, length)
    Composition.calc(size, length).map { |x| CompoProduct.calc(x, size) }.reduce(:+)
  end

  def self.calc(size, length)
    @computed[size] = {} if @computed[size].nil?
    @computed[size][length] = inner_sum(size, length) if @computed[size][length].nil?
    @computed[size][length]
  end
end

class Calc
  def self.g(n)
    G.calc(n)
  end

  def self.composition(n, length = nil)
    Composition.calc(n, length)
  end

  def self.multinomial(n, coeffs)
    Multinomial.calc(n, coeffs)
  end

  def self.compo_product(compo, n)
    CompoProduct.calc(compo, n)
  end

  def self.inner_sum(size, length)
    InnerSum.calc(size, length)
  end
end
