#include <iostream>
#include <thread>
#include <future>
#include <windows.h>

#include "StringSearch.h"

using namespace std;


void StringSearch::executeSearch( std::promise<WordList>&& promise, string searchString, string* searchBeginPtr, size_t length )
{
    WordList resultList;
    if( searchBeginPtr != nullptr )
    {
        for( int i = 0; i < length; i++ )
        {
            if( searchBeginPtr[i].rfind(searchString, 0) == 0 ) // pos=0 limits the search to the prefix
            {
                resultList.push_back( searchBeginPtr[i] );
            }
        }
        promise.set_value( resultList );
    }
}


void StringSearch::search( string searchString, WordList& wordList, WordList& resultList )
{   
    const size_t threadNum{ 4 };
    thread threads[threadNum];
    std::promise<WordList> promises[threadNum];
    std::future<WordList> futures[threadNum];

    size_t partSize = wordList.size() / threadNum;
    size_t leftover = wordList.size() % threadNum;

    for( int i = 0; i < threadNum; i++ )
    {
        futures[i] = promises[i].get_future();
        if( i == threadNum-1 )
        {
            partSize += leftover;
        }
        threads[i] = thread( &StringSearch::executeSearch, this, std::move( promises[i] ), searchString, wordList.data() + partSize * i, partSize );
    }

    // Get results from threads and merge them
    for( int i = 0; i < threadNum; i++ )
    {
        WordList partResultList{ futures[i].get() };
        resultList.insert( resultList.end(), partResultList.begin(), partResultList.end() );
        threads[i].join();
    }
}
