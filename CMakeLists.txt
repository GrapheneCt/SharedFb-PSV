cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_C_COMPILER "arm-vita-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-vita-eabi-g++")

project(SharedFb-sample)
add_subdirectory(gxminternalforvsh)

set(CMAKE_C_FLAGS "-Wl,-q -O3 -std=c99")

add_executable(${PROJECT_NAME}.elf
	src/main.c
	src/graphics.c
)

target_link_libraries(${PROJECT_NAME}.elf
	SceDisplay_stub 
	SceAppMgr_stub 
	SceGxm_stub 
	SceGxm_stub_weak
)

add_custom_target(${PROJECT_NAME}.vpk ALL
	COMMAND vita-elf-create ${PROJECT_NAME}.elf ${PROJECT_NAME}.velf
	COMMAND vita-make-fself ${PROJECT_NAME}.velf eboot.bin
	COMMAND vita-mksfoex -s TITLE_ID=SHAREDFBT "${PROJECT_NAME}" param.sfo
	COMMAND vita-pack-vpk -s param.sfo -b eboot.bin ${PROJECT_NAME}.vpk
)
add_dependencies(${PROJECT_NAME}.vpk ${PROJECT_NAME}.elf)
