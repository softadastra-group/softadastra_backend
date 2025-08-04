# ────────────────────────────────────────────────────────────────
# 🧪 Integration Tests — folder `test/`
# ────────────────────────────────────────────────────────────────

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

# Create an executable for integration tests
add_executable(softadastra_tests ${TEST_SOURCES})

target_include_directories(softadastra_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(softadastra_tests PRIVATE
    adastra
    softadastra_lib
    Threads::Threads
    nlohmann_json::nlohmann_json
    gtest
    gtest_main
)

target_compile_features(softadastra_tests PRIVATE cxx_std_17)

# Add to CTest
add_test(NAME softadastra_integration_tests COMMAND softadastra_tests)

