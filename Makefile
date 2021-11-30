
cs = ~/.cmdstan/$(shell ls ~/.cmdstan)

PYVER := $(shell python3 -V | cut -f2 -d' ' | cut -f1,2 -d.)
CFLAGS := -g -I/usr/include/python$(PYVER) -I$(shell python3 -c 'import numpy; print(numpy.get_include())')
LDFLAGS := -lpython$(PYVER)

test: main
	PYTHONPATH=./ python3 model.py

main: main.hpp
	echo $(PYVER)
	echo $(CFLAGS)
	echo $(cs)
	make -C $(cs) CXXFLAGS_OPTIM="$(CFLAGS)" LDFLAGS_OS="$(LDFLAGS)" $$PWD/$@

# TODO it turns out just cat is not enough,
# func.hpp should be inserted right before the model class
# so we keep main.hpp in the repo until this is automated
# main.hpp: func.hpp userfunc.hpp
# 	cat $^ > $@

# userfunc.hpp: userfunc.stan
# 	$(cs)/bin/stanc --allow-undefined $< --o $@
