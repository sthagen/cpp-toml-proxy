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
    TEST_CASE ("No error in parsing the example report.") {
        /* Example snippet:
         *
         * toml::table tbl = toml::parse(configuration);
         */
        try {
            toml::table tbl = toml::parse(configuration);
            std::ostringstream os;
            os << tbl;
            CHECK(os.str());
            REQUIRE(os.str().find("[library]") != std::string.npos);
        }
        catch (const toml::parse_error& err) {
            FAIL("Parsing failed:", err);
        }
    }
}
