cmake_minimum_required(VERSION 4.0)
project(StaffManagementSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(StaffManagementSystem
        源文件/职工管理系统.cpp
        源文件/workerManager.cpp
        源文件/employee.cpp
        源文件/manager.cpp
        源文件/boss.cpp
)