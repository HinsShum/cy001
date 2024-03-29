#!/bin/bash
# This script will use cmake to manage the project

function build()
{
    if [ "$board_name" == "posix" -o "$board_name" == "win32" ]; then
        cmake -B build -G "$build_tools"  -DBOARD_NAME=$board_name -DCMAKE_BUILD_TYPE=$build_type
    else
        cmake -B build -G "$build_tools" -DBOARD_NAME=$board_name -DCMAKE_TOOLCHAIN_FILE=boards/${board_name}/tools/${board_name}_toolchain.cmake -DCMAKE_BUILD_TYPE=$build_type
    fi
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

function generate_flash_jlink()
{
    os=`uname -s`
    if [ $( expr $os : 'Linux' ) -gt 0 ]; then
        jlink=JLinkExe
    else
        jlink=JLink
    fi
    rm build/download.* -f
    rm build/erase.* -f
    echo -e "si SWD\nspeed 12000\nr\nh\nloadbin build/${board_name}.bin,${load_start_address}\nr\nexit" > build/download.jlink
    echo "${jlink} -Device ${device} -If SWD -Speed 12000 -JTAGConf -1,-1 -autoconnect 1 -CommanderScript build/download.jlink" > build/download.sh
    echo -e "si SWD\nspeed 12000\nr\nh\nerase ${load_start_address} ${load_end_address}\nexit" > build/erase.jlink
    echo "${jlink} -Device ${device} -If SWD -Speed 12000 -JTAGConf -1,-1 -autoconnect 1 -CommanderScript build/erase.jlink" > build/erase.sh
}

function download_bin()
{
    cmd=`cat build/download.sh`
    echo $cmd | sh
}

function erase_bin()
{
    cmd=`cat build/erase.sh`
    echo $cmd | sh
}

function help_info()
{
    echo "This shell script help user to build the easy_bootloader project easily"
    echo "Usage:"
    echo "./build.sh -<B|b> --plat=<board name> [options]"
    echo ""
    echo "Board name: the support board must be documented in a file named support_board.cfg"
    echo "Options"
    echo "  -[C|c]             = compile the project after building"
    echo "  -[R|r]             = remove the building directory"
    echo "  -g=<build tools>   = select the build tools, the value can be either make of ninja, default is make"
    echo "  --debug            = select the debug level"
    echo "  --release          = select the debug level"
    echo "  --name=<program>   = specify the project name, default name is 'demo'"
    echo "  --download         = download firmware by jlink"
    echo "  --erase            = erase the chip flash by jlink"
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
download=0
erase=0
support_board=("posix:0:0:null" "win32:0:0:null" "cy001:0x08005000:0x08080000:STM32F103ZE")
find_board=0

while [ $# -gt 0 ]; do
    if [ $( expr $1 : '-[B|b]' ) -gt 0 ]; then
        build=1
    elif [ $( expr $1 : '-[C|c]' ) -gt 0 ]; then
        compile=1
    elif [ $( expr $1 : '-[R|r]' ) -gt 0 ]; then
        clear=1
    elif [ $( expr $1 : '--plat=[a-z|A-Z|0-9|_]\{1,\}' ) -gt 0 ]; then
        board_name=$( expr $1 : '--plat=\([a-z|A-Z|0-9|_]\{1,\}\)' )
    elif [ $( expr $1 : '--release' ) -gt 0 ]; then
        build_type=Release
    elif [ $( expr $1 : '--debug' ) -gt 0 ]; then
        build_type=Debug
    elif [ $( expr $1 : '--download' ) -gt 0 ]; then
        download=1
    elif [ $( expr $1 : '--erase' ) -gt 0 ]; then
        erase=1
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

if [ -n "$board_name" ]; then
    for loop in ${support_board[*]}
    do
        # split by '_'
        support=(${loop//:/ })
        if [ $( expr $board_name : ${support[0]} ) -gt 0 ]; then
            find_board=1
            load_start_address=${support[1]}
            load_end_address=${support[2]}
            device=${support[3]}
        fi
    done
    if [ $find_board -eq 0 ]; then
        echo "Please check the board name that you input, can not find the board name:${board_name}"
        exit
    fi
fi

if [ "$board_name" == "posix" -o "$board_name" == "win32" ]; then
    download=0
    erase=0
fi

if [ $build -gt 0 ]; then
    if [ -n "$board_name" ]; then
        build
        if [ "$board_name" != "posix" -a "$board_name" != "win32" ]; then
            generate_flash_jlink
        fi
    else
        echo "Please input the board name that you want to compile"
        exit 0
    fi
fi

if [ $compile -gt 0 ]; then
    compile
fi

if [ $download -gt 0 ]; then
    download_bin
fi

if [ $erase -gt 0 ]; then
    erase_bin
fi

exit 0
