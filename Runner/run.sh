#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <option>"
    exit 1
fi

option="$1"

# Check if the option is valid
if [ "$option" != "-merge" ] && [ "$option" != "-analyze" ]; then
    echo "Invalid option. Use <-merge|-analyze>"
    exit 1
fi

# Run the C++ application
./../build/App/App "$option"
