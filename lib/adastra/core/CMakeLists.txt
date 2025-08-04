file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS *.cpp)

if (CORE_SOURCES)
    add_library(core STATIC ${CORE_SOURCES})

    target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_compile_features(core PUBLIC cxx_std_17)
endif()
