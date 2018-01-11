#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Entry.h"
#include "../src/stringtool.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>

TEST_CASE("Stringtool trimAll", "[trimAll]") {
    std::string trimed = cppbase::stringtool::trimAll("   ***   ");
    REQUIRE( trimed == "***");
}

TEST_CASE("Stringtool countChar", "[countChar]") {
    REQUIRE(cppbase::stringtool::countChar("abc", 'a') == 1);
    REQUIRE(cppbase::stringtool::countChar("abc", 'b') == 1);
    REQUIRE(cppbase::stringtool::countChar("abc", 'c') == 1);
    REQUIRE(cppbase::stringtool::countChar("abc", 'd') == 0);
    REQUIRE(cppbase::stringtool::countChar("abca", 'a') == 2);
}

TEST_CASE( "Entry * * * * * * always match", "[Entry]" ) {
    sine::Entry entry;
    REQUIRE(entry.parse("* * * * * *"));
    REQUIRE(entry.parse("5,10 * * * * *"));
    REQUIRE_FALSE(entry.parse("5/* * * * * *"));
    REQUIRE(entry.parse("*/5 * * * * *"));
    entry.print();

    std::tm t = {};
    std::istringstream ss("2018-01-11 00:00:00");
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    auto test_time = mktime(&t);
    REQUIRE(entry.check(test_time));
    REQUIRE_FALSE(entry.check(test_time + 1));
    REQUIRE_FALSE(entry.check(test_time + 2));
    REQUIRE_FALSE(entry.check(test_time + 3));
    REQUIRE_FALSE(entry.check(test_time + 4));
    REQUIRE(entry.check(test_time + 5));
}