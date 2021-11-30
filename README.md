# pystanpy

PyStanPy lets you define your model in Python with whatever
technique you like for computing lp and its gradient.

## Why

Iterating on models is easier when you don't need to wait. Or,
you've got a model accessible in Python already. Etc etc.

## Details

This works by building a CmdStan model with a user defined
function which invokes a Python callable `lp` and `glp`
in the `model` module (however determined by `sys.path`
or `$PYTHONPATH`), as for example in this repo, where the
model, 

``` python
from autograd import grad, numpy as np

def lp(x):
    err = np.r_[:x.size] - x
    err = err * 5
    return np.sum(-err**2)

glp = grad(lp)
```
and the `cmdstanpy` invocation,

``` python
if __name__ == '__main__':
    from cmdstanpy import CmdStanModel
    model = CmdStanModel(exe_file='main')
    fit = model.sample(data={'n': 5}, chains=1, iter_sampling=200, iter_warmup=200)
    draws = fit.draws()
    print('draws.shape', draws.shape)
    print('inferred shifts (should be r_[:5])',
          np.round(draws.mean(axis=0)[0][-5:]))
```
are in the same file for convenience.  When run, we get
the expected result,
``` sh
~/src/pystanpy> PYTHONPATH=$PWD python3 model.py
INFO:cmdstanpy:start chain 1
INFO:cmdstanpy:finish chain 1
draws.shape (200, 1, 12)
inferred shifts (should be r_[:5]) [-0.  1.  2.  3.  4.]
deleting tmpfiles dir: /tmp/tmpm18b7spd
done
```
which ensures the Stan/Python interop works correctly,
so any algorithm in CmdStan exposed via CmdStanPy
will work as well.

## How slow?

For 5 parameters, the Python-calling model reports 
~280us for a gradient evaluation, while a pure Stan model 
(`compare.stan`)
computing the same thing reports ~4us.  This is expected
since Stan compiles to plain C++, so the overhead is
significant but constant: 
if we bump up the number of parameters from 5
to 5000, they take ~570 us and 420 us respectively.

## TODO

- [ ] improve c++ wrapper
  - [ ] intialize stuff once
  - [ ] use faster calls via C-API
  - [ ] maybe write it with Cython for error handling
- [ ] use `autograd.value_and_grad` w/ single C call
- [ ] clean up code w/ better names
- [ ] add layer over cmdstanpy to ease use
- [ ] CI build exes for matrix of cmdstan, python & platforms
- [ ] build wheels packing exes
- [ ] extend for Julia [https://docs.julialang.org/en/v1/manual/embedding/](API)?
