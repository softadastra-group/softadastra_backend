# ────────────────────────────────────────────────────────────────
# 📦 Softadastra entrypoint compilation (main.cpp)
# ────────────────────────────────────────────────────────────────

set(MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

if(EXISTS ${MAIN_FILE})
    add_executable(softadastra ${MAIN_FILE})

    target_include_directories(softadastra PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Crow/include
    )

    target_link_libraries(softadastra PRIVATE     
        adastra
        softadastra_lib
        Threads::Threads
        nlohmann_json::nlohmann_json
        crow
        SQLite::SQLite3
        MySQLCppConn::MySQLCppConn
    )

    target_compile_features(softadastra PRIVATE cxx_std_17)
endif()

