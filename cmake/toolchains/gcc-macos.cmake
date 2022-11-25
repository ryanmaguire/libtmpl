include_guard()

# Find gcc as installed by Homebrew or Macports
find_program(
    GCC
    NAMES gcc gcc-9 gcc-10 gcc-11
    PATHS /usr/local/Cellar /usr/local/opt /opt/local/bin /usr/local/bin
)

if(GCC)
    set(CMAKE_C_COMPILER ${GCC})
else()
    message(
        FATAL_ERROR
        "gcc was not found. Please install it using Homebrew or Macports."
    )
endif()
