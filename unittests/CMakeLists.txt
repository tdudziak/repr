find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

llvm_map_components_to_libnames(llvm_libs support core irreader)

include_directories(${LLVM_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)
add_definitions(${LLVM_DEFINITIONS})
add_definitions("-DENABLE_REPR_LLVM")

add_executable(StdlibTests StdlibTests.cpp)
target_link_libraries(StdlibTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${llvm_libs} ${EXTRA_LIBS})
add_test(StdlibTests StdlibTests)

add_executable(LLVMTests LLVMTests.cpp)
target_link_libraries(LLVMTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${llvm_libs} ${EXTRA_LIBS})
add_test(LLVMTests LLVMTests)
