import pystan
import numpy as np


calls = [0]

def lp(x):
    calls[0] += 1
    if calls[0] % 100 == 0:
        print("calls = ", calls[0])
    out = x.sum()
    return (-x**2).sum()

def glp(x):
    calls[0] += 1
    return -2*x

model = pystan.StanModel(
    model_code=open('userfunc.stan').read(),
    allow_undefined=True,
    includes=["func.hpp"],
    include_dirs=[".", "/usr/include/python3.7m"],
    #verbose=True,
    )

chains = model.sampling(data={'n': 100})
print(chains)
