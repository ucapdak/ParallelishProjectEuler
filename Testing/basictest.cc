#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Addition", "" ){
    int one = 1;
    REQUIRE( one * 2 == 2 );
}
