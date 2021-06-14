cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(iex_pcap)
set (CMAKE_CXX_STANDARD 11)

############################################################
### PcapPlusPlus

if(WIN32)
        SET(OS_CONFIG_COMMAND "configure-windows-mingw.bat")
endif()
IF(APPLE)
        SET(OS_CONFIG_COMMAND "configure-mac_os_x.sh")
endif()
IF(UNIX AND NOT APPLE)
        SET(OS_CONFIG_COMMAND "configure-linux.sh")
endif()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(project_pcapplusplus
        GIT_REPOSITORY "https://github.com/seladb/PcapPlusPlus"
        GIT_TAG "master"

        UPDATE_COMMAND ""
        PATCH_COMMAND ""

        SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/pcapplusplus"
        CONFIGURE_COMMAND ./${OS_CONFIG_COMMAND} --default

        BUILD_COMMAND make
        BUILD_IN_SOURCE 1

        INSTALL_COMMAND ""

        TEST_COMMAND ""
)

# Add the link and include directories from the external library.
link_directories("3rdparty/pcapplusplus/Dist")
include_directories("3rdparty/pcapplusplus/Dist/header")


############################################################
### IEX library
include_directories("include")

SET(EXT_LIBRARIES Packet++
                  Pcap++
                  Common++
                  pcap)

add_library(iex_pcap "src/iex_decoder.cpp" "src/iex_messages" "src/quotes_parser.cpp")

install(TARGETS iex_pcap DESTINATION ${CMAKE_SOURCE_DIR}/lib)
add_dependencies(iex_pcap project_pcapplusplus)

add_executable(parse_tops_quotes_to_csv "src/parse_tops_quotes_to_csv.cpp")
target_link_libraries(parse_tops_quotes_to_csv iex_pcap ${EXT_LIBRARIES})
install(TARGETS parse_tops_quotes_to_csv DESTINATION ${CMAKE_SOURCE_DIR}/bin)