#include <iostream>
#include <memory>

#include "TestClient.h"


int main()
{
    TestClient testClient;
    for (int i = 0; i < 1; i++)
    {
        testClient.runTest1();
        testClient.runTest2();
        testClient.runTest3();
        testClient.runTest4();
        testClient.runTest5();
    }
    return 0;
}
