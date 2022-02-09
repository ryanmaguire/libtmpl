"""
################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

# Numpy is needed for it's GCD function.
import numpy

# Needed to convert string to list of lists.
import ast

# Largest number of twists we'll check for torus knots.
torus_start = 2
torus_end = 20
torus_count = 0

R.<q> = LaurentPolynomialRing(QQ)
KnotList = []
PolyList = []
TorusStringList = []

# Open the file containing the PD data.
fp = open("pd_code_0_12.txt")

for m in range(torus_start, torus_end):

    if (m == 0) or (m == 1) or (m == -1):
        continue

    for n in range(m+1, torus_end):

        if (n == 0) or (n == 1) or (n == -1):
            continue

        if (numpy.gcd(m, n) != 1):
            continue

        L = snappy.Link("T(%d,%d)" % (m, n))
        f = L.alexander_polynomial()

        KnotList.append(L)
        PolyList.append(f)
        TorusStringList.append("(%d, %d)" % (m, n))
        torus_count += 1

for pd in fp:
    x = ast.literal_eval(pd)
    L = snappy.Link(x)
    f = L.alexander_polynomial()

    for n in range(torus_count):
        if PolyList[n] == f:
            if L.knot_floer_homology() == KnotList[n].knot_floer_homology():
                print("Match: %s" % TorusStringList[n],
                      "Crossing Number: %d" % len(x),
                      "PD Code %s" % pd)

