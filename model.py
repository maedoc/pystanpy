from cmdstanpy import CmdStanModel
from autograd import grad, numpy as np


calls = [0]

def lp(x):
    calls[0] += 1
    if calls[0] % 1000 == 0:
        print("calls = ", calls[0])
    return np.sum(-x**2)

glp = grad(lp)

model = CmdStanModel(exe_file='main')
fit = model.sample(data={'n': 100}, chains=1, iter_sampling=100, iter_warmup=50)
print(fit)
