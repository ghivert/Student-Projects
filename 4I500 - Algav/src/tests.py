from briandais import BriandaisTree
from ternary_trees import TernarySearchTree
import string

EXEMPLE = "A quel genial professeur de dactylographie sommes-nous redevables de \
la superbe phrase ci-dessous, un modele du genre, que toute dactylo connait par \
coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?"

def only_alpha():
    """Convert unicode string to ascii string without punctuations."""
    rstring = ""
    for word in EXEMPLE:
        for letter in word:
            if (letter in string.ascii_lowercase) or \
            (letter in string.ascii_uppercase) or \
            (letter == ' ') or (letter == '-'):
                rstring += letter
    return rstring

EXAMPLE = only_alpha()



briandais = BriandaisTree();
for word in EXEMPLE.split():
    briandais.add_word(word)
    
briandais.draw("briandais.pdf")

tree = TernarySearchTree()
for word in EXAMPLE.split(' '):
    tree.add_word(word)
tree.draw("ternary_regular.pdf")

tree = TernarySearchTree()
for word in EXAMPLE.split(' '):
    tree = tree.add_word_eq(word)
tree.draw("ternary_eq.pdf")
