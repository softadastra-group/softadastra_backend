# ────────────────────────────────────────────────────────────────
# 📦 Softadastra Library Compilation
# ────────────────────────────────────────────────────────────────

file(GLOB_RECURSE SOFTADASTRA_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(softadastra STATIC ${SOFTADASTRA_SOURCES})

target_include_directories(softadastra PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crow/include      
)

target_link_libraries(softadastra PUBLIC
    adastra
    Threads::Threads
    nlohmann_json::nlohmann_json
    crow
    SQLite::SQLite3
    MySQLCppConn::MySQLCppConn
)

target_compile_features(softadastra PUBLIC cxx_std_17)
