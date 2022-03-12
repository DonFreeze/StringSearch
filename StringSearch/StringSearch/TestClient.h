#pragma once

#include <iostream>

#include "StringSearch.h"

class TestClient
{
public:
    TestClient()
    {
        generateWordList();
    }
    void runTest1();
    void runTest2();
    void runTest3();
private:
    StringSearch stringSearch;
    void generateWordList();
    void printWordList( WordList& list );

    bool runTest( std::string testString, WordList& expecterResultList );
    bool compareWordLists( WordList& list1, WordList& list2 );

    WordList wordList;

};