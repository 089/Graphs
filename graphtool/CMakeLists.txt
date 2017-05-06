add_library(graphtoolShared SHARED Graph.cpp Graph.h)

target_include_directories (graphtoolShared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})