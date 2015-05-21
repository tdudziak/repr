find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

get_filename_component(TEST_DATA_DIR "data" ABSOLUTE)
configure_file("test_config.h.in" "test_config.h")

llvm_map_components_to_libnames(llvm_libs support core asmparser)

include_directories(${LLVM_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

add_executable(StdlibTests StdlibTests.cpp)
target_link_libraries(StdlibTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXTRA_LIBS})
add_test(StdlibTests StdlibTests)

add_executable(LLVMTests LLVMTests.cpp)
target_link_libraries(LLVMTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${llvm_libs} ${EXTRA_LIBS})
add_test(LLVMTests LLVMTests)
