cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

cmake_policy(SET CMP0123 NEW)

# 项目名称
set(PROJECT_NAME demo)

# 设定芯片类型
set(CMAKE_SYSTEM_PROCESSOR Cortex-M3)
set(CMAKE_SYSTEM_ARCH Cortex-M3)

# 设置语言标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# 设置编译器 C 的编译器
set(CMAKE_C_COMPILER armclang.exe)
set(CMAKE_C_COMPILER_WORKS TRUE)

# 设置编译器 C++ 的编译器
set(CMAKE_CXX_COMPILER armclang.exe)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

# 设置 ASM 的编译器（不设置配合 -masm=auto 使用）
set(CMAKE_ASM_COMPILER armclang.exe)

# 指明 ASM 编译器，配合 第二种 CMAKE_ASM_FLAGS_INIT 方式使用
#set(CMAKE_ASM_COMPILER armasm.exe)
#set(CMAKE_ASM_COMPILER_WORKS TRUE)

# 设置链接器
set(CMAKE_C_LINK_EXECUTABLE armlink.exe)
set(CMAKE_ASM_LINK_EXECUTABLE armlink.exe)
set(CMAKE_CXX_LINK_EXECUTABLE armlink.exe)

# 设置分散加载文件，由keil生成
set(SECTIONS_SCRIPT_PATH ${CMAKE_HOME_DIRECTORY}/air32.sct)

# 设置与芯片对应的 --target 编译选项
set(C_TARGET_FLAG --target=arm-arm-none-eabi)
set(ASM_TARGET_FLAG --target=arm-arm-none-eabi)

# 设置与芯片对应的 cpu 编译选项
set(LINKER_TARGET_FLAG --cpu=${CMAKE_SYSTEM_PROCESSOR})
set(COMPILE_RULE_FLAG "-mcpu=${CMAKE_SYSTEM_PROCESSOR}")

# 设置 C 编译器选项(这里就把MDK中的 C/C++ 分页里最下边一栏的属性贴进来)
# 参数 -w 表示忽略所有警告，不然要配具体忽略哪些警告，尽管贴过来也行，但是太乱
# 优化选项 -O 有 1~3   -Os 是平衡  -Oz 是最小体积
#set(CMAKE_C_FLAGS_INIT "${C_TARGET_FLAG} ${COMPILE_RULE_FLAG} \
#    -xc -std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar \
#    -gdwarf-4 -O0 -ffunction-sections")
set(CMAKE_C_FLAGS_INIT "${C_TARGET_FLAG} ${COMPILE_RULE_FLAG} \
    -xc -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -O0 -ffunction-sections")

# 设置 C++ 编译器选项(没有用到 c++ 所以不用配置)
#set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT})

# 设置ASM编译器选项
set(CMAKE_ASM_FLAGS_INIT "${ASM_TARGET_FLAG} ${COMPILE_RULE_FLAG} -masm=auto -gdwarf-4 ")

# 设置链接器选项
# 使用忽略所有警告的配置时没有 --map 及其之后的内容， 这里根据需要保留了一些信息，在 demo.map 中可以看到
set(CMAKE_EXE_LINKER_FLAGS_INIT  " \
            ${LINKER_TARGET_FLAG} \
            --library_type=microlib \
            --strict \
            --scatter ${SECTIONS_SCRIPT_PATH} \
            --info sizes --info totals --info unused --info veneers \
            --summary_stderr \
            --info summarysizes"
)

# 头文件搜索路径
include_directories(src/bsp src/Libraries/AIR32F10xLib/inc src/Libraries/CMSIS/Include
        D:/Keil_v5/Packs/Keil/AIR32F103_DFP/1.1.9/Device/Include
)

# 宏定义
add_definitions(-DAIR32F10X_MD -D__MICROLIB)

# 源文件
file(GLOB_RECURSE SOURCES src/bsp/*.* src/Libraries/AIR32F10xLib/*.*)
file(GLOB_RECURSE SOURCES ${SOURCES} src/Libraries/STARTUP/arm/startup_air32f10x.s)
#file(GLOB_RECURSE SOURCES ${SOURCES} src/Libraries/STARTUP/gcc/startup_air32f10x.s)

project(${PROJECT_NAME} C CXX ASM)

# 生成目标
add_executable(${PROJECT_NAME} ${SOURCES} ${LINKER_SCRIPT})

# 生成hex和bin文件
set(ARMCC_FROMELF fromelf.exe)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${ARMCC_FROMELF} --i32 --output=${HEX_FILE} ${ELF_FILE}
        COMMAND ${ARMCC_FROMELF} --bin --output=${BIN_FILE} ${ELF_FILE}
        #COMMENT "Building ${HEX_FILE} and ${BIN_FILE}"
)
