DIRS=beep_driver

all:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) || exit 1;)

load:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) load || exit 1;)

unload:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) unload || exit 1;)

clean:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) clean || exit 1;)

.PHONY: all load unload clean
