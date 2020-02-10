/*test.cpp*/

//
// Lab week 09 / project #04
// 
// Testing for util.cpp?
//

#include <iostream>
#include <vector>

#include "avl.h"
#include "util.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) ???") 
{
    vector<string>  values;
    REQUIRE(GetRecord("students", 0 , 5)[0] == "123456");
    REQUIRE(GetRecord("students", 0 , 5)[1] == "pooja");
    REQUIRE(GetRecord("students", 0 , 5)[2] == "sarkar");
    REQUIRE(GetRecord("students", 0 , 5)[3] == "psarka12");
    REQUIRE(GetRecord("students", 0 , 5)[4] == "pooja@piazza.com");
}

TEST_CASE("(1) ???") 
{
    vector<streamoff>  matches;
    REQUIRE(LinearSearch("students", 82, 5, "kim", 3)[0] == 3);
    //REQUIRE(GetRecord("students", 0 , 5)[1] == "pooja");    
}


