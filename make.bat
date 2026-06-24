::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                  LICENSE                                   ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  This file is part of libtmpl.                                             ::
::                                                                            ::
::  libtmpl is free software: you can redistribute it and/or modify           ::
::  it under the terms of the GNU General Public License as published by      ::
::  the Free Software Foundation, either version 3 of the License, or         ::
::  (at your option) any later version.                                       ::
::                                                                            ::
::  libtmpl is distributed in the hope that it will be useful,                ::
::  but WITHOUT ANY WARRANTY; without even the implied warranty of            ::
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ::
::  GNU General Public License for more details.                              ::
::                                                                            ::
::  You should have received a copy of the GNU General Public License         ::
::  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  Author:     Ryan Maguire                                                  ::
::  Date:       January 4, 2022                                               ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: Disable printing out the lines being executed.
@echo off

:: Prevent C flags from leaking into the caller's shell and make sure
:: command extensions are available.
SETLOCAL EnableExtensions

:: Clean up files produces by a previous build.
DEL /q *.exe *.obj *.o *.lib *.a *.dll 2>nul

:: Select the compiler. No argument defaults to MSVC.
SET "COMPILER=%~1"
IF "%COMPILER%"=="" SET "COMPILER=cl"

IF /I "%COMPILER%"=="cl" GOTO SetCL
IF /I "%COMPILER%"=="clang-cl" GOTO SetClangCL
IF /I "%COMPILER%"=="clang" GOTO SetClang
IF /I "%COMPILER%"=="gcc" GOTO SetGCC

:: Invalid compiler provided, jump to the usage statement.
GOTO Usage

::  Build settings:
::      CC:
::          The chosen compiler.
::      CONF:
::          The build settings used when compiling config.c.
::      CWARN:
::          Warning flags for the C compiler.
::      CFLAGS:
::          Flags (optimization, LTO, etc.) for the C compiler.
::      EXEOUT:
::          Flag that names the config executable.
::      ARCHIVER:
::          "lib" for MSVC, "ar" for GCC and Clang.
::      LIBOUT:
::           The name of the output static library.
:SetCL
    SET "CC=cl"
    SET "CONF=/DTMPL_SET_USE_MATH_TRUE"
    SET "CWARN=/W4"
    SET "CFLAGS=/nologo /I../ /O2 /GL /c"
    SET "EXEOUT=/Fe"
    SET "ARCHIVER=lib"
    SET "LIBOUT=libtmpl.lib"
    GOTO Build

:SetClangCL
    SET "CC=clang-cl"
    SET "CONF=/DTMPL_SET_USE_MATH_TRUE"
    SET "CWARN=-Weverything -Wno-padded -Wno-float-equal"
    SET "CFLAGS=/nologo /I../ /O2 /GL /c"
    SET "EXEOUT=/Fe"
    SET "ARCHIVER=lib"
    SET "LIBOUT=libtmpl.lib"
    GOTO Build

:SetClang
    SET "CC=clang"
    SET "CONF=-DTMPL_SET_USE_MATH_TRUE"
    SET "CWARN=-Weverything -Wno-padded -Wno-float-equal"
    SET "CFLAGS=-O3 -flto -I../ -c"
    SET "EXEOUT=-o "
    SET "ARCHIVER=ar"
    SET "LIBOUT=libtmpl.a"
    GOTO Build

:SetGCC
    SET "CC=gcc"
    SET "CONF=-DTMPL_SET_USE_MATH_TRUE"
    SET "CWARN=-Wall -Wextra -Wpedantic -Wno-padded -Wno-float-equal"
    SET "CFLAGS=-O3 -flto -I../ -c"
    SET "EXEOUT=-o "
    SET "ARCHIVER=ar"
    SET "LIBOUT=libtmpl.a"
    GOTO Build

:Build
    ECHO Building libtmpl with %CC%...

    :: Compile and execute the config.c file to probe the architecture.
    ECHO Configuring...
    %CC% %CONF% %EXEOUT%config.exe config.c
    IF errorlevel 1 GOTO ConfigError
    config.exe

    :: Check if an error occurred, then clean up the files.
    IF errorlevel 1 GOTO ConfigError
    DEL /q config.exe config.obj config.o 2>nul

    :: Compile every .c in the src directory, one subdirectory at a time,
    :: stopping on the first failure.
    FOR /D %%d in (src\*) DO (
        CALL :CompileDir "%%d"
        IF errorlevel 1 GOTO CompileError
    )

    :: Archive the objects into the static library.
    ECHO Creating %LIBOUT%...
    CALL :Archive
    IF errorlevel 1 GOTO LinkError

    :: Remove intermediates; keep the finished library.
    DEL /q *.exe *.obj *.o 2>nul
    GOTO Done

:: Compile every C file in a given subdirectory.
:CompileDir
    :: The batch script does not handle assembly code.
    :: If you wish to use assembly on Windows, build libtmpl using CMake.
    IF /I "%~nx1"=="assembly" (
        ECHO Skipping %~1\
        EXIT /b 0
    )

    ECHO Compiling %~1:

    :: Compile each .c file.
    FOR %%i in (%~1\*.c) DO (
        ECHO     %%i
        %CC% %CWARN% %CFLAGS% %%i

        :: Check for compiler errors, abort if there are any.
        IF errorlevel 1 EXIT /b 1
    )

    EXIT /b 0

:: Bundle the compiled objects into the static library.
:Archive

    :: MSVC and ClangCL use Microsoft's lib.exe tool.
    IF "%ARCHIVER%"=="lib" (
        lib /nologo /out:%LIBOUT% *.obj
        exit /b
    )

    :: GCC and regular Clang use ar. Create a list of object files.
    IF EXIST obj_list.tmp DEL /q obj_list.tmp
    FOR %%o in (*.o) DO ECHO %%o>>obj_list.tmp

    :: Create the static library from this list.
    ar rcs %LIBOUT% @obj_list.tmp

    :: Check for errors.
    IF errorlevel 1 (DEL /q obj_list.tmp 2>nul & EXIT /b 1)

    :: Clean up.
    DEL /q obj_list.tmp 2>nul
    EXIT /b 0

::  Error message if the user provides an unsupported compiler.
:Usage
    ECHO Unknown compiler "%COMPILER%".
    ECHO Usage: make.bat [cl ^| clang-cl ^| clang ^| gcc]
    ECHO No argument defaults to cl.
    GOTO Fail

:ConfigError
    ECHO ERROR: Failed to compile and execute config.c.
    GOTO Fail

:CompileError
    ECHO ERROR: a source file failed to compile. See the messages above.
    GOTO Fail

:LinkError
    ECHO ERROR: Failed to create %LIBOUT%.
    GOTO Fail

:Fail
    DEL /q *.exe *.obj *.o 2>nul
    ENDLOCAL
    EXIT /b 1

:Done
    ENDLOCAL
    EXIT /b 0