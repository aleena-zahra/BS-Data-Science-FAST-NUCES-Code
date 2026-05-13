#include<fstream>
#include<string>
#include<ncurses.h>
using namespace std;


struct Letter {
    char letter;
    Letter* next;
    Letter* prev;
    Letter(char l){
        letter = l;
        next = prev = NULL;
    }
};

class Word {
    Letter* head;
    Letter* tail;
    int length;
   
    public:
    Word(){
        head = tail = NULL;
        length = 0;
    }
    //deep copy constructor
    Word(const Word &word){
        head = tail = NULL;
        length = 0;
        //iterate through linked list
        Letter* temp = word.head;
        while(temp != NULL){
            addLetter(temp->letter);
            temp = temp->next;
        }
    }
    //assignment operator
    Word& operator=(const Word &word){
        //check for self assignment
        if(this == &word){
            return *this;
        }
        //delete the current linked list
        while(head != NULL){
            removeLetter();
        }
        //iterate through linked list
        head = tail = NULL;
        length=0;
        Letter* temp = word.head;
        while(temp != NULL){
            addLetter(temp->letter);
            temp = temp->next;
        }
        return *this;
    }
    ~Word(){
        while(head!=NULL){
            this->removeLetter();
        }
    }
    Letter* getNodeAtIndex(int index){
        if(index < 0 || index >= length){
            return NULL;
        }
        Letter* temp = head;
        for(int i = 0; i < index; i++){
            temp = temp->next;
        }
        return temp;
    }
    //inserted at the end
    void addLetter(char l){
        Letter* newLetter = new Letter(l);
        if(head == NULL){
            head = newLetter;
            tail = newLetter;
        } else {
            tail->next = newLetter;
            newLetter->prev = tail;
            tail = newLetter;
        }
        length++;
    }
    void removeLetter(){
        if(tail == NULL){
            return;
        }
        if(tail == head){
            delete tail;
            head = NULL;
            tail = NULL;
        } else {
            Letter* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
            temp = NULL;
        }
        length--;
    }
    void removeLetterAtIndex(int index){
        if(index < 0 || index >= length){
            printw("Invalid index\n");
            return;
        }
        if(index == length - 1){
            removeLetter();
            return;
        }
        Letter* node = getNodeAtIndex(index);
        if(node == head){
            head = head->next;
            head->prev = NULL;
            delete node;
            node = NULL;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            node = NULL;
        }
        length--;
    }
    bool isSpace(){
        return tail->letter == ' ';
    }
    Letter* getHead(){
        return this->head;
    }
    int getLength(){
        return this->length;
    }
    void print(){
        Letter* temp = head;
        while(temp != NULL){
            printw("%c",temp->letter);
            temp = temp->next;
        }
        printw("\n");
        refresh();
    }
    void swapNodes(int index1, int index2){
        if (index1 == index2 || index1 < 0 || index1>index2 || index2 >= length){
            printw("Invalid indexes\n");
            return;
        }
        //find the nodes at index1 and index2
        Letter* node1 = getNodeAtIndex(index1);
        Letter* node2 = node1->next;
        //swap the data of the nodes
        char temp = node1->letter;
        node1->letter = node2->letter;
        node2->letter = temp;
    }
    void addLetterAtIndex(char l, int index){
        if(index < 0 || index > length){
            printw("Invalid index\n");
            return;
        }
        if(index == length){
            addLetter(l);
            return;
        }
        Letter* newLetter = new Letter(l);
        //find node at the index to insert
        Letter* node = getNodeAtIndex(index);
        
        if(node == head){
            newLetter->next = head;
            head->prev = newLetter;
            head = newLetter;
        } else {
            newLetter->next = node;
            newLetter->prev = node->prev;
            node->prev->next = newLetter;
            node->prev = newLetter;
        }
        length++;
    }
    void setNodeAtIndex(char l, int index){
        if(index < 0 || index >= length){
            printw("Invalid index\n");
            return;
        }
        Letter* temp = head;
        for(int i = 0; i < index; i++){
            temp = temp->next;
        }
        temp->letter = l;
    }
       void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            clear();
            string line;
            while (getline(file, line)) {
                printw(" %s ", line.c_str());
            }
            file.close();
        }
    }
        void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            Letter* current = head;
            while (current != NULL) {
                file << current->letter;
                current = current->next;
            }
            file.close();
        }
    }
};
struct Node
{
    Node *left, *right;
    string dicWord;
    int height;

    Node(string dicWord = 0) {
        this->dicWord = dicWord;
        this->left = this->right = NULL;
        this->height = 1;
    }
};

class AVL
{
    Node *root;

    int getMax(int h1, int h2) {
        return (h1 > h2) ? h1 : h2;
    }

    int getHeight(Node *node) {
        if(node == NULL)
            return 0;
        return node->height;
    }

    Node* rightRotate(Node *node) {
        Node *node2 = node->left;
        Node *T2 = node2->right;

        // Perform rotation
        node2->right = node;
        node->left = T2;

        // Update heights
        node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
        node2->height = getMax(getHeight(node2->left), getHeight(node2->right)) + 1;

        // Return new root
        return node2;
    }

    Node* leftRotate(Node *node) {
        Node *node2 = node->right;
        Node *temp = node2->left;

        node2->left = node;
        node->right = temp;

        node->height = 1+ getMax(getHeight(node->left), getHeight(node->right));
        node2->height = 1+ getMax(getHeight(node2->left), getHeight(node2->right));

        return node2;
    }

    int getBalance(Node *node) {
        if (node == NULL)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* insertNode(Node *node, string dicWord) {
        if (node == NULL)
            return new Node(dicWord);
        if (dicWord < node->dicWord)
            node->left = insertNode(node->left, dicWord);
        else if (dicWord > node->dicWord)
            node->right = insertNode(node->right, dicWord);
        else
            return node;

        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

        // Get the balance factor
        int balance = getBalance(node);

        // Balance the tree
        // Left Left
        if (balance > 1 && dicWord < node->left->dicWord)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && dicWord > node->right->dicWord)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && dicWord > node->left->dicWord) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && dicWord < node->right->dicWord) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    Node * findWord(Node *root, string word){
        if (root == NULL)
            return root;
        if ( word < root->dicWord)
            return findWord(root->left, word);
        else if ( word > root->dicWord)
            return findWord(root->right, word);
        else {
            return root;
        }
    }

    void printAVL(Node *root) {
        if (root == NULL)
            return;
        printAVL(root->left);
        printw(" %s \n",(root->dicWord).c_str());
        printAVL(root->right);
    }
    Node * removeNode(Node *root, string dicWord) {
        if (root == NULL)
            return root;
        if (dicWord < root->dicWord)
            root->left = removeNode(root->left, dicWord);

        else if (dicWord > root->dicWord)
            root->right = removeNode(root->right, dicWord);

        else {
            // node with only one child or no child
            Node* temp;
            if (root->left == NULL || root->right == NULL) {
                if(root->left == NULL){
                    temp = root->right;
                }
                else temp = root->left;
                //no children
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else // One child case
                    *root = *temp; // copy child
                    delete temp;
                    temp = NULL;
            } else {
                // node with two children: Get the 
                // inorder successor (smallest in 
                // the right subtree)
                Node* temp = getMinValueNode(root->right);

                root->dicWord = temp->dicWord;

                root->right = removeNode(root->right, temp->dicWord);
            }
        }

        if (root == NULL)
            return root;

        root->height = 1 + max(getHeight(root->left), 
                    getHeight(root->right));

        int balance = getBalance(root);

        // Left Left
        if (balance >= 2 && 
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right
        if (balance >= 2 && 
            getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right
        if (balance <= -2 && 
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left
        if (balance <= -2 && 
            getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node *getMinValueNode(Node *node) {
        Node *current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }
    void deleteAVL(Node* node) {
        if (node != NULL) {
            deleteAVL(node->left);
            deleteAVL(node->right);
            delete node;
        }
    }

public:
    AVL() {
        root = NULL;
    }

    ~AVL() {
        deleteAVL(root);
    }
    Node *getRoot() {
        return root;
    }
    void remove(string dicWord) {
        this->root = removeNode(this->root, dicWord);
    }

    void insert(string dicWord) {
        this->root = insertNode(this->root, dicWord);
    }

    void print() {
        printAVL(root);
        printw("\n");
    }
    bool findWord(string word){
        Node * result = findWord(root, word);
        if(result==NULL){
            return false;
        }
        return true;
    }
    
};
//word.substr(0, i) + c + word.substr(i);
class SpellChecker{
    
    bool exited;

    //private helper functions
    string getWordString(Word &word){
        string result = "";
        Letter* current = word.getHead();
        while (current != NULL) {
            result += current->letter;
            current = current->next;
        }
        return result;
    }
    public:
    AVL dictionary;
    Word currentWord;
    SpellChecker(){
        exited = false;
        loadDictionaryInAVL();
    }
    void loadDictionaryInAVL(){
        //load dictionary in AVL tree
        //each line in text file is a word
        //open file
        ifstream file("dictionary.txt");
        string wordInFile;
        while(getline(file, wordInFile)){
            if(wordInFile[0]>=65 && wordInFile[0]<=90){
                wordInFile[0] = wordInFile[0]+32; //going upper to lowercasee
            }
            int len = wordInFile.length();
            //printw("original length: "<<len<<"\n");;
            wordInFile.erase(len-1); // remove the last character
            //printw("new length: "<<wordInFile.length()<<"\n");;
            dictionary.insert(wordInFile);
        }
        file.close();
        string head = dictionary.getRoot()->dicWord;
    }
    
    
    void checkWord(){
        string currentWord = getWordString(this->currentWord);
        if(dictionary.findWord(currentWord)){
            printw("%s found in dictionary\n",currentWord.c_str());
        }
        else {
            printw("%s word NOT found in dictionary\n",currentWord.c_str());
            displaySuggestions();
        }
    }
    void displaySuggestions(){
        letterReversal();
        letterInsertion();
        letterOmission();
        letterSubstitution();
    }
    bool notExited(){
        return !exited;
    }
    //for all functions below stop once a word in the dictionary is found
    void letterReversal(){
        //swapping adjacent nodes of copy linked list and checking if word is in dictionary
        
        for (int index =0 ; index < currentWord.getLength() -1 ; index ++){
            //deep copy of linked list currentWord
            Word copy = currentWord;
            //swap adjacent nodes, index and index + 1
            copy.swapNodes(index, index + 1);
            //check if copy is in dictionary
            string modifiedWord = getWordString(copy);
            if(dictionary.findWord(modifiedWord)){
                printw("Did you mean %s ?\n",modifiedWord.c_str());
                return;
            }
        }
        printw("No suggestions found with letter reversal\n");
    }
    void letterInsertion(){
        //loop through linked list and insert all 26 letter at each index in list
        for (int index = 0 ; index< currentWord.getLength(); index++){
            //insert all 26 letters at index
            for (char ch = 'a'; ch <= 'z'; ch++){
                //deep copy of linked list currentWord
                Word copy = currentWord;
                //insert c at index
                copy.addLetterAtIndex(ch,index);
                //check if copy is in dictionary
                string modifiedWord = getWordString(copy);
                if(dictionary.findWord(modifiedWord)){
                    printw("Did you mean %s ?\n",modifiedWord.c_str());
                    return;
                }
            }
        }
        printw("No suggestions found with letter insertion\n");
    }
    void letterOmission(){
        //loop through linked list and remove a node at every index and check if word is in dictionary
        for (int index =0 ; index <currentWord.getLength(); index++){
            //deep copy of linked list currentWord
            Word copy = currentWord;
            //remove node at index
            copy.removeLetterAtIndex(index);
            //check if copy is in dictionary
            string modifiedWord = getWordString(copy);
            if(dictionary.findWord(modifiedWord)){
                printw("Did you mean %s ?\n",modifiedWord.c_str());
                return;
            }

        }
        printw("No suggestions found with letter omission\n");
    }
    void letterSubstitution(){
        //loop through linked list and replace each nodes data with the 25 other letters
        for (int index = 0 ; index< currentWord.getLength(); index++){
            char currentLetter = currentWord.getNodeAtIndex(index)->letter;
            //insert all 26 letters at index
            for (char ch = 'a'; ch <= 'z'; ch++){
                if(ch!=currentLetter){
                    //deep copy of linked list currentWord
                    Word copyWord = currentWord;
                    //change letter at index
                    copyWord.setNodeAtIndex(ch,index);  
                    //check if copy is in dictionary
                    string modifiedWord = getWordString(copyWord);
                    
                    if(dictionary.findWord(modifiedWord)){
                        printw("Did you mean %s ?\n",modifiedWord.c_str());
                        return;
                    }
                }   
            }
        }
        printw("No suggestions found with letter substitution\n");
    }
    void setCurrentWord(string word){
        wipeCurrentWord();
        //add the word to the linked list
        for(int i = 0; i < word.length(); i++){
            currentWord.addLetter(word[i]);
        }
    }
    void wipeCurrentWord(){
        while(currentWord.getHead() != NULL){
            currentWord.removeLetter();
        }
    }
    void play(){
        while(exited==false){
            printw("Enter a word: \n");
            int letter;
            while ((letter = getch()) != ' ') {
                if( letter == 27){
                    exited = true;
                }
                else if(letter == '.'){
                    currentWord.saveToFile("file.txt");
                    break;
                    
                }
                else if (letter == ','){
                    currentWord.loadFromFile("file.txt");
                    break;
                }
                else if (letter == 10) {
                checkWord();
                break;
                } 
                else if (letter == KEY_BACKSPACE || letter == 127) {
                    currentWord.removeLetter();
                    printw("\b");
                }
                else {
                currentWord.addLetter(letter);
                }
            }
            wipeCurrentWord();
        }
    }
    
};
int main(){
    initscr();               
    echo();                   
    cbreak(); 
    keypad(stdscr, TRUE);    

    SpellChecker spellChecker;
    string currentWord;
    
    spellChecker.play();
    
    endwin();               
    
      
    return 0;
}