//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Andrej Vadovsky <xvadova00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Andrej Vadovsky
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"
using namespace ::testing;
//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
class NonEmptyTree : public Test{
    
    void SetUp() override {
        tree.InsertNode(1); 
        tree.InsertNode(2); 
        tree.InsertNode(3);
        tree.InsertNode(-15);
        tree.InsertNode(100);
        tree.InsertNode(150);
    }

protected:
    BinaryTree tree;
};

class EmptyTree : public Test{
protected:
    BinaryTree tree;
};

class TreeAxioms : public Test{

    void SetUp() override {
        tree.InsertNode(3);
        tree.InsertNode(-15);
        tree.InsertNode(100);
        tree.InsertNode(150);
        tree.InsertNode(8);
        tree.InsertNode(-9);
        tree.InsertNode(56);
        tree.InsertNode(200);
    }

protected:
    BinaryTree tree;
};

TEST_F(EmptyTree,InsertNode)
{
    ASSERT_TRUE(tree.GetRoot()==NULL);
    auto node=tree.InsertNode(3);
    ASSERT_TRUE(tree.GetRoot()!=NULL);
    ASSERT_EQ(node.first,true);
    EXPECT_TRUE(node.second->key==3);
}

TEST_F(EmptyTree, DeleteNode){
    ASSERT_TRUE(tree.GetRoot()==NULL);
    EXPECT_EQ(tree.DeleteNode(5), false);
}

TEST_F(EmptyTree, FindNode){
    ASSERT_TRUE(tree.GetRoot()==NULL);
    EXPECT_EQ(tree.FindNode(5), nullptr);
}

TEST_F(NonEmptyTree,InsertNode)
{
    ASSERT_TRUE(tree.GetRoot()!=NULL);
    auto node=tree.InsertNode(3);
    int i=0;
    do
    {
        i++;
        node=tree.InsertNode(i);
    }while(!node.first);
    ASSERT_TRUE(node.first==true);
    EXPECT_TRUE(node.second->key==i);
}

TEST_F(NonEmptyTree,FindNode)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetAllNodes(leafNodes);
    auto node=leafNodes[0]->key;
    int count=0;
    do
    {
        for(int i=0;i<leafNodes.size();i++)
        {
            if(node==leafNodes[i]->key)
            {
                count++;
            }
        }
        if(count==0)
        {
            break;
        }
        else
        {
            count=0;
            node=node+23;
        }
    
    }while(true);
    ASSERT_TRUE(tree.FindNode(node)==NULL);
    ASSERT_TRUE(tree.FindNode(leafNodes[0]->key)!=NULL);
    Node_t *ptr1=tree.FindNode(leafNodes[0]->key);
    EXPECT_TRUE(ptr1==leafNodes[0]);
}

TEST_F(NonEmptyTree,DeleteNode)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetAllNodes(leafNodes);
    auto node=leafNodes[0]->key;
    int count=0;
    do
    {
        for(int i=0;i<leafNodes.size();i++)
        {
            if(node==leafNodes[i]->key)
            {
                count++;
            }
        }
        if(count==0)
        {
            break;
        }
        else
        {
            count=0;
            node=node+23;
        }
    
    }while(true);
    ASSERT_FALSE(tree.DeleteNode(node));  //Neexistujuca hodnota
    auto node2=leafNodes[0]->key;
    EXPECT_TRUE(tree.DeleteNode(leafNodes[0]->key));
    EXPECT_FALSE(tree.DeleteNode(node2));   //Uz je vymazana
}

TEST_F(TreeAxioms,Axiom1)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    for (size_t i = 0; i < leafNodes.size(); i++) {
        EXPECT_EQ(leafNodes[i]->color,tree.BLACK);
    }
}

TEST_F(TreeAxioms,Axiom2)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetAllNodes(leafNodes);
    for (size_t i=0;i<leafNodes.size();i++) {
        if(leafNodes[i]->color==tree.RED)
        {
            EXPECT_EQ(leafNodes[i]->pLeft->color,tree.BLACK);
            EXPECT_EQ(leafNodes[i]->pRight->color,tree.BLACK);
        }
    }
}

TEST_F(TreeAxioms,Axiom3)
{//nastavim si pocet jedneho z prkov kolko ma medzi rootom ciernych a potom to skusam na dalsich prkvkoch
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    size_t count=0;
    size_t count2=0;
    while(leafNodes[0]->pParent!=NULL)
    {
        leafNodes[0]=leafNodes[0]->pParent;            
        if(leafNodes[0]->color==tree.BLACK)
        {
            count++;
        }
    }
    for(size_t i=1;i<leafNodes.size();i++) {
        while(leafNodes[i]->pParent!=NULL)
        {
            leafNodes[i]=leafNodes[i]->pParent;
            if(leafNodes[i]->color==tree.BLACK)
            {
                count2++;
            }
        }
        EXPECT_EQ(count,count2);
        count2=0;
    }
}
