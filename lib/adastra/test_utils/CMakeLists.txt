file(GLOB_RECURSE TEST_UTILS_SOURCES CONFIGURE_DEPENDS *.cpp)

if (TEST_UTILS_SOURCES)
    add_library(test_utils STATIC ${TEST_UTILS_SOURCES})

    target_include_directories(test_utils PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_compile_features(test_utils PUBLIC cxx_std_17)
endif()
