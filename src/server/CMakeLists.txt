
aux_source_directory(. SRC_LIST)

add_executable(ChatServer ${SRC_LIST})

target_link_libraries(ChatServer pthread muduo_net muduo_base)