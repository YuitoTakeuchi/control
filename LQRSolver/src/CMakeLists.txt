cmake_minimum_required(VERSION 3.13)
include(FetchContent)

set(LIBRARY_NAME LQRSolver)

add_library(${LIBRARY_NAME} STATIC LQRSolver.cpp)

# eigen
FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
set(EIGEN_BUILD_DOC OFF)
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
set( OFF)
FetchContent_MakeAvailable(Eigen)

# nlohmann json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.10.4
)
FetchContent_MakeAvailable(json)

# includeパスに追加
target_include_directories(${LIBRARY_NAME}
    PUBLIC  ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${json_SOURCE_DIR}/include
)

# ライブラリにリンク
target_link_libraries(${LIBRARY_NAME}
    PRIVATE Eigen3::Eigen
    PRIVATE nlohmann_json::nlohmann_json
)

# コンパイラ関連
target_compile_options(${LIBRARY_NAME} PUBLIC -O3 -march=native)