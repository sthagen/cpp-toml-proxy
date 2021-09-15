#include <iostream>

#include <toml++/toml.h>
using namespace std::string_view_literals;

int main() {
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
}
