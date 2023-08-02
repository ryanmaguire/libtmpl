for dir in ./*/; do
    chroot $dir bash chroot_unit_test.sh
    cp ${dir}/home/libtmpl/tests/tests_results/*.txt .
done

# This part is done in chroots.

# cd /home/libtmpl/

# make clean && make uninstall && make && make install
# cd tests/
# bash unit_tests.sh
# exit
