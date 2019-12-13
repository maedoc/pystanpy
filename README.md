# pystanpy

PyStanPy is an insidious attempt to define log-p and its gradient in
Python and use Stan's algorithms anyway. 

There's a memory leak, by the way.. missing a `Py_DECREF` or several..
