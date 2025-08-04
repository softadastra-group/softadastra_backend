# ────────────────────────────────────────────────────────────────
# 📦 Compilation of the Adastra library
# ────────────────────────────────────────────────────────────────

# 🔹 Add submodules of adastra
add_subdirectory(tools)
add_subdirectory(utils)
add_subdirectory(crypto)
add_subdirectory(network)
add_subdirectory(storage)
add_subdirectory(core)
add_subdirectory(config)
add_subdirectory(test_utils)
add_subdirectory(ai) # comment out if unused

# 🔹 Create the static library `adastra` with a dummy source
add_library(adastra STATIC dummy.cpp)

# 🔹 Link all submodules
target_link_libraries(adastra PUBLIC
    tools
    utils
    crypto
    network
    storage
    core
    config
    test_utils
    ai

    Threads::Threads
    nlohmann_json::nlohmann_json
)

# 🔹 Include headers
target_include_directories(adastra PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# 🔹 Enable C++17
target_compile_features(adastra PUBLIC cxx_std_17)
