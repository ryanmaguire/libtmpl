import snappy
import numpy

# Largest number of twists we'll check for torus knots.
torus_start = 2
torus_end   = 400
torus_count = 0

# Generate the ring of Laurent polynomials in variable over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Create two empty lists for storing the knots and their Jones' polynomials.
KnotList = []
MirrorList = []
TorusStringList = []

for m in range(torus_start, torus_end):

    # There are no torus knots with m or n equal to 0. The torus knots with
    # m or n equal +/- 1 are actually trivial knots, so skip.
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

        f = q**((m-1)*(n-1)//2)*(1-q**(m+1)-q**(n+1)+q**(m+n)) / (1-q**2)
        g = q**((1-m)*(n-1)//2)*(1-q**(-m-1)-q**(-n-1)+q**(-m-n))/(1-q**(-2))

        # Add the two knots to our lists.
        KnotList.append(f)
        MirrorList.append(g)
        TorusStringList.append("(%d, %d)" % (m, n))
        torus_count += 1

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

    for n in range(torus_count):
        tstring = TorusStringList[n]
        if (f == KnotList[n]):
            print("\t%s matches a torus knot: %s" % (knot_string, tstring))
        elif (f == MirrorList[n]):
            print("\t%s matches a torus knot mirror: %s"%(knot_string, tstring))
        else:
            pass

print("\nProcessing Hoste-Thistlethwaite Alternating Table:")
for m in range(367):
    knot_struct = Ka[m]
    f = knot_struct[1].jones_polynomial()
    knot_string = knot_struct[0]

    for n in range(torus_count):
        tstring = TorusStringList[n]
        if (f == KnotList[n]):
            print("\t%s matches a torus knot: %s" % (knot_string, tstring))
        elif (f == MirrorList[n]):
            print("\t%s matches a torus knot mirror: %s"%(knot_string,tstring))
        else:
            pass

print("\nProcessing Hoste-Thistlethwaite Non-Alternating Table:")
for m in range(185):
    knot_struct = Kn[m]
    f = knot_struct[1].jones_polynomial()
    knot_string = knot_struct[0]

    for n in range(torus_count):
        tstring = TorusStringList[n]
        if (f == KnotList[n]):
            print("\t%s matches a torus knot: %s" % (knot_string, t_string))
        elif (f == MirrorList[n]):
            print("\t%s matches a torus knot mirror: %s"%(knot_string,t_string))
        else:
            pass
