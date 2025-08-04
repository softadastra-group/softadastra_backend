file(GLOB_RECURSE CRYPTO_SOURCES CONFIGURE_DEPENDS *.cpp)

if (CRYPTO_SOURCES)
    add_library(crypto STATIC ${CRYPTO_SOURCES})

    target_include_directories(crypto PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_libraries(crypto PUBLIC OpenSSL::SSL OpenSSL::Crypto)

    target_compile_features(crypto PUBLIC cxx_std_17)
endif()
