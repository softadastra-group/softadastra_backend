# ────────────────────────────────────────────────────────────────
# 📦 Softadastra entrypoint compilation (main.cpp)
# ────────────────────────────────────────────────────────────────

set(MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

if(EXISTS ${MAIN_FILE})
    add_executable(softadastra_main ${MAIN_FILE})

    target_include_directories(softadastra_main PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Crow/include
    )

    target_link_libraries(softadastra_main PRIVATE     
        adastra
        softadastra
        Threads::Threads
        nlohmann_json::nlohmann_json
        crow
        SQLite::SQLite3
        MySQLCppConn::MySQLCppConn
    )

    target_compile_features(softadastra_main PRIVATE cxx_std_17)
endif()

