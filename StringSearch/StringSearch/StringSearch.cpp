#include <iostream>
#include <thread>
#include <future>
#include <windows.h>


#include "StringSearch.h"


using namespace std;

StringSearch::StringSearch()
{
    
}

void StringSearch::executeSearch(string searchString, WordList& wordList, WordList& resultList)
{

}

void someFunction( std::promise<WordList>&& promise, string searchString, WordList wordList )
{
    WordList resultList;
    

    for( string word : wordList )
    {
        if( word.rfind( searchString, 0 ) == 0 ) // pos=0 limits the search to the prefix
        {
            resultList.push_back( word );
        }
            
    }
    promise.set_value(resultList);
}

WordList StringSearch::search(string searchString, WordList& wordList)
{
    const int numberCpuCores = std::thread::hardware_concurrency();
    static constexpr int threadNum = 4;
    thread threads[threadNum];
    WordList listParts[threadNum];
    WordList resultLists[threadNum];

    std::promise<WordList> promises[threadNum];
    std::future<WordList> futures[threadNum];

    size_t const partSize = wordList.size() / threadNum;
    //cout << "WordList Begin : " << &wordList.front() << endl;
    //cout << "WordList End :   " << &wordList.back() << endl;
    for (int index = 0; index < threadNum; index++)
    {
        WordList listPart;
        if (index != threadNum-1)
        {

            listPart = WordList( wordList.begin() + partSize * index, wordList.begin() + partSize * (index + 1) );
        }
        else
        {
            listPart= WordList( wordList.begin() + partSize * index, wordList.end() );
        }
        //cout << "SubList Begin: "<< index << " " << &listPart.front() << endl;
        //cout << "SubList End  : "<< index << " " << &listPart.back() << endl;
        futures[index] = promises[index].get_future();

        threads[index] = thread( someFunction, std::move(promises[index]), searchString, listPart);
        //threads[index] = thread(executeSearch, searchString, listParts[index], resultLists[index]);
    }

    // Get results from threads and combine them
    WordList resultList;
    for( int i = 0; i < threadNum; i++ )
    {
        resultLists[i] = futures[i].get();
        resultList.insert( resultList.end(), resultLists[i].begin(), resultLists[i].end() );
        threads[i].join();
    }

    /*for (string word : resultList)
    {
        cout << word << endl;
    }*/
 

     return resultList;


}
