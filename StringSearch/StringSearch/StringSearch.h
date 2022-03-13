#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <future>

using WordList = std::vector<std::string>;


class StringSearch
{
public:
    StringSearch();
    WordList search( std::string searchString, WordList& wordList );
private:
    void executeSearch( std::promise<WordList>&& promise, std::string searchString, std::string* searchBeginPtr, size_t length );
    //void someFunction( std::promise<int>&& p );
};
