from cmdstanpy import CmdStanModel
from autograd import grad, numpy as np


def lp(x):
    lp.calls += 1
    if lp.calls % 1024 == 0:
        print('lp.calls', lp.calls)
    err = np.r_[:x.size] - x
    return np.sum(-err**2)
lp.calls = 0

glp = grad(lp)

if __name__ == '__main__':
    model = CmdStanModel(exe_file='main')
    fit = model.sample(data={'n': 5}, chains=1, iter_sampling=2, iter_warmup=2)
    print(fit.draws().mean(axis=0)[0][-10:])
    import time; time.sleep(600)
