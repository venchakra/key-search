
SUBDIRS= src test

all:
	set -e; for d in $(SUBDIRS); do $(MAKE) -C $$d ; done

clean:
	set -e; for d in $(SUBDIRS); do $(MAKE) -C $$d clean; done
	rm -rf *~

