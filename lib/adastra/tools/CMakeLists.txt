file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS *.cpp)

if (TOOLS_SOURCES)
    add_library(tools STATIC ${TOOLS_SOURCES})

    target_include_directories(tools PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    find_package(OpenCV REQUIRED)
    target_link_libraries(tools PUBLIC ${OpenCV_LIBS})

    target_compile_features(tools PUBLIC cxx_std_17)
endif()
