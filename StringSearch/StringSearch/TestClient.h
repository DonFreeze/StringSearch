#pragma once

#include <iostream>

#include "StringSearch.h"

class TestClient
{
public:
    TestClient()
    {
        generateWordList();
        //generateComplexWordList();
    }
    void runTest1();
    void runTest2();
    void runTest3();
    void runTest4();  // Complex Search
    void runTest5(); // Test with unused characters 
    void runTest6(); // Test with to long searchString
private:
    StringSearch stringSearch;
    void generateWordList();
    //void generateComplexWordList();
    void printWordList( WordList& list );

    bool runTest( std::string testString, WordList& expecterResultList );
    //bool runTest2(std::string testString, WordList& expectedResultList );
    bool compareWordLists( WordList& list1, WordList& list2 );
    
    WordList wordList;
    //WordList complexList;

};