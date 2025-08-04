# ────────────────────────────────────────────────────────────────
# 📦 Softadastra Library Compilation
# ────────────────────────────────────────────────────────────────

file(GLOB_RECURSE SOFTADASTRA_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(softadastra_lib STATIC ${SOFTADASTRA_SOURCES})

target_include_directories(softadastra_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crow/include      # ✅ version locale
)

target_link_libraries(softadastra_lib PUBLIC
    adastra
    Threads::Threads
    nlohmann_json::nlohmann_json
    crow
    SQLite::SQLite3
    MySQLCppConn::MySQLCppConn
)

target_compile_features(softadastra_lib PUBLIC cxx_std_17)
