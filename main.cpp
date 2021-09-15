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
    TEST_CASE ("No error in parsing the configuration fixture.") {
        /* Example snippet:
         *
         * toml::table tbl = toml::parse(configuration);
         */
        toml::table tbl = toml::parse(configuration);
        std::ostringstream os;
        os << tbl;
        CHECK(!os.str().empty());
        REQUIRE(os.str().find("[library]") != std::string::npos);
    }
}
