file(GLOB_RECURSE NETWORK_SOURCES CONFIGURE_DEPENDS *.cpp)

if (NETWORK_SOURCES)
    add_library(network STATIC ${NETWORK_SOURCES})

    target_include_directories(network PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_libraries(network PUBLIC Threads::Threads)

    target_compile_features(network PUBLIC cxx_std_17)
endif()
