file(GLOB_RECURSE DATABASE_SOURCES CONFIGURE_DEPENDS *.cpp)

if (DATABASE_SOURCES)
    add_library(database STATIC ${DATABASE_SOURCES})

    target_include_directories(database PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_libraries(database PUBLIC
        MySQLCppConn::MySQLCppConn
    )

    target_compile_features(database PUBLIC cxx_std_17)
endif()
