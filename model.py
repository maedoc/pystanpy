from cmdstanpy import CmdStanModel
from autograd import grad, numpy as np

def lp(x):
    err = np.r_[:x.size] - x
    err = err * 5
    return np.sum(-err**2)

glp = grad(lp)

if __name__ == '__main__':
    model = CmdStanModel(exe_file='main')
    fit = model.sample(data={'n': 5}, chains=1, iter_sampling=200, iter_warmup=200)
    draws = fit.draws()
    print('draws.shape', draws.shape)
    print('inferred shifts (should be r_[:5])',
          np.round(draws.mean(axis=0)[0][-5:]))
