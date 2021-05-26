#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <set>
#include <vector>
#include <tuple>
using namespace std;

#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;

//***********************basic cteate tree tests************************************************************************

TEST_CASE("create big tree") {
    BinaryTree<int> my_tree1;
    my_tree1.add_root(0);
    for (int i = 0; i < 10000; ++i) {
        if (i % 2 == 0) {
            CHECK_NOTHROW(my_tree1.add_right(i, i + 1));
        } else {
            CHECK_NOTHROW(my_tree1.add_left(i, i + 1));
        }
    }
}

TEST_CASE("Not existing values") {
    BinaryTree<int> my_tree2;
    my_tree2.add_root(0);
    for (int i = 0; i < 50; ++i) {
        if (i % 2 == 0) {
            CHECK_NOTHROW(my_tree2.add_right(i, i + 1));
        } else {
            CHECK_NOTHROW(my_tree2.add_left(i, i + 1));
        }
    }
    //try to insert childe to not exist parent
    for (int i = 100; i < 150; ++i) {
        if (i % 2 == 0) {
            CHECK_THROWS(my_tree2.add_right(i, i + 1));
        } else {
            CHECK_THROWS(my_tree2.add_left(i, i + 1));
        }
    }
}

//*********************************add root,add left and add right tests***************************************************
TEST_CASE("add_root") {
    for (int i = 0; i < 15; ++i) {
        BinaryTree<int> int_tree;
        int rand_int = rand() % 100+1;
        CHECK_NOTHROW(int_tree.add_root(rand_int));
        CHECK_EQ(*int_tree.begin(), rand_int);
        CHECK_EQ(*int_tree.begin_inorder(), rand_int);
        CHECK_EQ(*int_tree.begin_postorder(), rand_int);
        CHECK_EQ(*int_tree.begin_preorder(), rand_int);
    }

    for (int i = 0; i < 15; ++i) {
        BinaryTree<string> string_tree;
        int rand_int = rand() % 100+1;
        string rand_string = to_string(rand_int);
        CHECK_NOTHROW(string_tree.add_root(rand_string));
        CHECK_EQ(*string_tree.begin(), rand_string);
        CHECK_EQ(*string_tree.begin_inorder(), rand_string);
        CHECK_EQ(*string_tree.begin_postorder(), rand_string);
        CHECK_EQ(*string_tree.begin_preorder(), rand_string);
    }

    //create object/////////////////////////////
    class person {
      string name;
      int age;

     public:
      person(string n ,int a) : name(n), age(a) {}

      bool operator==(const person &p) const { 
        return (name==p.name && age==p.age); 
      }
    };
    //end////////////////////////////////////////
    
    for (int i = 0; i < 15; ++i) {
        BinaryTree<person> person_tree;
        int rand_int = rand() % 100+1;
        string rand_string= to_string(rand_int);
        person my_person = person(rand_string, rand_int);
        CHECK_NOTHROW(person_tree.add_root(my_person));
        CHECK_EQ(*person_tree.begin(), my_person);
        CHECK_EQ(*person_tree.begin_inorder(), my_person);
        CHECK_EQ(*person_tree.begin_postorder(), my_person);
        CHECK_EQ(*person_tree.begin_preorder(), my_person);
    }
}

TEST_CASE("add_right") {
    ///////basic////////////////////////////////////////////////////////////////////////////////////
    BinaryTree<int> right_tree;
    right_tree.add_root(0);
    for (int i=1; i<=15; i++){
        right_tree.add_right(i-1,i);
    }
    int temp=0;
    ///inorder sould do - 0,1,......,15
    for (auto it = right_tree.begin(); it != right_tree.end(); ++it){
        CHECK(*it == temp++);
    }

    /////random ////////////////////////////////////////////////////////////////////////////////////
    BinaryTree<int> rand_tree;
    set<int> rand_set;
    vector<int> rand_vec;
    int location=-1;// save the last node 

    //random values to the set
    while(rand_set.size()<=15){
        rand_set.insert(rand() % 300 +1);
    }

    for(auto node = rand_set.begin(); node != rand_set.end(); ++node){
        if (node==rand_set.begin()){
            CHECK_NOTHROW(rand_tree.add_root(*node));
        }
        else{
            CHECK_NOTHROW(rand_tree.add_right(location, *node));   
        }
        rand_vec.push_back(*node);
        location = *node;
    }

    //chack the basic iterator (inorder) 
    unsigned long i = 0;
    for (auto it = rand_tree.begin(); it != rand_tree.end(); ++it){
        CHECK(*it == rand_vec.at(i++));
    }
}

TEST_CASE("add_left") {
    ////////basic////////////////////////////////////////////////////////////////////////////////////
    BinaryTree<int> left_tree;
    left_tree.add_root(0);
    for (int i=1; i<=15; i++){
        left_tree.add_left(i-1,i);
    }
    int temp=15;
    //inorder should do- 15,14,.....0
    for (auto it = left_tree.begin(); it != left_tree.end(); ++it){
        CHECK(*it == temp--);
    }

    /////random ////////////////////////////////////////////////////////////////////////////////////
    BinaryTree<int> rand_tree;
    set<int> rand_set;
    vector<int> rand_vec;
    int location=-1;// save the last node 

    //random values to the set
    while(rand_set.size()<=15){
        rand_set.insert(rand() % 300 +1);
    }

    for(auto node = rand_set.begin(); node != rand_set.end(); ++node){
        if (node==rand_set.begin()){
            CHECK_NOTHROW(rand_tree.add_root(*node));
        }
        else{
            CHECK_NOTHROW(rand_tree.add_left(location, *node));   
        }
        rand_vec.push_back(*node);
        location = *node;
    }

    //chack the basic iterator (inorder) 
    unsigned long i = rand_vec.size() - 1;
    for (auto it = rand_tree.begin(); it != rand_tree.end(); ++it){
        CHECK(*it == rand_vec.at(i--));
    }
}

//********************************iterators tests**************************************************************************
TEST_CASE ("operators(*,==,++,!=) and basic iterators checks"){
    BinaryTree<int> my_tree;
    my_tree.add_root(0).add_left(0, 1).add_right(0, -1);
    /*
          0
         / \
        1  -1
    */
    
    //basic itrator 1, 0, -1(sould be the same as on-order)
    auto it_basic = my_tree.begin();
    CHECK(*it_basic==1);
    CHECK_NOTHROW(++it_basic);
    CHECK(*it_basic==0);
    CHECK_NOTHROW(++it_basic);
    CHECK(*it_basic==-1);
    CHECK(*it_basic!=1);
    
    //preorder itrator 0, 1, -1
    auto it_pre = my_tree.begin_preorder();
    CHECK(*it_pre==0);
    CHECK_NOTHROW(++it_pre);
    CHECK(*it_pre==1);
    CHECK_NOTHROW(++it_pre);
    CHECK(*it_pre==-1);
    CHECK(*it_pre!=0);
    
    //inorder iterator 1, 0, -1
    auto it_in = my_tree.begin_inorder();
    CHECK(*it_in==1);
    CHECK_NOTHROW(++it_in);
    CHECK(*it_in==0);
    CHECK_NOTHROW(++it_in);
    CHECK(*it_in==-1);
    CHECK(*it_in!=1);

    //postorder iterator 1, -1, 0
    auto it_post = my_tree.begin_postorder();
    CHECK(*it_post==1);
    CHECK_NOTHROW(++it_post);
    CHECK(*it_post==-1);
    CHECK_NOTHROW(++it_post);
    CHECK(*it_post==0);
    CHECK(*it_post!=1);

}

TEST_CASE("pre order iterator checks") {
    BinaryTree<int> pre_tree;
    pre_tree.add_root(1);
    pre_tree.add_left(1,2);
    pre_tree.add_right(1,7);
    pre_tree.add_left(2,3);
    pre_tree.add_right(2,6);
    pre_tree.add_left(3,4);
    pre_tree.add_right(3,5);
    pre_tree.add_left(7,8);
    pre_tree.add_right(7,9);
    pre_tree.add_left(9,10);
    /*
                1 
             /     \        
            2       7          
           / \     /  \
          3   6   8    9
         / \          /
        4   5       10

    */
    int count =1;
    for (auto it = pre_tree.begin_preorder(); it != pre_tree.end_preorder(); ++it){
        CHECK(*it == count++);
    }  
}

TEST_CASE("in order iterator checks") {
    BinaryTree<int> in_tree;
    in_tree.add_root(6);
    in_tree.add_left(6,4);
    in_tree.add_right(6,8);
    in_tree.add_left(4,2);
    in_tree.add_right(4,5);
    in_tree.add_left(2,1);
    in_tree.add_right(2,3);
    in_tree.add_left(8,7);
    in_tree.add_right(8,10);
    in_tree.add_left(10,9);
    /*
                6 
             /     \        
            4       8          
           / \     /  \
          2   5   7   10
         / \         /
        1   3      9

    */
    int count =1;
    for (auto it = in_tree.begin_inorder(); it != in_tree.end_inorder(); ++it){
        CHECK(*it == count++);
    }  
}

TEST_CASE("post order iterator checks") {
    BinaryTree<int> post_tree;
    post_tree.add_root(10);
    post_tree.add_left(10,5);
    post_tree.add_right(10,9);
    post_tree.add_left(5,3);
    post_tree.add_right(5,4);
    post_tree.add_left(3,1);
    post_tree.add_right(3,2);
    post_tree.add_left(9,6);
    post_tree.add_right(9,8);
    post_tree.add_left(8,7);
    /*
               10 
             /     \        
            5       9          
           / \     /  \
          3   4   6    8
         / \          /
        1   2        7

    */
    int count =1;
    for (auto it = post_tree.begin_postorder(); it != post_tree.end_postorder(); ++it){
        CHECK(*it == count++);
    }  
}




