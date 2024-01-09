add_executable(App main.cpp)

target_link_libraries(App
    Server.Merger
    Server.Analyzer
)
