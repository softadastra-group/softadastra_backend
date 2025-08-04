file(GLOB_RECURSE AI_SOURCES CONFIGURE_DEPENDS *.cpp)

if (AI_SOURCES)
    add_library(ai STATIC ${AI_SOURCES})

    target_include_directories(ai PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    find_package(OpenCV REQUIRED)

    target_link_libraries(ai PUBLIC ${OpenCV_LIBS})

    target_compile_features(ai PUBLIC cxx_std_17)
endif()
