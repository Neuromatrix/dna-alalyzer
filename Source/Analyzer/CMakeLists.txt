add_library(Server.Analyzer
	Source/Analyzer.cpp
)
target_include_directories(Server.Analyzer
PUBLIC
    Include/
    Source/
)
