cmake_minimum_required(VERSION 3.16)
project(libnpcjni VERSION 1.0.0
    DESCRIPTION "JNI bridge for libnpc"
    LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Find JNI ───────────────────────────────────────────────────
find_package(JNI REQUIRED)

# On macOS, include the darwin-specific JNI headers
if(APPLE)
    find_path(JNI_DARWIN_INCLUDE jni_md.h
        HINTS ${JAVA_INCLUDE_PATH}
              ${JAVA_INCLUDE_PATH}/darwin
              /Library/Java/JavaVirtualMachines/*/Contents/Home/include/darwin)
    if(JNI_DARWIN_INCLUDE)
        include_directories(${JNI_DARWIN_INCLUDE})
    endif()
endif()

include_directories(${JNI_INCLUDE_DIRS})

# ── Locate libnpc (pre-built) ──────────────────────────────────
# Set LIBNPC_ROOT to point to the libnpc source directory
if(NOT LIBNPC_ROOT)
    set(LIBNPC_ROOT "${CMAKE_SOURCE_DIR}/../numpy")
endif()

find_library(LIBNPC_LIBRARY NAMES npc libnpc
    HINTS ${LIBNPC_ROOT}/lib
    NO_DEFAULT_PATH)

if(NOT LIBNPC_LIBRARY)
    message(FATAL_ERROR "libnpc not found. Build it first: cd ${LIBNPC_ROOT} && make lib")
endif()

find_path(LIBNPC_INCLUDE_DIR array.h
    HINTS ${LIBNPC_ROOT}/include
    NO_DEFAULT_PATH)

if(NOT LIBNPC_INCLUDE_DIR)
    message(FATAL_ERROR "libnpc headers not found at ${LIBNPC_ROOT}/include")
endif()

message(STATUS "Using libnpc: ${LIBNPC_LIBRARY}")
message(STATUS "Using libnpc headers: ${LIBNPC_INCLUDE_DIR}")

# ── Locate libnpcpp headers (header-only) ──────────────────────
if(NOT LIBNPCPP_ROOT)
    set(LIBNPCPP_ROOT "${CMAKE_SOURCE_DIR}/../npc++")
endif()

find_path(LIBNPCPP_INCLUDE_DIR npc/npc.hpp
    HINTS ${LIBNPCPP_ROOT}/include
    NO_DEFAULT_PATH)

if(NOT LIBNPCPP_INCLUDE_DIR)
    message(FATAL_ERROR "libnpcpp headers not found. Set -DLIBNPCPP_ROOT=/path/to/npc++")
endif()

message(STATUS "Using libnpcpp headers: ${LIBNPCPP_INCLUDE_DIR}")

# ── Find libzip (optional, for NPZ I/O) ────────────────────────
find_library(LIBZIP_LIBRARY NAMES zip libzip
    HINTS /opt/homebrew/lib /usr/local/lib)
find_path(LIBZIP_INCLUDE_DIR zip.h
    HINTS /opt/homebrew/include /usr/local/include)

if(LIBZIP_LIBRARY AND LIBZIP_INCLUDE_DIR)
    message(STATUS "Found libzip: ${LIBZIP_LIBRARY}")
    set(NPC_HAS_LIBZIP 1)
else()
    message(STATUS "libzip not found — NPZ I/O disabled")
    set(NPC_HAS_LIBZIP 0)
endif()

# ── JNI shared library ─────────────────────────────────────────
file(GLOB JNI_SOURCES native/src/*.cpp)

add_library(npcjni SHARED ${JNI_SOURCES})

target_include_directories(npcjni PRIVATE
    ${CMAKE_SOURCE_DIR}/native/src
    ${LIBNPC_INCLUDE_DIR}
    ${LIBNPCPP_INCLUDE_DIR}
)

if(NPC_HAS_LIBZIP)
    target_include_directories(npcjni PRIVATE ${LIBZIP_INCLUDE_DIR})
endif()

target_compile_definitions(npcjni PRIVATE
    NPC_HAS_LIBZIP=${NPC_HAS_LIBZIP}
)

target_link_libraries(npcjni PRIVATE
    ${LIBNPC_LIBRARY}
    ${CMAKE_DL_LIBS}
    m
)

if(NPC_HAS_LIBZIP)
    target_link_libraries(npcjni PRIVATE ${LIBZIP_LIBRARY})
endif()

# Platform-specific settings
if(APPLE)
    set_target_properties(npcjni PROPERTIES
        SUFFIX ".dylib"
        INSTALL_RPATH "@loader_path"
        LINK_FLAGS "-undefined dynamic_lookup")
    target_link_options(npcjni PRIVATE -undefined dynamic_lookup)
else()
    set_target_properties(npcjni PROPERTIES
        SUFFIX ".so"
        INSTALL_RPATH "$ORIGIN")
endif()

# ── Install ────────────────────────────────────────────────────
install(TARGETS npcjni DESTINATION lib)
