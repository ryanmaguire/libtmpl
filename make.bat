::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                 LICENSE                                    ::
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

:: Delete old files.
IF EXIST *.exe (del *.exe)
IF EXIST *.obj (del *.obj)
IF EXIST *.o (del *.o)
IF EXIST *.lib (del *.lib)
IF EXIST *.so (del *.so)

:: See if the user specified which compiler to use.
IF %1.==. GOTO MakeCL
IF %1 == cl GOTO MakeCL
IF %1 == clang-cl GOTO MakeClang
IF %1 == clang GOTO MakeClang

:MakeClang

    :: Arguments for the compiler.
    SET CMACR=-DTMPL_SET_USE_MATH_TRUE
    SET CWARN=-Weverything -Wno-padded -Wno-float-equal -Wno-reserved-id-macro
    SET CARGS=-O2 -I..\ -c

    :: Create include\tmpl_endianness.h
    clang-cl %CMACR% config.c -o config.exe
    config.exe
    del *.exe *.obj

    :: Compile the library.
    for /D %%d in (.\src\*) do (
        if "%%d" == ".\src\assembly" (
            echo Skipping src\assembly\
        ) else (
            if "%%d" == ".\src\builtins" (
                echo Skipping src\builtins\
            ) else (
                clang-cl %CWARN% %CARGS% %%d\*.c
            )
        )
    )

    :: Go to the Linking stage.
    GOTO LinkLib

:MakeCL

    :: Arguments for the compiler.
    SET CMACR=/DTMPL_SET_USE_MATH_TRUE
    SET CWARN=/W4
    SET CARGS= /I../ /O2 /c

    :: Create include\tmpl_endianness.h
    cl %CMACR% config.c /link /out:config.exe
    config.exe
    del *.exe *.obj

    :: Compile the library.
    for /D %%d in (.\src\*) do (
        if "%%d" == ".\src\assembly" (
            echo Skipping src\assembly\
        ) else (
            if "%%d" == ".\src\builtins" (
                echo Skipping src\builtins\
            ) else (
                cl %CWARN% %CARGS% %%d\*.c
            )
        )
    )

    :: Go to the Linking stage.
    GOTO LinkLib

:LinkLib

    :: Link everything into a .lib file.
    lib /out:libtmpl.lib *.obj

    :: Clean up.
    del *.exe *.obj

