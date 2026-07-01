cmake_minimum_required(VERSION 4.3)
project(MXBanking VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The RE golden flags (Disable security, keep debug symbols)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-stack-protector")

# List ALL your .cpp files here
add_executable(mxbanking 
    main.cpp
    Account.cpp
    AccountDatabase.cpp
    App.cpp
    Utils.cpp
)

# Windows specific: Link against necessary libs
if(WIN32)
    target_link_libraries(mxbanking ws2_32)
endif()