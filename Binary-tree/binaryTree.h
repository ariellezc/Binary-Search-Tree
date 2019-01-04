#include <iostream>
#include <new>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <regex>

class Node{
public:
    std::string data;
    Node* left;
    Node* right;
    int frequency;
};

class Tree{
public:
    Node* rNode;
    Node* insertNode(Node* rNode, std::string dataToInsert);
    std::string removeCharacters(std::string stringOfWords);
    std::string readFile(std::string fileName);
    std::vector<std::string> preOrder(Node* rNode, std::vector<std::string> preOrderVec);
    bool searchTree(Node* rNode, std::string dataToSearch);
    void putWordsToTree(std::string fileName);
    Node* deleteNode(Node* rNode, std::string dataToDelete);
    Node* maxValue(Node* rNode);
    std::vector<std::string> preOrderVec;
    std::vector<std::string> listOfWords;
};

/*https://www.geeksforgeeks.org/remove-characters-alphabets-string/
Implemented it so it works with only lowercase and spaces
if it's an alphabet shift it to the left and increment the count of j removing characters that does is not an between a - z*/
std::string Tree::removeCharacters(std::string stringOfWords){
    int j = 0;
    for(int i=0; i<stringOfWords.size(); i++){
        if (((stringOfWords[i] >= 'a' && stringOfWords[i] <= 'z') || isspace(stringOfWords[i]))){
            stringOfWords[j] = stringOfWords[i];
            j++;
        }
    }
    return stringOfWords.substr(0,j);
}

/*tutorial on files: http://www.cplusplus.com/doc/tutorial/files/
tutorial on regex: http://www.cplusplus.com/reference/regex/regex_replace/
convert all strings to lowercase so it's easier to handle
call function to remove unnecessary strings
return the word replaceing multiple whitespaces into a single one*/
std::string Tree::readFile(std::string fileName){
    std::string words,finalWord;
    std::ifstream file(fileName);
    std::regex re("\\s{2,}");
    if (!file){
        std::cout << "File failed to open." << std::endl;
    }
    while (std::getline(file,words)){
        std::transform(words.begin(), words.end(), words.begin(), ::tolower);
        finalWord = removeCharacters(words);
    }
    file.close();
    return regex_replace(finalWord, re, " ");
}

//insert all words in listOfWords vector into the tree by calling the function insertNode
void Tree::putWordsToTree(std::string fileName){

    std::stringstream wordsStringStream(readFile(fileName));
    std::string line;
    while (getline(wordsStringStream, line, ' ')){
        listOfWords.emplace_back(line);
    }
    for (int i=0;i<listOfWords.size();i++){
        insertNode(rNode,listOfWords[i]);
    }
}

/*create new node
set data equals to the string passed
make left and right null and return node*/
Node* newNode(std::string data){
    auto nNode = new Node();
    nNode->data = data;
    nNode->left = nullptr;
    nNode->right = nullptr;
    nNode->frequency = 1;
    return nNode;
}

/*first check if the tree doesnt have a value and if there isn't -> create new node and pass the data
if root is null create new node and pass data
if the data is equivalent to the dataToBeInserted don't create new node just increment frequency
goes to the left if data is lower and right if higher*/
Node* Tree::insertNode(Node* rNode, std::string dataToInsert) {
    if(this->rNode == nullptr){
        this->rNode = newNode(dataToInsert);
    }
    if (rNode == nullptr){
        rNode = newNode(dataToInsert);
    }
    else if (dataToInsert == rNode->data){
        (rNode->frequency)++;
    }
    else if (dataToInsert <= rNode->data){
        rNode->left = insertNode(rNode->left, dataToInsert);
    }
    else{
        rNode->right = insertNode(rNode->right, dataToInsert);
    }
    return rNode;
}

/*check first if the tree uis empty
goes to through the tree left or right according to the value to be inserted implicitly saying where to go
if it gets to null without the data searched output value not found and return false (do the opposite if it doesnt meet requirement)*/
bool Tree::searchTree(Node* rNode, std::string dataToSearch){
    if (this->rNode == nullptr){
        std::cout << "Tree is empty." << std::endl;
    }
    else if (rNode == nullptr){
        std::cout << "Value not found." << std::endl;
        return false;
    }
    else if(rNode->data == dataToSearch){
        std::cout << "Value " << dataToSearch << " is found." << std::endl;
        return true;
    }
    else if(dataToSearch < rNode->data){
        std::cout << "Value " << dataToSearch << " is less than " << rNode->data << " going to the left." << std::endl;
        searchTree(rNode->left, dataToSearch);
    }
    else {
        std::cout << "Value " << dataToSearch << " is greater than " << rNode->data << " going to the right." << std::endl;
        searchTree(rNode->right, dataToSearch);
    }
}

/*slide number 10 pseudocode help me implement this (returns a vector instead)
check if the tree is empty
output the data first, followed by the left value, once done move to the right value*/
std::vector<std::string> Tree::preOrder(Node* rNode,std::vector<std::string> preOrderVec){
    if (rNode == nullptr){
        std::cout << "Tree is empty" << std::endl;
    }
    preOrderVec.emplace_back(rNode->data);
    if (rNode->left != nullptr){
        preOrderVec = preOrder(rNode->left,preOrderVec);
    }
    if (rNode->right != nullptr){
        preOrderVec = preOrder(rNode->right,preOrderVec);
    }
    return preOrderVec;
}

//looks for the max value found at the right side (stops when it's null and return node)
Node* Tree::maxValue(Node* rNode){
    if (rNode->right == nullptr){
        return rNode;
    }
    else{
        maxValue(rNode->right);
    }
}


/*function for deleting node
http://faculty.winthrop.edu/dannellys/csci271/binary_tree_delete.htm
check if the tree is empty first
does a search for the data to be deleted
decrements frequency of the word if it's already there so only make changes to the frequency of the word
if no child just delete root
if right child has no child, make root current, point to the left and delete current
if left has no child, make root current, point to the right and delete current
if it has two children, look for the max value from the left subtree*/
Node* Tree::deleteNode(Node* rNode, std::string dataToDelete){
    if (rNode == nullptr){
        std::cout << "Tree is empty" << std::endl;
    }
    else if (dataToDelete < rNode->data){
        rNode->left = deleteNode(rNode->left,dataToDelete);
    }
    else if (dataToDelete > rNode->data){
        rNode->right = deleteNode(rNode->right,dataToDelete);
    }
    else {
        if (rNode->frequency > 1){
            (rNode->frequency)--;
        }
        else if ((rNode->left == nullptr) && (rNode->right == nullptr)){
            delete rNode;
            rNode = nullptr;
        }
        else if (rNode->right == nullptr){
            Node* currentNode = rNode;
            rNode = rNode->left;
            delete currentNode;

        }
        else if (rNode->left == nullptr) {
            Node* currentNode = rNode;
            rNode = rNode->right;
            delete currentNode;
        }
        else{
            Node* currentNode = maxValue(rNode->left);
            rNode->data = currentNode->data;
            rNode->left = deleteNode(rNode->left,currentNode->data);
        }
    }
    return rNode;
}

/*int main() {
    auto tree1 = new Tree();
    tree1->putWordsToTree("words.txt");
    std::cout << std::endl;
    std::vector<std::string> preorder = tree1->preOrder(tree1->rNode,tree1->preOrderVec);
    std::cout << std::endl;
    std::cout << std::endl;
    tree1->searchTree(tree1->rNode, "a");
    tree1->deleteNode(tree1->rNode, "bee");
    tree1->insertNode(tree1->rNode,"spider");
}*/
