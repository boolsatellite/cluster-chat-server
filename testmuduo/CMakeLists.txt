cmake_minimum_required(VERSION 3.22)
project(main)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
set(CMAKE_CXX_STANDARD 14)

# 配置头文件搜索路径
# include_directories()

# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST testmuduo.cpp)

# 把指定路径下所有源文件放在变量名SRC_LIST里面
# aux_source_directory(. SRC_LIST)

# 生成可执行文件，由STC_LIST编译而来
add_executable(testmuduo
        ${SRC_LIST})

# server这个目标程序需要链接的库文件
target_link_libraries(testmuduo muduo_net muduo_base pthread)
