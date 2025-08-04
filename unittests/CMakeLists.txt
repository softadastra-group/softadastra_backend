# ────────────────────────────────────────────────────────────────
# 🧪 Softadastra Unit Tests
# ────────────────────────────────────────────────────────────────

file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(softadastra_unittests ${UNIT_TEST_SOURCES})

target_include_directories(softadastra_unittests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(softadastra_unittests PRIVATE
    adastra
    softadastra
    Threads::Threads
    nlohmann_json::nlohmann_json
    gtest
    gtest_main
)

if(ENABLE_CATCH2)
    target_link_libraries(softadastra_unittests PRIVATE Catch2::Catch2WithMain)
endif()

add_test(NAME softadastra_all_tests COMMAND softadastra_unittests)
