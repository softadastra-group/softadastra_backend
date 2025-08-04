file(GLOB_RECURSE CONFIG_SOURCES CONFIGURE_DEPENDS *.cpp)

if (CONFIG_SOURCES)
    add_library(config STATIC ${CONFIG_SOURCES})

    target_include_directories(config PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_compile_features(config PUBLIC cxx_std_17)
endif()
