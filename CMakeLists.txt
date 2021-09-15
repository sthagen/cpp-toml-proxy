cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# ---- Project ----

project(toml_proxy LANGUAGES CXX)

option(TOML_EXAMPLES "whether or not to build the examples" ON)

# ---- Fetch CPM ----

set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# ---- Add dependencies via CPM ----
# See https://github.com/TheLartians/CPM.cmake for details and examples

CPMAddPackage(
  NAME tomlplusplus
  GIT_REPOSITORY https://github.com/sthagen/cpp-toml.git
  VERSION 2.3.0                                  
  # 2.3.0 is released by Mark Gillard (upstream), but we read from a fork so use the associated commit directly
  GIT_TAG 4face4d5bf16326aca0da1fb33876dbca63b6e2f 
)

if(tomlplusplus_ADDED)
  add_library(tomlplusplus INTERFACE)
  target_include_directories(tomlplusplus INTERFACE ${tomlplusplus_SOURCE_DIR}/include/)
  message("Added ${tomlplusplus_SOURCE_DIR}/include/ as include")
endif()

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY sthagen/doctest
  GIT_TAG 2020.12
)

# ---- Create binary ----

add_executable(toml_test main.cpp)
target_link_libraries(toml_test doctest tomlplusplus)
set_target_properties(toml_test PROPERTIES CXX_STANDARD 17)

# ---- Enable testing ----

enable_testing() 
add_test(toml_test toml_test)

# ---- Create the examples ----

message(STATUS "Note the fetched includes are taken from below: ${FETCHCONTENT_BASE_DIR}")
if (TOML_EXAMPLES)
    macro(toml_examples EXAMPLENAME)
        add_executable(${EXAMPLENAME} ${ARGN})
        set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER examples)
        set_target_properties(${EXAMPLENAME} PROPERTIES CXX_STANDARD 17)
        target_include_directories(${EXAMPLENAME} PUBLIC "${FETCHCONTENT_BASE_DIR}/tomlplusplus-src/include/")
        add_test(NAME ${EXAMPLENAME} COMMAND ${EXAMPLENAME})
    endmacro()
    add_subdirectory(examples)
endif()
