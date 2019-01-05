#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Binary_tree/binaryTree.h"
//used catch2 for unit testing
//https://github.com/catchorg/Catch2


//binary tree testing

TEST_CASE("Testing for tree -> pre-order, delete, insert, frequency") {

    std::cout << "Binary tree testing" << std::endl;

    //insert words to tree1
    auto tree1 = new Tree();
    std::vector<std::string> tree1Words = {"if", "you", "fell", "down", "yesterday", "stand", "up", "today"};

    for (int i = 0; i < tree1Words.size(); i++) {
        tree1->insertNode(tree1->rNode, tree1Words[i]);
    }
    //insert words to tree2
    auto tree2 = new Tree();
    std::vector<std::string> tree2Words = {"opportunity", "does", "not", "knock", "it", "presents", "itself", "when",
                                           "you", "beat", "down", "the", "door"};

    for (int i = 0; i < tree2Words.size(); i++) {
        tree2->insertNode(tree2->rNode, tree2Words[i]);
    }
    //insert words to tree3
    auto tree3 = new Tree();
    std::vector<std::string> tree3Words = {"start", "where", "you", "are", "use", "what", "you", "have", "do", "what",
                                           "you", "can"};

    for (int i = 0; i < tree3Words.size(); i++) {
        tree3->insertNode(tree3->rNode, tree3Words[i]);
    }

    SECTION("Testing tree if it's returning in pre-order") {
        //1st test for tree1
        std::vector<std::string> treeVector1;
        std::vector<std::string> tree1VecPreOrder = tree1->preOrder(tree1->rNode, treeVector1);
        std::vector<std::string> correct_preOrder_test1 = {"if", "fell", "down", "you", "yesterday", "stand", "up",
                                                           "today"};
        REQUIRE(tree1VecPreOrder == correct_preOrder_test1);
        //2nd test for tree2
        std::vector<std::string> treeVector2;
        std::vector<std::string> tree2VecPreOrder = tree2->preOrder(tree2->rNode, treeVector2);
        std::vector<std::string> correct_preOrder_test2 = {"opportunity", "does", "beat", "not", "knock", "it", "down",
                                                           "door", "itself", "presents", "when", "the", "you"};
        REQUIRE(tree2VecPreOrder == correct_preOrder_test2);
        //3rd test for tree3
        std::vector<std::string> treeVector3;
        std::vector<std::string> tree3VecPreOrder = tree3->preOrder(tree3->rNode, treeVector3);
        std::vector<std::string> correct_preOrder_test3 = {"start", "are", "have", "do", "can", "where", "use", "what",
                                                           "you"};
        REQUIRE(tree3VecPreOrder == correct_preOrder_test3);
    }

    SECTION("Testing tree is deleting properly") {

        SECTION("Deleting leaf nodes") {

            std::cout << "testing delete tree1 (word = today)" << std::endl;
            tree1->deleteNode(tree1->rNode, "today");
            REQUIRE(!tree1->searchTree(tree1->rNode, "today"));

            std::cout << std::endl;
            std::cout << "testing delete tree2 (word = itself)" << std::endl;
            tree2->deleteNode(tree2->rNode, "itself");
            tree2->searchTree(tree2->rNode, "itself");
            REQUIRE(!tree2->searchTree(tree2->rNode, "itself"));

            std::cout << std::endl;
            std::cout << "testing delete tree3 (word = can)" << std::endl;
            tree3->deleteNode(tree3->rNode, "can");
            REQUIRE(!tree3->searchTree(tree3->rNode, "can"));
        }

        SECTION("Deleting parent with one child") {
            std::cout << "Deleting parent with one child" << std::endl;

            std::cout << std::endl;
            std::cout << "testing delete tree1 (word = you)" << std::endl;
            tree1->deleteNode(tree1->rNode, "you");
            REQUIRE(!tree1->searchTree(tree1->rNode, "you"));
            REQUIRE(tree1->rNode->right->data == "yesterday");


            std::cout<<std::endl;
            std::cout << "testing delete tree2 (word = not)" << std::endl;
            tree2->deleteNode(tree2->rNode, "not");
            REQUIRE(!tree2->searchTree(tree2->rNode,"not"));
            REQUIRE(tree2->rNode->left->right->data == "knock");

            std::cout<<std::endl;
            std::cout << "testing delete tree3 (word = are)" << std::endl;
            tree3->deleteNode(tree3->rNode,"are");
            REQUIRE(!tree3->searchTree(tree3->rNode,"are"));
            REQUIRE(tree3->rNode->left->data == "have");
        }

        SECTION("Deleting parent with two children"){
            std::cout << "Deleting parent with two children" <<std::endl;

            std::cout<<std::endl;
            std::cout << "testing delete tree2 (word = it)" << std::endl;
            tree2->deleteNode(tree2->rNode, "it");
            REQUIRE(!tree2->searchTree(tree2->rNode,"it"));
            REQUIRE(tree2->rNode->left->right->left->left->data == "down");

            std::cout<<std::endl;
            std::cout << "testing delete tree3 (word = where)" << std::endl;
            tree3->deleteNode(tree3->rNode,"where");
            REQUIRE(!tree3->searchTree(tree3->rNode, "where"));
            REQUIRE(tree3->rNode->right->data == "what");
        }

        SECTION("Testing delete with frequency"){
            std::cout << "Deleting data with more than one frequency" <<std::endl;

            std::cout<<std::endl;
            std::cout << "testing delete tree3 (word = what)" << std::endl;
            tree3->deleteNode(tree3->rNode,"what");
            REQUIRE(tree3->searchTree(tree3->rNode, "what"));
            REQUIRE(tree3->rNode->right->left->right->data == "what");
            REQUIRE(tree3->rNode->right->left->right->frequency == 1);

            std::cout<<std::endl;
            std::cout << "testing delete tree3 (word = you)" << std::endl;
            tree3->deleteNode(tree3->rNode,"you");
            REQUIRE(tree3->searchTree(tree3->rNode, "you"));
            REQUIRE(tree3->rNode->right->right->data == "you");
            REQUIRE(tree3->rNode->right->right->frequency == 2);
        }
    }

    SECTION("Testing tree is inserting properly"){
        //test tree 1 properly
        REQUIRE(tree1->rNode->data == "if");
        REQUIRE(tree1->rNode->left->data == "fell");
        REQUIRE(tree1->rNode->left->left->data == "down");
        REQUIRE(tree1->rNode->right->data == "you");
        REQUIRE(tree1->rNode->right->left->data == "yesterday");
        REQUIRE(tree1->rNode->right->left->left->data == "stand");
        REQUIRE(tree1->rNode->right->left->left->right->data == "up");
        REQUIRE(tree1->rNode->right->left->left->right->left->data == "today");

        //test tree3 insert and frequency
        //insert
        REQUIRE(tree3->rNode->data == "start");
        REQUIRE(tree3->rNode->left->data == "are");
        REQUIRE(tree3->rNode->left->right->data == "have");
        REQUIRE(tree3->rNode->left->right->left->data == "do");
        REQUIRE(tree3->rNode->left->right->left->left->data == "can");
        REQUIRE(tree3->rNode->right->data == "where");
        REQUIRE(tree3->rNode->right->left->data == "use");
        REQUIRE(tree3->rNode->right->left->right->data == "what");
        REQUIRE(tree3->rNode->right->right->data == "you");
        //frequency
        REQUIRE(tree3->rNode->right->left->right->frequency == 2);
        REQUIRE(tree3->rNode->right->right->frequency == 3);
    }
}

TEST_CASE("Testing tree from txt file"){

    std::cout << "Binary tree testing from file" << std::endl;

    auto tree1 = new Tree();
    tree1->putWordsToTree("words.txt");

    //pre-order test
    std::vector<std::string> tree1VecPreOrder = tree1->preOrder(tree1->rNode,tree1->preOrderVec);
    std::vector<std::string> correctPreOrder = {"cat","ant","bee","dog","crab","cow","dinosaur","lion","elephant","snake"};
    REQUIRE(tree1VecPreOrder == correctPreOrder);

    //insert test
    REQUIRE(tree1->rNode->data == "cat");
    REQUIRE(tree1->rNode->left->data == "ant");
    REQUIRE(tree1->rNode->left->right->data == "bee");
    REQUIRE(tree1->rNode->right->data == "dog");
    REQUIRE(tree1->rNode->right->left->data == "crab");
    REQUIRE(tree1->rNode->right->left->left->data == "cow");
    REQUIRE(tree1->rNode->right->left->right->data == "dinosaur");
    REQUIRE(tree1->rNode->right->right->data == "lion");
    REQUIRE(tree1->rNode->right->right->left->data == "elephant");
    REQUIRE(tree1->rNode->right->right->right->data == "snake");

    //delete test
    std::cout<<std::endl;
    std::cout << "testing delete for main (word = cow) -> leaf node" << std::endl;
    tree1->deleteNode(tree1->rNode, "cow");
    REQUIRE(!tree1->searchTree(tree1->rNode,"cow"));

    std::cout<<std::endl;
    std::cout << "testing delete for main (word = ant) -> one child" << std::endl;
    tree1->deleteNode(tree1->rNode, "ant");
    REQUIRE(!tree1->searchTree(tree1->rNode,"ant"));
    REQUIRE(tree1->rNode->left->data == "bee");

    std::cout<<std::endl;
    std::cout << "testing delete for main (word = dog) -> two children" << std::endl;
    tree1->deleteNode(tree1->rNode, "dog");
    REQUIRE(!tree1->searchTree(tree1->rNode,"dog"));
    REQUIRE(tree1->rNode->right->data == "dinosaur");

    std::cout<<std::endl;
    std::cout << "testing delete for main (word = bee) -> more than one frequency" << std::endl;
    tree1->deleteNode(tree1->rNode, "bee");
    REQUIRE(tree1->searchTree(tree1->rNode,"bee"));
    REQUIRE(tree1->rNode->left->data == "bee");
    REQUIRE(tree1->rNode->left->frequency == 1);

    //search
    std::cout<<std::endl;
    std::cout<< "testing for searching (Capital recognizable?, extra symbol?)" <<std::endl;
    std::cout<<std::endl;
    REQUIRE(tree1->searchTree(tree1->rNode, "snake"));
    std::cout<<std::endl;
    REQUIRE(!tree1->searchTree(tree1->rNode, "Snake"));
    std::cout<<std::endl;
    REQUIRE(!tree1->searchTree(tree1->rNode, "SNAKE"));
    std::cout<<std::endl;
    REQUIRE(!tree1->searchTree(tree1->rNode, "sna.ke"));
}
