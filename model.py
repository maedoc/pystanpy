import pystan
from autograd import grad, numpy as np


calls = [0]

def lp(x):
    calls[0] += 1
    if calls[0] % 1000 == 0:
        print("calls = ", calls[0])
    return np.sum(-x**2)

glp = grad(lp)

model = pystan.StanModel(
    model_code=open('userfunc.stan').read(),
    allow_undefined=True,
    includes=["func.hpp"],
    include_dirs=[".", "/usr/include/python3.7m"],
    #verbose=True,
    )

chains = model.sampling(data={'n': 100}, iter=10, warmup=5)
print(chains)
