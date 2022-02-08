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

:: Delete old files.
del *.exe *.obj *.o *.so *.dll *.lib

IF %1.==. SET CC=cl
IF %1 == cl SET CC=cl
IF %1 == clang SET CC=clang-cl
IF %1 == clang-cl SET CC=clang-cl

IF %CC% == "clang-cl" (
    :: Delete old files.
    del *.exe *.obj *.o *.so *.dll *.lib

    :: Create include\tmpl_endianness.h
    clang-cl det_end.c -o det.exe
    det.exe
    del *.exe *.obj

    :: Compile the library.
    for /D %%d in (.\src\*) do ^
        clang-cl -O2 -Weverything -Wno-padded -Wno-float-equal -I..\ -c %%d\*.c

    :: Link everything into a .lib file.
    lib /out:libtmpl.lib *.obj

    :: Clean up.
    del *.exe *.obj
) ELSE (
    :: Create include\tmpl_endianness.h
    cl det_end.c /link /out:det.exe
    det.exe
    del *.exe *.obj

    :: Compile the library.
    for /D %%d in (.\src\*) do cl /I../ /W4 /O2 /c %%d\*.c

    :: Link everything into a .lib file.
    lib /out:libtmpl.lib *.obj

    :: Clean up.
    del *.exe *.obj
)

