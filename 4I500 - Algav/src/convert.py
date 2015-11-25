import briandais as BRD
import ternary_trees as TST

def ternary_to_briandais(ternary=TST.TernarySearchTree()):
    tree = BRD.BriandaisTree()
    for word in ternary.all_words():
        tree.add_word(word)
    return tree

def briandais_to_ternary(briandais=BRD.BriandaisTree()):
    tree = TST.TernarySearchTree()
    for word in briandais.all_words():
        tree.add_word(word)
    return tree
