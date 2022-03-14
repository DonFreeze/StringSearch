#pragma once

#include <iostream>
#include <algorithm>
#include "StringSearch.h"

class TestClient
{
public:
    TestClient()
    {   
        wordList.reserve( pow( letters.length(), wordlength) ); // to avoid realocation of memory when generating the list 
        generateWordList();
    }

    void runTest1();
    void runTest2();
    void runTest3();
    void runTest4(); // Test with to long searchString
    void runTest5(); // Test with unused characters 
    
private:
    StringSearch stringSearch;
    WordList wordList;
    std::string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    static constexpr std::size_t wordlength{ 4 };

    void generateWordList();
    void printWordList( WordList& list );

    bool runTest( std::string testString, WordList& expecterResultList );
    bool compareWordLists( WordList& list1, WordList& list2 );
};