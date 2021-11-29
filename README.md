# pystanpy

PyStanPy lets you define your model in Python with whatever
technique you like for computing lp and its gradient.

This works by building a CmdStan model with a user defined
function which invokes a Python callable `lp` and `glp`
in the `model` module (however determined by `sys.path`
or `$PYTHONPATH`), e.g.

``` sh
PYTHONPATH=$PWD python3 model.py
```

which for convenience, places the `cmdstanpy` driver code
and the model in the same file. 

Currently, the gradients don't seem to be making it back
to Stan properly.
