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

Node* newNode(std::string data){
    auto nNode = new Node();
    nNode->data = data;
    nNode->left = nullptr;
    nNode->right = nullptr;
    nNode->frequency = 1;
    return nNode;
}

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

Node* Tree::maxValue(Node* rNode){
    if (rNode->right == nullptr){
        return rNode;
    }
    else{
        maxValue(rNode->right);
    }
}

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
