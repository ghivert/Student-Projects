"""Module de gestion des arbres de la briandais. BriandaisTree est la classe
associee, et des fonctions de gestion existe afin de manipuler l'arbre de maniere
non POO."""

import string
import os

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

class BriandaisTree(object):
    """Represent a Briandais Tree, a tree to stock an entire dictionnary."""
    def __init__(self, word=None, brother=None):
        self.key = None
        self.child = None
        self.brother = brother
        self.final = False

        if word is not None:
            self.add_word(word)

    def add_word(self, word):
        """Add a word to the tree."""
        word = word.lower()
        if len(word) == 0: # Empty word.
            return None

        if self.key is None: # On the root uninitialized.
            self.key = word[0] # Empty tree, so add root.
            if len(word) == 1: # Word is over.
                self.final = True
            else: # Recursively add.
                self.child = BriandaisTree(word[1:])
        elif word[0] == self.key: # Tree already full.
            if len(word) == 1: # Word is over.
                self.final = True
            else: # Recursively add. New tree if child empty.
                if self.child is None:
                    self.child = BriandaisTree(word[1:])
                else:
                    self.child.add_word(word[1:])

        # Insert at the right place.
        else:
            if self.brother is None: # No brother, add it.
                self.brother = BriandaisTree(word)
            elif self.brother.key > word[0]: # Next brother follow the word.
                thing = self.brother
                self.brother = BriandaisTree(word, thing)
            else: # Continue.
                self.brother.add_word(word)

    def is_empty(self):
        """Test if the tree is empty."""
        if self.key is None and self.child is None and self.brother is None:
            return True

    def contains(self, word):
        """Test if tree contains the word."""
        word = word.lower()
        if len(word) == 0: # Empty IS in the tree. But it could not be. What do you prefer ?
            return True
        if self.key is None: # On an uninitialized tree.
            return False

        if self.key == word[0]: # On the correct branch.
            if len(word) == 1: # Word is over.
                if self.final is True: # Word exists.
                    return True
                else: # Word doesn't exists.
                    return False
            if self.child is not None: # Word not over, continue to search.
                return self.child.contains(word[1:])
            return False # No child. Too bad.
        elif self.brother is not None: # Continue to search on branch.
            return self.brother.contains(word)
        else:
            return False

    def number_words(self):
        """Return the number of words."""
        number = 0
        if self.final is True: # On a word. Hell yeah.
            number += 1
        if self.key is None:
            return number
        # Search if tree has child and brother.
        if self.child is not None:
            number += self.child.number_words()
        if self.brother is not None:
            number += self.brother.number_words()
        return number

    def all_words(self):
        """Return all the words of the tree."""
        words = []
        def get_all(tree, buffer=''):
            """Get all words of the tree."""
            if tree.key is None:
                return None

            if tree.final is True:
                words.append(buffer + tree.key)
            if tree.child is not None:
                get_all(tree.child, buffer + tree.key)
            if tree.brother is not None:
                get_all(tree.brother, buffer)
        get_all(self)
        return words

    def height(self, number=0):
        """Return the height of the tree."""
        if self.key is None:
            return 0

        # On the node, height is 1. Search for chid's height, and compare
        # to brother height. If brother higher than me, return brother's height.
        result = 1
        if self.child is not None:
            result += self.child.height()

        if self.brother is not None:
            temp = self.brother.height(result)
            if temp > result:
                return temp
        return result

    def average_height(self, number=0):
        """Return the average height of the tree."""
        if self.key is None:
            return 0.0

        average = 1.0
        if self.child is not None:
            average += self.child.height()

        if self.brother is not None:
            temp = self.brother.height(average)
            average = round((average + temp) / 2, 2)
        return average

    def prefix(self, word):
        """Get all words which start by the word."""
        word = word.lower()
        words = []
        if self.key is None:
            return []

        def get_all(tree, word, buffer=''):
            """Get all words which start by the word."""
            if len(word) == 0: # All words remaining are prefixed by word.
                if tree.final is True:
                    words.append(buffer + tree.key)
                if tree.child is not None:
                    get_all(tree.child, word, buffer + tree.key)
                if tree.brother is not None:
                    get_all(tree.brother, word, buffer)
            elif tree.key == word[0]: # Prefix isn't over. Explore.
                buffer += tree.key
                if tree.final is True and len(word) == 1:
                    words.append(buffer) # Prefix is a word by itself.
                if tree.child is not None:
                    get_all(tree.child, word[1:], buffer)
            else: # Explore on brother.
                if tree.brother is not None:
                    get_all(tree.brother, word, buffer)
        get_all(self, word)
        return words

    def suppress(self, word):
        """Delete a word from the tree."""
        word = word.lower()
        if len(word) == 0: # Impossible, so return False.
            return None

        if self.key == word[0]: # Correct node.
            if len(word) == 1: # On a leaf.
                if self.child is None: # Empty tree.
                    if self.final is True: # If tree is a final word.
                        self.final = False
                        if self.brother is not None: # Return brother to suppress itself.
                            return self.brother
                        else: # Brother is None, return True to suppress itself.
                            return True
                    return None
                else:
                    self.final = False # Suppress but keep structure.
                    return None
            else: # Anywhere in the tree.
                if self.child is not None:
                    suppr = self.child.suppress(word[1:])
                    if suppr is not None:
                        self.child = None
                        if self.final is False:
                            if self.brother is not None:# Return brother to suppress itself.
                                return self.brother
                            else: # Brother is None, return True to suppress itself.
                                return True
                    return None
        else: # Incorrect node, explore brothers.
            if self.brother is not None:
                suppr = self.brother.suppress(word)
                if suppr is not None:
                    self.brother = suppr
                    if self.final is False and self.child is None:
                        return self.brother # Suppress itself.

    def merge(self, tree):
        """Add all words from the tree into itself."""
        # The easy way...
        words = tree.all_words()
        for word in words:
            self.add_word(word)

    def __str__(self, buffer=''):
        """Add a string representation."""
        string = ''
        string += buffer + "Cle : " + self.key + '\n'
        if self.child is not None:
            string += self.child.__str__(buffer + ' ')
        if self.brother is not None:
            string += self.brother.__str__(buffer)
        return string
    def __repr__(self):
        return self.__str__()

    def print_br(self, filename):
        def to_dot(self, filename):
            nodes = ["0 [label=\"root\" color=\"black\"]"]
            edges = []
            id_gen = [1]
            
            def aux (tree, father) :
                if tree.key is None:
                    return None
                    
                id = id_gen[0]
                id_gen[0] += 1
                    
                edges.append(str(father) + " -> " + str(id))
                    
                color = "red" if tree.final else "blue"
                nodes.append(str(id) + " [label=\"" + tree.key + "\" color=\"" + color + "\"]")
                        
                if tree.brother is not None:
                    aux(tree.brother, father)
                            
                if tree.child is not None:
                    aux(tree.child, id)
                                
            aux(self, 0)
                
            fh = open(filename, 'w')
            fh.write("digraph {\n");
            fh.write("\n".join(nodes))
            fh.write("\n".join(edges))
            fh.write("\n}\n")
            fh.close
        
        to_dot(self, "tmp.dot")
        os.system("dot -Tps tmp.dot -o " + filename)
        

def merge(first, second):
    """Merge two trees into one."""
    # The complex way...

    if first is None:
        return second
    if second is None:
        return first

    tree = BriandaisTree()

    if first.key == second.key:
        tree.key = first.key
        tree.child = merge(first.child, second.child)
        tree.brother = merge(first.brother, second.brother)
        if first.final is True or second.final is True:
            tree.final = True
    elif first.key > second.key:
        tree.key = second.key
        tree.child = second.child
        tree.brother = merge(first, second.brother)
        if second.final is True:
            tree.final = True
    else:
        tree.key = first.key
        tree.child = first.child
        tree.brother = merge(first.brother, second)
        if first.final is True:
            tree.final = True
    return tree

# Functions to comply the specifications...
def BriandaisTreeVide():
    """Retourne un arbre de la briandais vide."""
    return BriandaisTree()
def NouveauBriandaisTree(word):
    """Retourne un arbre de la briandais initialise avec le mot word."""
    return BriandaisTree(word)
def Recherche(tree, word):
    """Recherche le mot word dans l'arbre tree et indique s'il est dans l'arbre."""
    return tree.contains(word)
def ComptageMot(tree):
    """Retourne le nombre de mots de l'arbre tree."""
    return tree.number_words()
def ComptageNil(tree):
    """Compte le nombre de pointeurs nuls de l'arbre tree."""
    if tree.is_empty:
        return 2
    else:
        number = 0
        if tree.child is None:
            number += 1
        else:
            number += ComptageNil(tree.child)
        if tree.brother is None:
            number += 1
        else:
            number += ComptageNil(tree.brother)
        return number
def Hauteur(tree):
    """Retourne la hauteur de l'arbre tree."""
    return tree.height()
def ProfondeurMoyenne(tree):
    """Retourne la hauteur moyenne de l'arbre tree."""
    return tree.average_height()
def Prefixe(tree, word):
    """Retourne tous les mots de l'arbre tree commencant par le prefixe word."""
    return tree.prefix(word)
def Suppression(tree, word):
    """Supprime le mot word de l'arbre tree s'il existe."""
    tree.suppress(word)
    return tree
def Fusion(arbre1, arbre2):
    "Fusionne les deux arbres arbre1 et arbre2 et retourne un nouvel arbre."
    return merge(arbre1, arbre2)

