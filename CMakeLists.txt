cmake_minimum_required(VERSION 3.16)
project(LuaCppBridge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Trouver Lua sur le système
find_package(Lua REQUIRED)

add_executable(lua_test main.cpp)

# Lier les headers et les binaires de Lua
target_include_directories(lua_test PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(lua_test PRIVATE ${LUA_LIBRARIES})
