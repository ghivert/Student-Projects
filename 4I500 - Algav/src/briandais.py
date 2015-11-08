import string

exemple = "A quel genial professeur de dactylographie sommes-nous redevables de la superbe phrase ci-dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";

def only_alpha():
    rstring = ""
    for word in exemple:
        for letter in word:
            if (letter in string.ascii_lowercase) or (letter in string.ascii_uppercase) or (letter == ' ') or (letter == '-'):
                rstring += letter
    return rstring

example = only_alpha()

class BriandaisTree(object):
    """Represent a Briandais Tree, a tree to stock an entire dictionnary."""
    def __init__(self, word, key = None):
        self.key = key # Keep the key.
        self.sons = []

        if len(word) == 0: # Determine if the letter is final.
            self.final = True
        else:
            self.final = True
            self.add_word(word.lower())

    # Add a word to the tree.
    def add_word(self, word):
        if len(word) == 0: # If the word is a prefix of an existing word.
            self.final = True
        else:
            for son in self.sons:
                if son.key == word[0].lower():
                    return son.add_word(word[1:].lower())
            self.sons.append(BriandaisTree(word[1:].lower(), word[0].lower()))

    # Test if the tree is empty.
    def is_empty(self):
        if key == None and self.sons == []:
            return True
        else:
            return False

    # Test if tree contains the word.
    def contains(self, word):
        if len(word) == 0:
            return True
        for son in self.sons:
            if son.key == word[0].lower():
                return son.contains(word[1:].lower())
        return False

    # Return the number of words.
    def number_words(self, key = None):
        number = 0
        if self.sons == []:
            if self.final == True and self.key != None: # On a leaf.
                number += 1
        else:
            for son in self.sons:
                number += son.number_words(str(key) + str(self.key))
            if self.final == True and self.key != None: # On a word.
                number += 1
        return number

    # Return all the words of the tree.
    def all_words(self):
        list = []
        def get_all(tree, word = ''):
            tree.sons.sort(key = lambda x: x.key)
            if tree.sons == []:
                if tree.final == True and tree.key != None:
                    list.append(word + str(tree.key))
            else:
                if tree.final == True and tree.key != None:
                    list.append(word + str(tree.key))
                for son in tree.sons:
                    if tree.key != None:
                        get_all(son, word + str(tree.key))
                    else:
                        get_all(son, word)
        get_all(self)
        return list

    # Return the height of the tree.
    def height(self):
        height = 0
        for son in self.sons:
            temp = son.height()
            if temp > height:
                height = temp
        if self.key != None:
            return height + 1
        return height

    # Return the average height of the tree.
    def average_height(self):
        average = -1.0
        for son in self.sons:
            temp = son.average_height()
            if average < 0: # Initialization.
                average = temp
            else:
                average = round((average + temp) / 2, 2)
        return round(average + 1)

    # Get all words which start by the word.
    def prefix(self, word):
        answer = []
        def get_all(tree, word, pref = ''):
            if len(word) == 0:
                if tree.final == True: # On a word which is prefixed by word.
                    answer.append(pref + tree.key)
                for son in tree.sons: # Recursively search every other words.
                    get_all(son, word, pref + tree.key)
            elif tree.key == None: # On the root.
                for son in tree.sons: # Recursively search every words.
                    get_all(son, word, pref)
            else: # Everywhere else in the tree.
                if tree.key == word[0]:
                    if tree.final == True and len(word) == 1:
                        answer.append(pref + word) # Add the word cause it's final.
                    for son in tree.sons: # Recursively search every other words.
                        get_all(son, word[1:], pref + tree.key)
        get_all(self, word)
        return answer

    # Delete a word from the tree.
    def suppress(self, word):
        if self.key == None: # On the root.
            for son in self.sons:
                suppr = son.suppress(word)
                if suppr == True:
                    self.sons.remove(son) # Suppression to keep compacity.
        else: # Everywhere else.
            if len(word) == 0: # Son of the word to suppress.
                return False
            if self.key == word[0]: # In the prefix.
                for son in self.sons:
                    suppr = son.suppress(word[1:])
                    if suppr == True:
                        self.sons.remove(son) # Suppression to keep compacity.
                if self.sons == []:
                    return True # Can be removed.
                else: # Word have to be deleted, but other words depends on it.
                    self.final = False
                    return False

    # Add a string representation.
    def spaces(self, nb):
        string = " " * nb + str(self.key) + " " + str(self.final) + "\n"
        for i in self.sons:
            string += i.spaces(nb + 2)
        return string
    def __repr__(self):
        return self.spaces(0)

# Functions to comply the specifications...
def BriandaisTreeVide():
    return BriandaisTree('')
def NouveauBriandaisTree(word):
    return BriandaisTree(word)
def Recherche(tree, word):
    return tree.contains(word)
def ComptageMot(tree):
    return tree.number_words()
def ComptageNil():
    return 0
def Hauteur(tree):
    return tree.height()
def ProfondeurMoyenne(tree):
    return tree.average_height()
def Prefixe(tree, word):
    return tree.prefix(word)
def Suppression(tree, word):
    tree.suppress(word)
    return tree
