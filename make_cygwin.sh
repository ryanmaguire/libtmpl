rm -f *.so *.o *.dll *.exe
clang ./det_end.c -o det.exe
./det.exe
rm -f det.exe
for dir in ./src/*; do
    for filename in $dir/*.c; do
        clang -Weverything -std=c89 -O3 -flto -I../ -c $filename
    done
done
clang ./*.o -O3 -I../ -flto -shared -libtmpl.dll -lm
rm -f *.o
