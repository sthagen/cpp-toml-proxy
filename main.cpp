#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <toml++/toml.h>
using namespace std::string_view_literals;

static constexpr std::string_view configuration = R"(
    [library]
    name = "toml++"
    authors = ["Mark"]
    cpp = 17
)"sv;


TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("No error in parsing the configuration fixture with round trip.") {
        /* Example snippet:
         *
         * toml::table tbl = toml::parse(configuration);
         */
        toml::table tbl = toml::parse(configuration);
        std::ostringstream os;
        os << tbl;
        SUBCASE("The configuration repersentation is not empty in round trip.") {
            REQUIRE(!os.str().empty());
        }
        SUBCASE("The section is present in round trip.") {
            REQUIRE(os.str().find("[library]") != std::string::npos);
        }
        SUBCASE("The array values of the authors key are not lost in round trip.") {
            REQUIRE(os.str().find("authors = [ 'Mark' ]") != std::string::npos);
        }
    }
}
