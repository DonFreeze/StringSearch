#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <future>

using WordList = std::vector<std::string>;


class StringSearch
{
public:
    void search( std::string searchString, WordList& wordList, WordList& resultList );
private:
    void executeSearch( std::promise<WordList>&& promise, std::string searchString, std::string* searchBeginPtr, size_t length );
};
