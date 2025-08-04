file(GLOB_RECURSE UTILS_SOURCES CONFIGURE_DEPENDS *.cpp)

if (UTILS_SOURCES)
    add_library(utils STATIC ${UTILS_SOURCES})

    target_include_directories(utils PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    find_package(OpenCV REQUIRED)
    target_link_libraries(utils PUBLIC ${OpenCV_LIBS})

    target_compile_features(utils PUBLIC cxx_std_17)
endif()

