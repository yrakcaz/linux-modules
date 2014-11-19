DIRS=beep_driver

all:
	$(foreach var, $(DIRS), $(MAKE) -C $(var);)

load:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) load;)

unload:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) unload;)

clean:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) clean;)

distclean: clean unload
