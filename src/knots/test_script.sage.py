import snappy
import numpy

Torus_Start = 3
Torus_End   = 15

# The SnapPy module has 367 altnerating Hoste-Thistlethwaite knots
# and 185 non-alternating Hoste-Thistlethwaite knots. We can loop over these
# with strings.

# The syntax for manipulating strings in Sage comes from Python, which is
# borrowed from the syntax used in C. We use %d to indicate a placeholder for
# and integer, and then pass an integer to that placeholder via % n, where n is
# and actual integer. We surround the string with quotation marks.

# These are all of the alternating Hoste-Thistlethwaite knots available:
# Ka = [("K11a%d" % n) for n in range(1, 368)]

# And these are the non-alternating ones.
# Kn = [("K11n%d" % n) for n in range(1, 186)]

# As a side note, the range function (which is from Python) has syntanx
# range(m,n) and creates an iterator between m and n-1. That is, n is NOT
# included. Hence the need to iterate between 1 and 368 for the alternating and
# 1 and 186 for the non-alternating.

# We can use a try-except to store all of the knots in the Rolfsen table.
n = 1
ManifoldList = []

# Counters for seeing how many of the knots work with the SnapPy
# is_isometric_to method.
counter_gcd = 0
counter_success = 0

# SnapPy has the Rolfsen table for many knots, the highest being 11 crossings.
# Loop between 3 (Trefoil) and 11.
for k in range(3, 12):

    # If the knot k_n does not exist (for example, "3_5"), and we try to
    # create it, Python will produce an error, crashing the program.
    # Perform this loop in a try-except block to catch any exception raised
    # by the SnapPy module.
    try:
    	while(1):
            knot_string = ("%d_%d" % (k, n))

            # Create a copy of the manifold class and the link class
            # corresponding to the current knot.
            m = snappy.Manifold(knot_string)
            l = snappy.Link(knot_string)

            # Append the manifold and link to our list and increment n.
            ManifoldList.append([knot_string,m,l])
            n += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except IOError:

        # Reset n to 1 and continue the outer-most for-loop.
        n = 1
        continue

# We need to loop over all Torus knots within a certain range. A torus knot
# can be specified by an ordered pair (n, m) of COPRIME integers.
for n in range(Torus_Start, Torus_End):
    print("Current: %d  Total: %d" % (n, Torus_End))

    # If n is -1, 0, or 1, skip. There are no Torus knots with -1, 0, or 1 as
    # one of its entries, with the exception of the trivial knot, and we can
    # skip this one.
    if ((n == -1) or (n == 1) or (n == 0)):
        continue

    # The knot T(n,m) and T(m,n) are the same. The link T(m,m) is a collection
    # of m trivial knots. To avoid these we may start the second loop at
    # m = n+1.
    for m in range (n+1, Torus_End):

        # Similar to the outer loop, if m is -1, 0, or 1, skip.
        if ((m == -1) or (m == 1) or (m == 0)):
            continue

        # We only have a new torus knot is GCD(n,m) = 1. Check this.
        if (numpy.gcd(n, m) == 1):

            # Increment our counter that checks if is_isometric_to works.
            counter_gcd += 1

            # Compute the Link class corresponding to our torus knot.
            knot_string = "T(%d, %d)" % (n, m)
            torus_knot = snappy.Link(knot_string)

            # Loop over all of the knots in our list and check if they have the
            # same Jones Polynomial as the torus knot T(n,m).
            for k in ManifoldList:

                # Print out some information for status updates.
            	# print(k[0], knot_string)

                # Skip this for now, it does not work.
                # The is_isometric_to method failed for EVERY torus knot. The
                # documentation indicates this may happen for
                # "closed manifolds". We need to have this statement in a
                # try-except block since SnapPy produces a RunTime error if
                # SnapPea (the C code) is unable to determine if two manifolds
                # are isometric.
                """
            	try:
            	    if (k[1].is_isometric_to(torus_knot.exterior())):
            	        continue
            	except RuntimeError as err:
            	    print(err)
        	        continue
        	    """

                # If we get here (and the is_isometric_to block is NOT
                # commented out), then is_isometric_to succeeded and we should
                # increment our counter. If the is_isometric_to block is
                # commented out, we can just ignore this.
                counter_success += 1

                # Compute the Jones polynomial of the torus knot.
                torus_poly = torus_knot.jones_polynomial()

                # Shift the Jones polynomial so that all of the powers are
                # non-negative. That is, make the Jones polynomial an actual
                # polynomial, and not a Laurent polynomial with negative
                # exponents.
                torus_poly = torus_poly.shift(-min(torus_poly.exponents()))

                # Do the same thing for our current knot.
                knot_poly = k[2].jones_polynomial()
                knot_poly = knot_poly.shift(-min(knot_poly.exponents()))

                # Make the constant coefficient of our polynomials positive.
                if (knot_poly[0] < 0.0):
                    knot_poly = -knot_poly

                if (torus_poly[0] < 0.0):
                    torus_poly = -torus_poly

                # Compare the two polynomials.
            	if (torus_poly == knot_poly):
            	    print("\n\tMATCH: %s %s\n" % (k[0], knot_string))

# print(100.0*counter_success/counter_gcd)

