


add_library(Library.Subscriber
	Client/Source/Client.cpp
)
target_include_directories(Library.Subscriber
PUBLIC
    Client/Include/
    Client/Source/
)
target_link_libraries(Library.Subscriber

)


add_library(Library.Publisher
    Server/Source/Server.cpp
)
target_include_directories(Library.Publisher
PUBLIC
    Server/Include/
    Server/Source/
)
target_link_libraries(Library.Publisher

)
