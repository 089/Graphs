add_library(graphtoolShared SHARED Graph.cpp Graph.h)

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(BoostExec Graph.cpp)

if(Boost_FOUND)
    target_link_libraries(BoostExec ${Boost_LIBRARIES})
endif()

target_include_directories (graphtoolShared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
