cmake_minimum_required(VERSION 3.16)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp Interpreter/Interpreter.cpp Interpreter/Interpreter.h StringProcessor/StringProcessor.cpp StringProcessor/StringProcessor.h Interpreter/showResult.h Interpreter/callAPI.h Table/Table.cpp Table/Table.h GlobalVariable/GlobalVariable.h GlobalVariable/GlobalVariable.cpp)