#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <toml++/toml.h>
using namespace std::string_view_literals;


TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("No error in parsing the example report.") {
        /* Example snippet:
         *
         * TODO(sthagen) fill in the example liaison info
         */
        static constexpr std::string_view configuration = R"(
            [library]
            name = "toml++"
            authors = ["Mark"]
            cpp = 17
        )"sv;

        try {
            toml::table tbl = toml::parse(configuration);
            std::cout << tbl << "\n";
        }
        catch (const toml::parse_error& err) {
            std::cerr << "Parsing failed:\n" << err << "\n";
            return 1;
        }
            REQUIRE(tbl);
    }
}
