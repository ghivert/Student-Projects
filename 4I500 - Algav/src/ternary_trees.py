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

class TernarySearchTree(object):
    """Represent a dictionnary, which as a ternary Search tree."""
    def __init__(self, word = None):
        self.left = None
        self.equal = None
        self.right = None
        self.final = False
        self.key = None

        if word != None:
            self.add_word(word.lower())

    # Add a word to the tree.
    def add_word(self, word):
        word = word.lower()
        if len(word) == 0:
            return None

        if self.key == None: # If we are on the root uninitialized.
            self.key = word[0] # Initialize.
            if len(word) == 1:
                self.final = True
            else:
                self.equal = TernarySearchTree(word[1:])

        # Tree already full.
        elif word[0] == self.key:
            if len(word) == 1: # One letter word.
                self.final = True
            # Existent or non-existent son ? Yes => Add, No => Create.
            elif self.equal == None:
                self.equal = TernarySearchTree(word[1:])
            else:
                self.equal.add_word(word[1:])
        elif word[0] < self.key:
            # Existent or non-existent son ? Yes => Add, No => Create.
            if self.left == None:
                self.left = TernarySearchTree(word)
            else:
                self.left.add_word(word)
        else: # If first letter > key
            # Existent or non-existent son ? Yes => Add, No => Create.
            if self.right == None:
                self.right = TernarySearchTree(word)
            else:
                self.right.add_word(word)

    # Test if the tree is empty.
    def is_empty(self):
        if self.left == None and self.equal == None and self.right == None and self.key == None:
            return True
        return False

    # Test if tree contains the word.
    def contains(self, word):
        word = word.lower()
        # Word is empty or tree is empty.
        if len(word) == 0:
            return True
        if self.key == None:
            return False

        # Look for the words in other branches.
        if word[0] < self.key and self.left != None:
            return self.left.contains(word)
        elif word[0] > self.key and self.right != None:
            return self.right.contains(word)
        elif word[0] == self.key: # On the correct branch.
            if len(word) == 1:
                if self.final == True:
                    return True
                else:
                    return False
            if self.equal != None:  # Search for the rest of word.
                return self.equal.contains(word[1:])
        else:
            return False

    # Return the number of words. Just search for final tag.
    def number_words(self):
        number = 0
        if self.left != None:
            number += self.left.number_words()
        if self.equal != None:
            number += self.equal.number_words()
        if self.right != None:
            number += self.right.number_words()
        if self.final == True:
            number += 1
        return number

    # Return all the words in the tree.
    def all_words(self):
        words = []
        def get_all(tree, buffer = ''):
            if tree.key == None:
                return None
            if tree.left != None: # Left branch, lower than word[0].
                get_all(tree.left, buffer)

            if tree.final == True: # On node.
                words.append(buffer + tree.key)
            if tree.equal != None: # Equal branch, keep the buffer and the letter.
                get_all(tree.equal, buffer + tree.key)

            if tree.right != None: # Right branch, higher than word[0]
                get_all(tree.right, buffer)
        get_all(self)
        return words

    # Get the height of the tree.
    def height(self):
        if self.key == None:
            return 0
        number = 0
        if self.left != None:
            temp = self.left.height()
            if temp > number:
                number = temp
        if self.equal != None:
            temp = self.equal.height()
            if temp > number:
                number = temp
        if self.right != None:
            temp = self.right.height()
            if temp > number:
                number = temp
        return number + 1

    # Get the average height of the tree.
    def average_height(self):
        average = 0.0
        if self.left != None:
            average = self.left.average_height()
        if self.equal != None:
            temp = self.equal.average_height()
            if average == 0.0:
                average = temp
            else:
                average = round((average + temp) / 2, 2)
        if self.right != None:
            temp = self.right.average_height()
            if average == 0.0:
                average = temp
            else:
                average = round((average + temp) / 2, 2)
        return round(average + 1)

    # Get all words which prefix is word.
    def prefix(self, word):
        word = word.lower()

        # Factory to map a list[str] and add prefix.
        def create_map(pref):
            def add_pref(word):
                return pref + word
            return add_pref

        answer = []
        def get_all(tree, word, buffer = ''):
            word = word.lower()
            if tree == None:
                return []

            if len(word) == 1: # We're on the node of the end of prefix.
                buffer += tree.key
                if tree.final == True: # Prefix is a valid word.
                    print(buffer)
                    answer.append(buffer)
                if tree.equal != None: # Get all the remaining words.
                    words = tree.equal.all_words()
                    # Map the list to get the correct words.
                    return list(map(create_map(buffer), words)) + answer
                return answer

            if tree.key == word[0]: # The prefix is correct, continue to find next.
                if tree.equal != None:
                    return get_all(tree.equal, word[1:], buffer + tree.key)
            if tree.key < word[0]: # The letter is incorrect, search for prefix.
                if tree.left != None:
                    return get_all(tree.left, word, buffer)
            if tree.key > word[0]: # The letter is incorrect, search for prefix.
                if tree.right != None:
                    return get_all(tree.right, word, buffer)
            return answer
        return get_all(self, word)

    # Suppress the word from the tree.
    def suppress(self, word):
        pass

    # Add a string representation.
    def spaces(self, nb):
        string = " " * nb + str(self.final) + " " + str(self.key) + "\n"
        if self.left != None:
            string += self.left.spaces(nb + 2)
        if self.equal != None:
            string += self.equal.spaces(nb + 2)
        if self.right != None:
            string += self.right.spaces(nb + 2)
        return string
    def __repr__(self):
        return self.spaces(0)

# Functions to comply specifications...
def Recherche(tree, word):
    return tree.contains(word)
def ComptageMot(tree):
    return tree.number_words()
def ListeMots(tree):
    return tree.all_words()
def ComptageNil(tree):
    if tree == None:
        return 1
    number = 0
    if tree.is_empty:
        return 4
    number += ComptageNil(tree.left)
    number += ComptageNil(tree.equal)
    number += ComptageNil(tree.right)
    return number
def Hauteur(tree):
    return tree.height()
def ProfondeurMoyenne(tree):
    return tree.average_height()
def Prefixe(tree, word):
    return tree.prefix(word)
def Suppression(tree, word):
    return tree.suppress(word)

tree = TernarySearchTree()
for word in example.split(' '):
    tree.add_word(word)
print(tree.contains('dactylographie'))
print(tree.number_words())
print(tree.all_words())
print(ComptageNil(tree))
print(Hauteur(tree))
print(ProfondeurMoyenne(tree))
print(Prefixe(tree, 'ap'))
Suppression(tree, 'dactylo')
print(tree.contains('dactylo'))
