import numpy as np
import spam

EPSILON = 1e-8


def approx_equals(x: float, y: float) -> bool:
    return abs(x - y) < EPSILON


def test_logit():
    assert approx_equals(spam.logit(0.5), 0.0)


def test_logit_numpy():
    xs = np.array([0.5])
    f = np.frompyfunc(spam.logit, 1, 1)
    assert approx_equals(f(xs)[0], 0.0)


def test_add():
    assert approx_equals(spam.add(0.2, 0.3), 0.5)


def test_add_numpy():
    xs = np.array([0.2])
    ys = np.array([0.3])
    g = np.frompyfunc(spam.add, 2, 1)
    assert approx_equals(g(xs, ys)[0], 0.5)


def test_mystery():
    assert approx_equals(spam.mystery(0.3, 0.2, True), 0.5)
    assert approx_equals(spam.mystery(0.3, 0.2, False), 0.1)


def test_mystery_numpy():
    xs = np.array([0.3])
    ys = np.array([0.2])
    # Must use `int` instead of `bool` to avoid this warning:
    #   /Users/conor/ygg/spam/venv/lib/python3.12/site-packages/numpy/lib/function_base.py:2410: DeprecationWarning: In future, it will be an error for 'np.bool_' scalars to be interpreted as an index
    bs_true = np.array([True])
    bs_false = np.array([False])
    h = np.frompyfunc(spam.mystery, 3, 1)
    assert approx_equals(h(xs, ys, bs_true)[0], 0.5)
    assert approx_equals(h(xs, ys, bs_false)[0], 0.1)
