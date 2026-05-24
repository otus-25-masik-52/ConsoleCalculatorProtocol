cmake_minimum_required(VERSION 3.28)

project(ConsoleCalculatorProtocol VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
include(CTest)

# =========================
# Dependencies
# =========================

FetchContent_Declare(
  NlohmannJsonLib
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)

FetchContent_Declare(
  Googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

if (MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

FetchContent_MakeAvailable(NlohmannJsonLib Googletest)

# =========================
# Generated protocol version
# =========================

set(CONSOLE_CALCULATOR_PROTOCOL_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CONSOLE_CALCULATOR_PROTOCOL_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CONSOLE_CALCULATOR_PROTOCOL_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/calculator-protocol/version/protocol-version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/calculator-protocol/version/protocol-version.h
  @ONLY
)

# =========================
# Library
# =========================

add_library(calculator_protocol
  src/calculator-protocol/codes/operation-code.cpp
  src/calculator-protocol/codes/status-code.cpp
  src/calculator-protocol/errors/protocol-error.cpp

  src/calculator-protocol/formats/json-codec.cpp

  src/calculator-protocol/models/calculation-response.cpp

  src/calculator-protocol/validators/validator.cpp
)

target_include_directories(calculator_protocol
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_link_libraries(calculator_protocol
  PRIVATE
  nlohmann_json::nlohmann_json
)

target_compile_features(calculator_protocol
  PUBLIC
  cxx_std_20
)

# =========================
# Tests
# =========================

if (BUILD_TESTING)
  add_executable(calculator_protocol_tests
    tests/compatibility-tests.cpp
    tests/json-codec-tests.cpp
    tests/operation-code-tests.cpp
    tests/request-validator-tests.cpp
    tests/status-code-tests.cpp
  )

  target_link_libraries(calculator_protocol_tests
    PRIVATE
    calculator_protocol
    GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(calculator_protocol_tests)
endif ()