#include <iostream>
#include <cmath>
#include <vector>


#include "TestClient.h"


int main()
{
    for(int i = 0; i < 10; i++)
    {
        TestClient testClient;
        testClient.runTest1();
        testClient.runTest2();
        testClient.runTest3();
        //testClient.runTest4();
        testClient.runTest5();
        testClient.runTest6();

    }
    return 0;
}
