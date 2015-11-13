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
        self.final = False

        if len(word) == 0:
            if self.key != None:
                self.final = True
        else:
            self.add_word(word.lower())

    def add_word(self, word):
        """Add a word to the tree."""
        word = word.lower()
        if len(word) == 0: # If the word is a prefix of an existing word.
            self.final = True
        else:
            for son in self.sons:
                if son.key == word[0]:
                    return son.add_word(word[1:])
            self.sons.append(BriandaisTree(word[1:], word[0]))

    def is_empty(self):
        """Test if the tree is empty."""
        if key == None and self.sons == []:
            return True
        else:
            return False

    def contains(self, word):
        """Test if tree contains the word."""
        word = word.lower()
        if len(word) == 0:
            return True
        for son in self.sons:
            if son.key == word[0]:
                return son.contains(word[1:])
        return False

    def number_words(self):
        """Return the number of words."""
        number = 0
        if self.sons == []:
            if self.final == True: # On a leaf.
                number += 1
        else:
            for son in self.sons:
                number += son.number_words()
            if self.final == True: # On a word.
                number += 1
        return number

    def all_words(self):
        """Return all the words of the tree."""
        list = []
        def get_all(tree, word = ''):
            tree.sons.sort(key = lambda x: x.key)
            if tree.sons == []: # On a leaf.
                if tree.final == True and tree.key != None: # Word is final.
                    list.append(word + str(tree.key))
            else: # Everywhere else in the tree.
                if tree.final == True and tree.key != None:
                    list.append(word + str(tree.key))
                for son in tree.sons:
                    if tree.key == None: # On the root.
                        get_all(son, word)
                    else: # Everywhere else in the tree.
                        get_all(son, word + str(tree.key))
        get_all(self)
        return list

    def height(self):
        """Return the height of the tree."""
        height = 0
        for son in self.sons:
            temp = son.height()
            if temp > height:
                height = temp
        if self.key != None:
            return height + 1
        return height

    def average_height(self):
        """Return the average height of the tree."""
        average = 0.0
        for son in self.sons:
            temp = son.average_height()
            if average == 0.0: # Initialization.
                average = temp
            else:
                average = round((average + temp) / 2, 2)
        return round(average + 1)

    def prefix(self, word):
        """Get all words which start by the word."""
        word = word.lower()
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

    def suppress(self, word):
        """Delete a word from the tree."""
        word = word.lower()
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

    def merge(self, tree):
        """Add all words from the tree into itself."""
        # The easy way...
        words = tree.all_words()
        for word in words:
            self.add_word(word)

    def spaces(self, nb):
        """Add a string representation."""
        string = " " * nb + str(self.key) + " " + str(self.final) + "\n"
        for i in self.sons:
            string += i.spaces(nb + 2)
        return string
    def __repr__(self):
        return self.spaces(0)

def merge(first, second):
    """Merge two trees into one."""
    # The complex way...

    if first.key != second.key: # Can't append, but in case...
        raise Exception("Not a normal situation...")

    tree = BriandaisTree('') # Instantiate new tree.
    tree.key = first.key # Keep the key.
    tree.final = True if first.final == True or second.final == True else False
    i = 0; j = 0
    # Sort the sons.
    first.sons.sort(key = lambda x: x.key)
    second.sons.sort(key = lambda x: x.key)

    # If one tree is empty, keep everything else.
    if len(first.sons) == 0:
        for son in second.sons:
            tree.sons.append(son)
        return tree
    if len(second.sons) == 0:
        for son in first.sons:
            tree.sons.append(son)
        return tree

    # Merge the trees.
    while i < len(first.sons) and j < len(second.sons):
        if first.sons[i].key < second.sons[j].key:
            tree.sons.append(first.sons[i])
            i += 1
        elif first.sons[i].key > second.sons[j].key:
            tree.sons.append(second.sons[j])
            j += 1
        else:
            tree.sons.append(merge(first.sons[i], second.sons[j]))
            i += 1; j += 1
    return tree

# Functions to comply the specifications...
def BriandaisTreeVide():
    return BriandaisTree('')
def NouveauBriandaisTree(word):
    return BriandaisTree(word)
def Recherche(tree, word):
    return tree.contains(word)
def ComptageMot(tree):
    return tree.number_words()
def ComptageNil(tree):
    if tree.is_empty:
        return 1
    else:
        number = 0
        for son in tree.sons:
            number += ComptageNil(son)
        return number
def Hauteur(tree):
    return tree.height()
def ProfondeurMoyenne(tree):
    return tree.average_height()
def Prefixe(tree, word):
    return tree.prefix(word)
def Suppression(tree, word):
    tree.suppress(word)
    return tree
def Fusion(arbre1, arbre2):
    return merge(arbre1, arbre2)
