cmake_minimum_required(VERSION 3.10) #������ cmake

project(c_pq)  #�������� �������

add_subdirectory("C:/Dock/PSQ 001/c_pq/libpqxx-7.8.1" libc_pq) 
#�������� ���������� � ������� � libc_pq \ �������� �� /
add_executable(c_pq main.cpp)  #������
target_compile_features(c_pq PRIVATE cxx_std_17) # �������� 17 ��� �++
target_link_libraries(c_pq pqxx) #�������