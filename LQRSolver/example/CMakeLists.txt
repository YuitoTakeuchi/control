cmake_minimum_required(VERSION 3.13)
include(FetchContent)

add_executable(${PROJECT_NAME} main.cpp)

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

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${EIGEN3_INCLUDE_DIR}
    PUBLIC ${json_SOURCE_DIR}/include
)

# ライブラリにリンク
target_link_libraries(${PROJECT_NAME}
    PRIVATE LQRSolver

# external libs
    PUBLIC Eigen3::Eigen
    PUBLIC nlohmann_json::nlohmann_json
)


# コンパイラ関連
target_compile_options(${PROJECT_NAME} PUBLIC -O3 -march=native -DEIGEN_NO_DEBUG)