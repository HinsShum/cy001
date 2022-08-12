#!/bin/bash
# This script will use cmake to manage the project

function build()
{
    cmake -B build -G "$build_tools"  -DBOARD_NAME=$board_name -DCMAKE_BUILD_TYPE=$build_type
}

function compile()
{
    cmake --build build
}

function clear_build()
{
    echo "clear build"
    rm build -rf
    rm *.elf* -rf
}

function help_info()
{
    echo "This shell script help user to build the easy_bootloader project easily"
    echo "Usage:"
    echo "./build.sh -<B|b> [options]"
    echo ""
    echo "Options"
    echo "  -[C|c]             = compile the project after building"
    echo "  -[R|r]             = remove the building directory"
    echo "  -g=<build tools>   = select the build tools, the value can be either make of ninja, default is make"
    echo "  --debug            = select the debug level"
    echo "  --release          = select the debug level"
    echo "  --name=<program>   = specify the project name, default name is 'demo'"
}

if [ $# -eq 0 ]; then
    echo "Please input the board name that you want to compile"
    exit 0
fi

build=0
compile=0
clear=0
build_type=Debug
build_tools="Ninja"

while [ $# -gt 0 ]; do
    if [ $( expr $1 : '-[B|b]' ) -gt 0 ]; then
        build=1
    elif [ $( expr $1 : '-[C|c]' ) -gt 0 ]; then
        compile=1
    elif [ $( expr $1 : '-[R|r]' ) -gt 0 ]; then
        clear=1
    elif [ $( expr $1 : '--release' ) -gt 0 ]; then
        build_type=Release
    elif [ $( expr $1 : '--debug' ) -gt 0 ]; then
        build_type=Debug
    elif [ $( expr $1 : '-[-help|h]' ) -gt 0 ]; then
        help_info
    elif [ $( expr $1 : '-g=make' ) -gt 0 ]; then
        build_tools="Unix Makefiles"
    elif [ $( expr $1 : '-g=ninja' ) -gt 0 ]; then
        build_tools="Ninja"
    fi
    shift
done

if [ $clear -gt 0 ]; then
    clear_build
fi

if [ $build -gt 0 ]; then
    build
fi

if [ $compile -gt 0 ]; then
    compile
fi

exit 0