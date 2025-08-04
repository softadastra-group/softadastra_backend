file(GLOB_RECURSE STORAGE_SOURCES CONFIGURE_DEPENDS *.cpp)

if (STORAGE_SOURCES)
    add_library(storage STATIC ${STORAGE_SOURCES})

    target_include_directories(storage PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_libraries(storage PUBLIC SQLite::SQLite3)

    target_compile_features(storage PUBLIC cxx_std_17)
endif()
