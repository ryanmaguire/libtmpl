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

# Largest number of twists we'll check for torus knots.
twist_start = 0
twist_end = 20
twist_count = 0

# Generate the ring of Laurent polynomials in variable over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Create two empty lists for storing the knots and their Jones' polynomials.
KnotList = []
MirrorList = []
TwistInd = []

# Loop over and compute the Jones' Polynomial of twist knots.
for m in range(twist_start, twist_end):

    # We only perform the computation if p and q are coprime. Otherwise we
    # have a link, several intertwined knots.
    if m % 2 == 0:
        f = (q**3 + q - q**(3-m) + q**(-m))/(1+q)
        g = (q**(-3) + q**(-1) - q**(m-3) + q**m)/(1+q**(-1))
    else:
        f = (1 + q**(-2) + q**(-m) - q**(-m-3))/(1+q)
        g = (1 + q**2 + q**(m) - q**(m+3))/(1+q**(-1))

    # Add the two knots to our lists.
    KnotList.append(f)
    MirrorList.append(g)
    TwistInd.append(m)
    twist_count += 1

# SnapPy has the Rolfsen table for many knots, the highest being 11 crossings.
# Loop between 3 (Trefoil) and 11.
print("\nProcessing Rolfsen Table:")
for k in range(3, 12):

    # Reset m to one.
    m = 1

    # If the knot k_n does not exist (for example, "3_5"), and we try to
    # create it, Python will produce an error, crashing the program.
    # Perform this loop in a try-except block to catch any exception raised
    # by the SnapPy module.
    try:
        while(1):
            knot_string = ("%d_%d" % (k, m))
            knot = snappy.Link(knot_string)
            f = knot.jones_polynomial()

            for n in range(twist_count):
                if (f == KnotList[n]):
                    print("\t%s matches a twist knot: %d"
                          % (knot_string, TwistInd[n]))
                elif (f == MirrorList[n]):
                    print("\t%s matches a torus knot mirror: %d"
                          % (knot_string, TwistInd[n]))
                else:
                    pass

            # Increment m.
            m += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except (IOError, ValueError):
        continue
