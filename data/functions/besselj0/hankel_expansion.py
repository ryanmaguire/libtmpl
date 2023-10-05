

import tmpld

ONE_BY_ROOT_TWO = tmpld.mpmath.sqrt(0.5)
ROOT_TWO_BY_PI = tmpld.mpmath.sqrt(tmpld.mpmath.mpf(2.0) / tmpld.mpmath.pi())
ROOT_PI_BY_TWO = tmpld.mpmath.sqrt(tmpld.mpmath.pi() / tmpld.mpmath.mpf(2.0))

def pzero(x_in):
    x_val = tmpld.mpmath.mpf(x_in)

    sqrt_x = tmpld.mpmath.sqrt(x_val)

    cos_x = tmpld.mpmath.cos(x_val)
    sin_x = tmpld.mpmath.sin(x_val)

    cos_x_pi_4 = (sin_x + cos_x) * ONE_BY_ROOT_TWO
    sin_x_pi_4 = (sin_x - cos_x) * ONE_BY_ROOT_TWO

    j_x = tmpld.mpmath.besselj(0, x_val)
    y_x = tmpld.mpmath.bessely(0, x_val)

    scaled_j_x = ROOT_PI_BY_TWO * j_x * sqrt_x
    scaled_y_x = ROOT_PI_BY_TWO * y_x * sqrt_x

    return cos_x_pi_4*scaled_j_x + sin_x_pi_4*scaled_y_x

def qzero(x_in):
    x_val = tmpld.mpmath.mpf(x_in)

    sqrt_x = tmpld.mpmath.sqrt(x_val)

    cos_x = tmpld.mpmath.cos(x_val)
    sin_x = tmpld.mpmath.sin(x_val)

    cos_x_pi_4 = (sin_x + cos_x) * ONE_BY_ROOT_TWO
    sin_x_pi_4 = (sin_x - cos_x) * ONE_BY_ROOT_TWO

    j_x = tmpld.mpmath.besselj(0, x_val)
    y_x = tmpld.mpmath.bessely(0, x_val)

    scaled_j_x = ROOT_PI_BY_TWO * j_x * sqrt_x
    scaled_y_x = ROOT_PI_BY_TWO * y_x * sqrt_x

    return -sin_x_pi_4*scaled_j_x + cos_x_pi_4*scaled_y_x

def hankel(x_in):
    x_val = tmpld.mpmath.mpf(x_in)

    sqrt_x = tmpld.mpmath.sqrt(x_val)
    scale = ROOT_TWO_BY_PI / sqrt_x

    cos_x = tmpld.mpmath.cos(x_val)
    sin_x = tmpld.mpmath.sin(x_val)

    cos_x_pi_4 = (sin_x + cos_x) * ONE_BY_ROOT_TWO
    sin_x_pi_4 = (sin_x - cos_x) * ONE_BY_ROOT_TWO

    p_0 = pzero(x_val)
    q_0 = qzero(x_val)

    return scale * (cos_x_pi_4 * p_0 - sin_x_pi_4 * q_0)
