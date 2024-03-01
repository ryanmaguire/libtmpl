import tmpld
import tmpld.chebyshev
import tmpld.poly
import tmpld.pade
import tmpld.rat
import tmpld.remez

FOUR = tmpld.mpmath.mpf(4)
END = tmpld.mpmath.mpf(64)
NUMBER = tmpld.mpmath.mpf(128)
STEP = END / NUMBER

def forward(t_val):
    mpf_t = tmpld.mpmath.mpf(t_val)
    return FOUR / (FOUR + mpf_t)

def backward(t_val):
    mpf_t = tmpld.mpmath.mpf(t_val)
    return (FOUR - FOUR*mpf_t) / mpf_t

def erfcx(t_val):
    mpf_t = tmpld.mpmath.mpf(t_val)
    return tmpld.mpmath.exp(mpf_t*mpf_t) * tmpld.mpmath.erfc(mpf_t)

def cheb(t_val):
    return erfcx(backward(t_val))

def poly(coeffs, t_val):
    return tmpld.poly.poly_eval(coeffs, forward(t_val))

START = tmpld.mpmath.mpf(1)
LAST = forward(END)
INCREMENT = (START - LAST) / NUMBER
NEXT = START - INCREMENT

(P, Q, e) = tmpld.remez.rat_remez(cheb, 6, 0, NEXT, START)
