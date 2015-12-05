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
    print "-------- Testing create, add, and draw functions. --------\n"
    
    EXAMPLE = only_alpha(EXEMPLE)

    # test of briandais tree
    print "Creating a new Briandais Tree"
    briandais = BriandaisTree();
    print "Adding all words of the example"
    for word in EXEMPLE.split():
        briandais.add_word(word)
    print "Drawing the briandais Tree (look at briandais.pdf)"
    briandais.draw("briandais.pdf")

    # test of regular Ternary tree
    print "Creating a new 'Trie Hybride'"
    tree = TernarySearchTree()
    print "Adding all words of the example"
    for word in EXAMPLE.split(' '):
        tree.add_word(word)
    print "Drawing the 'Trie hybride' (look at ternary_regular.pdf)"
    tree.draw("ternary_regular.pdf")

    # test of self-balancing Ternary tree
    print "Creating a new 'Trie Hybride', but this time it will be balance"
    tree = TernarySearchTree()
    print "Adding all words of the exemple (still keeping the balance)"
    for word in EXAMPLE.split(' '):
        tree = tree.add_word_eq(word)
    print "Drawing the tree. (look at ternary_eq.pdf)\n\n"
    tree.draw("ternary_eq.pdf")


def shakespeare_test():
    print "-------- Demarrage des tests avances --------\n"
    
    # creating the Shakespeare briandais tree
    print("*********** BRIANDAIS TREE ************")
    startt = time.time()
    briandais = BriandaisTree();
    for filename in glob.iglob('Shakespeare/*'):
        fh = open(filename, "r")
        for word in fh:
            briandais.add_word(only_alpha(word))
        fh.close()
    print("Oeuvre de Shakespeare ajoutee a l'arbre. ")
    print("\tDuree: " + str(time.time() - startt))
    
    startt = time.time()
    print("Comptage du nombre de mot : " + str(briandais.number_words()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage du nombre de NIL : " + str(ComptageNil(briandais)))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage de la hauteur : " + str(briandais.height()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage de la hauteur moyenne: " + str(briandais.average_height()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage de la hauteur moyenne better: " + str(briandais.av_leaf_height()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Suppression de tous les mots.")
    for word in briandais.all_words():
        briandais.suppress(word)
    print("\tDuree: " + str(time.time() - startt))

    # Drawing such a big tree takes some time, so if you really want to see it,
    # uncommment the next line.
    #briandais.draw("briandais_shake.pdf")

    print('')

    
    # creating the Shakespeare ternary tree
    print("*********** TRIE HYBRIDE ************")
    startt = time.time()
    tree = TernarySearchTree()
    for filename in glob.iglob('Shakespeare/*'):
        fh = open(filename, "r")
        for word in fh:
            tree.add_word(only_alpha(word))
        fh.close()
    print("Oeuvre de Shakespeare ajoutee a l'arbre. ")
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage du nombre de mot : " + str(tree.number_words()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage du nombre de NIL : " + str(Nil(tree)))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage de la hauteur : " + str(tree.height()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Comptage de la hauteur moyenne : " + str(tree.av_leaf_height()))
    print("\tDuree: " + str(time.time() - startt))

    startt = time.time()
    print("Suppression de tous les mots.")
    for word in tree.all_words():
        tree.suppress(word)
    print("\tDuree: " + str(time.time() - startt))

    # Drawing such a big tree takes some time, so if you really want to see it,
    # uncommment the next line.
    #tree.draw("ternary_shake.pdf")

short_test()
shakespeare_test()
