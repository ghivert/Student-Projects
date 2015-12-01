from briandais import BriandaisTree
from ternary_trees import TernarySearchTree
from ternary_trees import ComptageNil as Nil
from briandais import ComptageNil
import string
import os
import glob
import time

EXEMPLE = "A quel genial professeur de dactylographie sommes-nous redevables de \
la superbe phrase ci-dessous, un modele du genre, que toute dactylo connait par \
coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?"

def only_alpha(text):
    """Convert unicode string to ascii string without punctuations."""
    rstring = ""
    for word in text:
        for letter in word:
            if (letter in string.ascii_lowercase) or \
            (letter in string.ascii_uppercase) or \
            (letter == ' ') or (letter == '-'):
                rstring += letter
    return rstring

def short_test():
    EXAMPLE = only_alpha(EXEMPLE)

    # test of briandais tree
    briandais = BriandaisTree();
    for word in EXEMPLE.split():
        briandais.add_word(word)
    briandais.draw("briandais.pdf")

    # test of regular Ternary tree
    tree = TernarySearchTree()
    for word in EXAMPLE.split(' '):
        tree.add_word(word)
    tree.draw("ternary_regular.pdf")

    # test of self-balancing Ternary tree
    tree = TernarySearchTree()
    for word in EXAMPLE.split(' '):
        tree = tree.add_word_eq(word)
    tree.draw("ternary_eq.pdf")


def shakespeare_test():
    # creating the Shakespeare briandais tree
    startt = time.time()
    briandais = BriandaisTree();
    for filename in glob.iglob('Shakespeare/*'):
        fh = open(filename, "r")
        for word in fh:
            briandais.add_word(only_alpha(word))
        fh.close()
    print("BRIANDAIS")
    print("On ajoute tout SH !")
    print(time.time() - startt)

    startt = time.time()
    print(briandais.number_words())
    print("On compte les mots !")
    print(time.time() - startt)

    startt = time.time()
    print(ComptageNil(briandais))
    print("On compte les nil !")
    print(time.time() - startt)

    startt = time.time()
    print(briandais.height())
    print("On compte la hauteur !")
    print(time.time() - startt)

    startt = time.time()
    print(briandais.average_height())
    print("On compte la hauteur moyenne !")
    print(time.time() - startt)

    startt = time.time()
    for word in briandais.all_words():
        briandais.suppress(word)
    print("On compte les suppressions !")
    print(time.time() - startt)

    # and printing it
    #briandais.draw("briandais_shake.pdf")

    print('')

    # creating the Shakespeare ternary tree
    startt = time.time()
    tree = TernarySearchTree()
    for filename in glob.iglob('Shakespeare/*'):
        fh = open(filename, "r")
        for word in fh:
            tree.add_word(only_alpha(word))
        fh.close()
    print("TST")
    print("On ajoute tout SH !")
    print(time.time() - startt)

    startt = time.time()
    print(tree.number_words())
    print("On compte les mots !")
    print(time.time() - startt)

    startt = time.time()
    print(Nil(tree))
    print("On compte les nil !")
    print(time.time() - startt)

    startt = time.time()
    print(tree.height())
    print("On compte la hauteur !")
    print(time.time() - startt)

    startt = time.time()
    print(tree.average_height())
    print("On compte la hauteur moyenne !")
    print(time.time() - startt)

    startt = time.time()
    for word in tree.all_words():
        tree.suppress(word)
    print("On compte les suppressions !")
    print(time.time() - startt)

    # and printing it
    #tree.draw("ternary_shake.pdf")

short_test()
shakespeare_test()
