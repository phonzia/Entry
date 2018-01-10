#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Entry.h"
#include "../src/stringtool.h"

TEST_CASE("Stringtool trimAll", "[trimAll]") {
    std::string trimed = cppbase::stringtool::trimAll("   ***   ");
    REQUIRE( trimed == "***");
}

TEST_CASE( "Entry * * * * * * always match", "[Entry]" ) {
    sine::Entry entry;
    REQUIRE(entry.parse("* * * * * *"));
}