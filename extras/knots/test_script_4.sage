import snappy
import numpy

# Generate the ring of Laurent polynomials in variable over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Get the figure 8 knot's Jones polynomial.
figure_8_poly = snappy.Link("4_1").jones_polynomial()

# The SnapPy module has 367 altnerating Hoste-Thistlethwaite knots
# and 185 non-alternating Hoste-Thistlethwaite knots. We can loop over these
# with strings.

# The syntax for manipulating strings in Sage comes from Python, which is
# borrowed from the syntax used in C. We use %d to indicate a placeholder for
# and integer, and then pass an integer to that placeholder via % n, where n is
# and actual integer. We surround the string with quotation marks.

# These are all of the alternating Hoste-Thistlethwaite knots available:
Ka = []
for n in range(1, 368):
    knot_string = "K11a%d" % n
    knot = snappy.Link(knot_string)
    Ka.append([knot_string, knot])

# And these are the non-alternating ones.
Kn = []
for n in range(1, 186):
    knot_string = "K11n%d" % n
    knot = snappy.Link(knot_string)
    Kn.append([knot_string, knot])

# As a side note, the range function (which is from Python) has syntanx
# range(m,n) and creates an iterator between m and n-1. That is, n is NOT
# included. Hence the need to iterate between 1 and 368 for the alternating and
# 1 and 186 for the non-alternating.

# We can use a try-except to store all of the knots in the Rolfsen table.
n = 1
total_size = 0
ManifoldList = []

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
            total_size += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except IOError:

        # Reset n to 1 and continue the outer-most for-loop.
        n = 1
        continue

print("Processing Rolfsen Table:")
for m in range(total_size):
    knot_struct = ManifoldList[m]
    f = knot_struct[2].jones_polynomial()
    knot_string = knot_struct[0]

    if (f == figure_8_poly):
        print("\tMatch: %s" % knot_string)
    else:
        pass

print("\nProcessing Hoste-Thistlethwaite Alternating Table:")
for m in range(367):
    knot_struct = Ka[m]
    f = knot_struct[1].jones_polynomial()
    knot_string = knot_struct[0]

    if (f == figure_8_poly):
        print("\tMatch: %s" % knot_string)
    else:
        pass

print("\nProcessing Hoste-Thistlethwaite Non-Alternating Table:")
for m in range(185):
    knot_struct = Kn[m]
    f = knot_struct[1].jones_polynomial()
    knot_string = knot_struct[0]

    if (f == figure_8_poly):
        print("\tMatch: %s" % knot_string)
    else:
        pass
