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
#   Purpose:                                                                   #
#       Test a conjecture about Khovanov homology and the Jones' polynomial.   #
#       The idea is that Khovanov homology can distinguish a Torus knot from   #
#       a non-torus knot. First, see if this is true of the Jones' polynomial. #
#       If we find a match, compute (currently by hand or lookup table) the    #
#       Khovanov homologies of the matching pair to see if they're the same.   #
#       This is the same as jones_polynomial_conjecture_snappy_2_9_001.sage,   #
#       except that the torus knot Jones' polynomials are computed via         #
#       a known formula, rather than using SnapPy to directly compute the      #
#       polynomial. This hugely saves on computation time.                     #
#                                                                              #
#       This code works with SnapPy versions less than 3.0. Snappy 3.0 and     #
#       higher changed how the Jones' polynomial function works.               #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 12, 2021.                                                     #
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
torus_end = 100
torus_count = 0

# Generate the ring of Laurent polynomials in variable over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Create two empty lists for storing the knots and their Jones' polynomials.
KnotList = []
MirrorList = []
TorusStringList = []

# Open the file containing the PD data.
fp = open("pd_code_0_12.txt")

# Loop over and compute the Jones' Polynomial of torus knots.
for m in range(torus_start, torus_end):

    # There are no torus knots with m or n equal to 0. The torus knots with
    # m or n equal +/- 1 are trivial knots, so skip.
    if (m == 0) or (m == 1) or (m == -1):
        continue

    # The torus knot T(m,n) and T(m,n) are the same. Because of this we can cut
    # the square lattice [-N, -N] x [N, N] in half and compute the upper
    # triangle. This saves us from redundant computations.
    for n in range(m+1, torus_end):

        # Same skip as before.
        if (n == 0) or (n == 1) or (n == -1):
            continue

        # We only perform the computation if p and q are coprime. Otherwise we
        # have a link, several intertwined knots.
        if (numpy.gcd(m, n) != 1):
            continue

        # Torus knots have a closed form Jones' polynomial. Use this.
        f = q**((m-1)*(n-1)//2)*(1-q**(m+1)-q**(n+1)+q**(m+n)) / (1-q**2)
        g = q**((1-m)*(n-1)//2)*(1-q**(-m-1)-q**(-n-1)+q**(-m-n))/(1-q**(-2))

        # Add the two knots to our lists.
        KnotList.append(f)
        MirrorList.append(g)
        TorusStringList.append("(%d, %d)" % (m, n))
        torus_count += 1

for pd in fp:
    x = ast.literal_eval(pd)
    L = snappy.Link(x)
    f = L.jones_polynomial(new_convention=False)

    for n in range(torus_count):
        if KnotList[n] == f or MirrorList[n] == f:
            print("Match: %s" % TorusStringList[n],
                  "Crossing Number: %d" % len(x),
                  "PD Code %s" % pd)

