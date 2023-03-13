"""
################################################################################
#                                   LICENSE                                    #
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
#       Routines for computing Remez polynomials.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Arrays.
import numpy

# argrelextrema found here.
import scipy.signal

# Muli-precision math routines found here.
import mpmath

# Polynomial evaluation found here.
import poly

# Rational function evaluation found here.
import rat

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.prec = 224

# Computes the peaks of |yarr| and returns the xarr values.
def get_peaks(xarr, yarr):
    """
        Function:
            get_peaks
        Purpose:
            Given x-data xarr and y-data yarr, with len(xarr) = len(yarr),
            compute the points xarr[n] such that xarr[n] corresponds to a peak
            of the absolute value |yarr[n]|.
        Arguments:
            xarr (list or array):
                The points in the x-axis the data corresponds to.
            yarr (list or array):
                The y-data.
        Output:
            peaks (numpy.array):
                The x-values corresponding to the peaks of |yarr|.
    """

    # scipy has a built-in function that is easy to use.
    maxind = list(scipy.signal.argrelextrema(yarr, numpy.greater_equal)[0])

    # The first and last elements of the interval should be added. Check.
    if len(xarr) - 1 not in maxind:
        maxind.append(len(xarr)-1)

    if 0 not in maxind:
        maxind = [0] + maxind

    # Convert back to a numpy array to be returned.
    maxind = numpy.array(maxind)

    # Return the points corresponding to peaks as an array.
    return xarr[maxind]

# Resets the x and y samples to correspond to the new peak points.
def reset_samples(func, xarr, yarr):
    """
        Function:
            reset_samples
        Purpose:
            Resets x and y samples to corresponds to peaks in yarr as a function
            of xarr. That is, the peaks in |yarr| are found and the x-values are
            stored in x_vals. Then y_vals = func(x_vals) is computed.
        Arguments:
            func (function):
                The function being computed.
            xarr (list or array):
                The x-data.
            yarr (list or array):
                The y-data.
        Output:
            x_vals (list):
                The x-values of the peak points.
            y_vals (list):
                The function func evaluated at x_vals.
    """

    # Get the peaks of the error funcion |f(x) - P(x)|.
    maxarr = get_peaks(xarr, yarr)

    # Convert the points to mpmath objects.
    x_vals = [mpmath.mpf(k) for k in maxarr]

    # Evaluate the function at these new points and return.
    y_vals = [func(k) for k in x_vals]

    return x_vals, y_vals

# Given (x_vals, y_vals) data, inverts the Remez matrix and solves.
def perform_remez_exchange(x_vals, y_vals):
    """
        Function:
            perform_remez_exchange
        Purpose:
            Given data (x_vals, y_vals), inverts the Remez matrix and solves
            for the coefficients of the approximant Minimax polynomial.
        Arguments:
            x_vals (list or array):
                The x-value data.
            y_vals (list or array):
                The values func(x_vals) where func is the function being
                approximated by the Minimax polynomial.
        Outputs:
            coeffs (list):
                The coefficients of the approximate Minimax polynomial.
    """

    # The degree of the polynomial is given by the size of the input array.
    deg = len(x_vals) - 1

    # We'll compute the entries of the coefficient matrix term-by-term.
    coeff_matrix = []

    # Loop over the rows of the matrix.
    for row_ind in range(deg + 2):
        row = []

        # And loop over the columns of the matrix.
        for column_ind in range(deg + 2):

            # The last column is given by the error term E. The coefficients
            # simply osciallate, (-1)^k where k is the row index.
            if column_ind == deg + 1:
                row.append(mpmath.mpf((-1)**row_ind))

            # Otherwise the elements are given by powers of x.
            else:
                row.append(mpmath.mpf(x_vals[row_ind]**column_ind))

        # Add this row to the matrix.
        coeff_matrix.append(row)

    # Convert our list-of-lists to a matrix using mpmath.
    coeff_matrix = mpmath.matrix(coeff_matrix)

    # Convert the data vector, which is a list, to an actual vector.
    y_data = mpmath.matrix(y_vals)

    # Solve the equation using LU decomposition and return as a list.
    return list(mpmath.lu_solve(coeff_matrix, y_data))[0:deg + 1]

# Given (x_vals, y_vals) data, inverts the rational Remez matrix and solves.
def perform_rational_remez_exchange(x_vals, y_vals, num_deg, den_deg):
    """
        Function:
            perform_rational_remez_exchange
        Purpose:
            Given data (x_vals, y_vals), inverts the Remez coefficient matrix
            for the rational approximation P(x)/Q(x) by linearizing and
            iteratively imporiving the linear approximation for the error
            term.
        Arguments:
            x_vals (list or array):
                The x-value data.
            y_vals (list or array):
                The values func(x_vals) where func is the function being
                approximated by the Minimax rational function.
            num_deg (int):
                The degree of the numerator P(x).
            den_deg (int):
                The degree of the denominator Q(x).
        Outputs:
            coeffs (list):
                The coefficients of the approximate Minimax rational function.
    """

    # The degree of the polynomial is given by the size of the input array.
    deg = num_deg + den_deg

    # We'll compute the entries of the coefficient matrix term-by-term.
    coeff_matrix = []

    # The rational approximation does not yield a linear system of equations
    # for the coefficients. We linearize by using an initial guess of E = E0 = 0
    # and then iteratively improve this until the E value stablizes.
    error_guess = mpmath.mpf(0.0)

    # Variable for keeping track of the number of iterations performed.
    iters = 0

    # Iteratively improve the guess for E0.
    while iters < 100:
        coeff_matrix = []

        # Loop over the rows of the matrix.
        for row_ind in range(deg + 2):
            row = []

            # The first coefficients of the row come from the polynomial in the
            # numerator.
            for num_ind in range(num_deg + 1):
                row.append(x_vals[row_ind]**num_ind)

            # The next coefficient come from the polynomial in the denominator,
            # combined with the data y and the error guess E0.
            for den_ind in range(1, den_deg + 1):
                row.append((x_vals[row_ind]**den_ind) *
                           (((-1)**row_ind)*error_guess - y_vals[row_ind]))

            # The last column is the (-1)^k E term.
            row.append((-1)**row_ind)
            coeff_matrix.append(row)

        # We have n+2 equations with n+2 unknowns (the n+1 coefficients, and
        # the error estimate). Solve this using matrices.
        coeff_matrix = mpmath.matrix(coeff_matrix)

        # Convert the y data to a vector.
        y_vec = mpmath.matrix(y_vals)

        # Invert and solve using LU Decomposition.
        data = list(mpmath.lu_solve(coeff_matrix, y_vec))

        # Avoid division by zero.
        if data[-1] == 0:
            iters += 1
            continue

        # Compute the relative difference and check if it is small enough.
        rel_increment_diff = mpmath.fabs((error_guess - data[-1])/data[-1])

        # If the error has stabilized, we're done.
        if rel_increment_diff < mpmath.mpf(1.0E-6):
            return data

        # Update the error guess.
        error_guess = data[-1]
        iters += 1

# Computes the degree "deg" Remez MiniMax polynomial of "f" on [start, end]
def remez(func, deg, start, end):
    """
        Function:
            remez
        Purpose:
            Computes the Minimax polynomial of a function f on a given interval
            of a specified degree using the Remez exchange algorithm.
        Arguments:
            f (function):
                The function to be approximated.
            deg (int):
                The degree of the output Minimax polynomial.
            start (float):
                The left-most point of the interval f is approximated on.
            end (float):
                The right-most point of the interval f is approximated on.
        Output:
            coeffs (list):
                The coefficients of the Minimax polynomial in ascending order
                in terms of the degrees.
    """

    # Convert the inputs to mpmath objects if necessary.
    start = mpmath.mpf(start)
    end = mpmath.mpf(end)

    # Compute the distance between initial samples.
    dist = (end - start)/mpmath.mpf(deg + 1)

    # Sample the interval [start, end] with a sufficient number of points so
    # that the peaks can be easily calculated. Compute the corresponding
    # y-vals farr = func(xarr).
    xarr = numpy.arange(float(start), float(end), float(dist)*1.0E-3)
    farr = [func(k) for k in xarr]

    x_vals = [start + m*dist for m in range(deg + 2)]
    y_vals = [func(m) for m in x_vals]

    # Iteratively perform the Remez exchange algorithm until the error is good.
    while True:

        # Invert the coefficient matrix and solve for the polynomial.
        data = perform_remez_exchange(x_vals, y_vals)

        # Compute the error. If the bumps are the same magnitude, stop.
        yarr = numpy.abs(
            numpy.array(
                [
                    float(farr[k] - poly.poly_eval(data, xarr[k]))
                    for k in range(len(xarr))
                ]
            )
        )

        # Stop the computation if this is good enough.
        if input("Max Err = %.5e | Stop? (y/n): " % numpy.max(yarr)) == "y":
            return data

        # Reset the samples to the peaks and compute the function there.
        x_vals, y_vals = reset_samples(func, xarr, yarr)

# Computes the rational Minimax function using the Remez exchange.
def rat_remez(func, num_deg, den_deg, start, end):
    """
        Function:
            rat_remez
        Purpose:
            Computes the Minimax rational approximation of a function f on a
            given interval of a specified degree using the Remez algorithm.
        Arguments:
            f (function):
                The function to be approximated.
            deg (int):
                The degree of the output Minimax polynomial.
            start (float):
                The left-most point of the interval f is approximated on.
            end (float):
                The right-most point of the interval f is approximated on.
        Output:
            coeffs (list):
                The coefficients of the Minimax polynomial in ascending order
                in terms of the degrees.
    """

    # Convert the inputs to mpmath objects if necessary.
    start = mpmath.mpf(start)
    end = mpmath.mpf(end)

    # The "degree" of the approximation is the sum of the degrees.
    deg = num_deg + den_deg

    # Compute the distance between initial samples.
    dist = (end - start)/mpmath.mpf(deg + 1)

    # Sample the interval [start, end] with a sufficient number of points so
    # that the peaks can be easily calculated. Compute the corresponding
    # y-vals farr = func(xarr).
    xarr = numpy.arange(float(start), float(end), float(dist)*1.0E-3)
    farr = [func(k) for k in xarr]

    x_vals = [start + m*dist for m in range(deg + 2)]
    y_vals = [func(m) for m in x_vals]

    # Variable for keeping track of the number of iterations performed.
    iters = 0

    # The iteration stops when E_{n} and E_{n+1} are close. Keep track of both.
    previous_error = mpmath.mpf(0)

    # Iteratively apply the Remez exchange algorithm until the error is decent.
    while iters < 100:

        # Compute the coefficient of the approximate Minimax polynomial.
        data = perform_rational_remez_exchange(x_vals, y_vals, num_deg, den_deg)

        # Compute the error. If the bumps are the same magnitude, stop.
        num = data[0:num_deg + 1]
        den = [mpmath.mpf(1)] + data[num_deg + 1: deg + 1]

        # Check if we can stop.
        if previous_error != mpmath.mpf(0):
            rel_diff = mpmath.fabs((data[-1] - previous_error)/data[-1])
            if rel_diff < mpmath.mpf(1.0E-6):
                return num, den, data[-1]

        yarr = numpy.abs(
            numpy.array(
                [
                    float(farr[k] - rat.rat_eval(num, den, xarr[k]))
                    for k in range(len(xarr))
                ]
            )
        )

        # Reset the samples to the peaks and compute the function there.
        x_vals, y_vals = reset_samples(func, xarr, yarr)
        previous_error = data[-1]
        iters += 1

# Print the coefficients for the Remez polynomial.
def print_coeffs(coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Minimax polynomial in a manner that is
            easy to copy/paste into a C program using macros.
        Arguments:
            coeffs (list):
                The coefficients of the polynomial.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
        Output:
            None.
    """

    # Number of decimals to print.
    number_of_decimals = 50

    # Index corresponding to the given coefficient.
    current_ind = 0

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the Remez polynomial."
          "                                    */")

    # Loop through the coefficients.
    for x_val in coeffs:

        # Convert to mpmath objects if necessary.
        x_mpf = mpmath.mpf(x_val)

        # Convert the mpmath object to a string.
        x_string = mpmath.nstr(
            x_mpf, number_of_decimals, show_zero_exponent = True,
            strip_zeros = False, min_fixed = 0, max_fixed = 0
        ).replace("e", "E")

        # Pad a zero to the exponent if necessary.
        if not x_string[-2:].isnumeric():
            x_string = x_string[:-1] + "0" + x_string[-1:]

        # Add plus sign if the coefficient is positive.
        if x_mpf >= 0:
            print("#define A%02d (+%s%s)" % (current_ind, x_string, ext))
        else:
            print("#define A%02d (%s%s)" % (current_ind, x_string, ext))

        current_ind += 1

# Print the coefficients for the Remez rational approximation.
def print_rat_coeffs(num_coeffs, den_coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Minimax polynomial in a manner that is
            easy to copy/paste into a C program using macros.
        Arguments:
            num_coeffs (list):
                The coefficients of the numerator.
            den_coeffs (list):
                The coefficients of the denominator.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
        Output:
            None.
    """

    # Number of decimals to print.
    number_of_decimals = 50

    # Index corresponding to the given coefficient.
    current_ind = 0

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the numerator of the Remez rational "
          "approximation.       */")

    # Loop through the numerator coefficients.
    for x_val in num_coeffs:

        # Convert to mpmath objects if necessary.
        x_mpf = mpmath.mpf(x_val)

        # Convert the mpmath object to a string.
        x_string = mpmath.nstr(
            x_mpf, number_of_decimals, show_zero_exponent = True,
            strip_zeros = False, min_fixed = 0, max_fixed = 0
        ).replace("e", "E")

        # Pad a zero to the exponent if necessary.
        if not x_string[-2:].isnumeric():
            x_string = x_string[:-1] + "0" + x_string[-1:]

        # Add plus sign if the coefficient is positive.
        if x_mpf >= 0:
            print("#define P%02d (+%s%s)" % (current_ind, x_string, ext))
        else:
            print("#define P%02d (%s%s)" % (current_ind, x_string, ext))

        current_ind += 1

    print("\n/*  Coefficients for the denominator of the Remez rational "
          "approximation.     */")

    # Reset the index to zero for the denominator coefficients.
    current_ind = 0

    # Loop through the denominator coefficients.
    for x_val in den_coeffs:

        # Convert to mpmath objects if necessary.
        x_mpf = mpmath.mpf(x_val)

        # Convert the mpmath object to a string.
        x_string = mpmath.nstr(
            x_mpf, number_of_decimals, show_zero_exponent = True,
            strip_zeros = False, min_fixed = 0, max_fixed = 0
        ).replace("e", "E")

        # Pad a zero to the exponent if necessary.
        if not x_string[-2:].isnumeric():
            x_string = x_string[:-1] + "0" + x_string[-1:]

        # Add plus sign if the coefficient is positive.
        if x_mpf >= 0:
            print("#define Q%02d (+%s%s)" % (current_ind, x_string, ext))
        else:
            print("#define Q%02d (%s%s)" % (current_ind, x_string, ext))

        current_ind += 1
