cmake_minimum_required(VERSION 3.10) #версия cmake

project(c_pq)  #название проекта

add_subdirectory("C:/Dock/PSQ 001/c_pq/libpqxx-7.8.1" libc_pq) 
#добавляю библиотеку и называю её libc_pq \ заменяем на /
add_executable(c_pq main.cpp)  #ресуры
target_compile_features(c_pq PRIVATE cxx_std_17) # стандарт 17 для с++
target_link_libraries(c_pq pqxx) #линкуем