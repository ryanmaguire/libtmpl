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
IF %1 == cl (
    :: Compiler being used.
    SET CC=cl

    :: Arguments for the compiler.
    SET CMACR=/DTMPL_SET_USE_MATH_TRUE
    SET CWARN=/W4
    SET CARGS= /I../ /O2 /c

    :: Out command for compiler.
    SET OUT=/out:
) ELSE (
    IF %1 == clang-cl (
        :: Compiler being used.
        SET CC=clang-cl

        :: Arguments for the compiler.
        SET CMACR=-DTMPL_SET_USE_MATH_TRUE
        SET CWARN=-Weverything -Wno-padded -Wno-float-equal -Wno-reserved-id-macro
        SET CARGS=-O2 -I..\ -c

        :: Out command for compiler.
        SET OUT=-o
    ) ELSE (
        IF %1 == clang (
            :: Compiler being used.
            SET CC=clang-cl

            :: Arguments for the compiler.
            SET CMACR=-DTMPL_SET_USE_MATH_TRUE
            SET CWARN=-Weverything -Wno-padded -Wno-float-equal -Wno-reserved-id-macro
            SET CARGS=-O2 -I..\ -c

            :: Out command for compiler.
            SET OUT=-o
        ) ELSE (
            :: Compiler being used.
            SET CC=cl

            :: Arguments for the compiler.
            SET CMACR=/DTMPL_SET_USE_MATH_TRUE
            SET CWARN=/W4
            SET CARGS= /I../ /O2 /c

            :: Out command for compiler.
            SET OUT=/out:
        )
    )
)

:: Create include\tmpl_endianness.h
%CC% %CMACR% config.c %OUT%config.exe
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
            %CC% %CWARN% %CARGS% %%d\*.c
        )
    )
)


:: Link everything into a .lib file.
lib /out:libtmpl.lib *.obj

:: Clean up.
del *.exe *.obj
