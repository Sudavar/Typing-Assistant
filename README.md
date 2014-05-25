This was implemented as a home exercise in subject of System Programing of Department of Informatics of UoA.
This program loads a dictionary from a file with a word in each line (should add CSV file option) and then
when the users types a text, it suggests some words if the TAB button is pressed. User can also delete characters
pressing the BACKSPACE, unfortunately it is not some kind of text editor. There is no graphic interface, it works
from terminal. Some user can redirect standard output to a file and thus save his text.

Implementation explained, though it's in Greek for now:
	Η Trie είναι όλο η δομή που βλέπει ο χρήστης και περιέχει ένα TrieNode που είναι η ρίζα, έναν
προσωρινό κόμβο για να ξέρουμε που βρισκόμαστε και κρατάει και τα γράμματα που έχει
πληκτρολογήσει μέχρι τώρα ο χρήστης.
	Το TrieNode είναι οι κόμβοι του δένδρου που αναπαριστούν και τα γράμματα. Κάθε ένας
περιέχει 26 παιδιά κόμβους (όσοι και το αγγλικό λεξικό) (αυτό αλλάζει με την σταθερά DICT),
έναν κόμβο προς τον γονέα του, έναν πίνακα από Ν δείκτες σε φύλλα για να βρίσκουμε άμεσα
τις Ν πιο χρησιμοποιούμενες λέξεις, ένα δείκτη σε φύλο που αντιπροσωπεύει την λέξη μέχρι τον
κόμβο και κρατά μέσα την συχνότητα εμφάνισης της λέξης. Τέλος υπάρχει και ένας χαρακτήρας
για να κρατά το γράμμα του κόμβου. Αρχικά δεν το είχα προσθέσει γιατί στη διάσχιση του
δένδρου από πάνω προς τα κάτω, δεν χρειαζόταν, ενώ στην από κάτω προς τα πάνω για να
βρεθεί το γράμμα θα χρειαζόταν ακόμα log n * DICT πράξεις στην χειρότερη περίπτωση, οπότε
προτίμησα να αποθηκεύω τον χαρακτήρα
	Το TrieLeaf που δεν περιέχει τίποτε ιδιαίτερο παρά την συχνότητα της λέξεις και τον γονέα του
φύλλου. Χρησιμεύει ωστόσο για να δείξουμε στη λέξη όχι από τον γονέα κόμβο και να για
βρούμε την λέξη με την συνάρτηση string* TrieLeaf::find_word(TrieNode *).