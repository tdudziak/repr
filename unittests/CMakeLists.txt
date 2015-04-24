find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# llvm_map_components_to_libnames(llvm_libs support core irreader)

include_directories(${LLVM_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)
add_definitions(${LLVM_DEFINITIONS})

add_executable(StdlibTests StdlibTests.cpp)
target_link_libraries(StdlibTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXTRA_LIBS})
