
# Makefile du projet.
#

# Répertoire d'installation de CMocka.
# TODO changer pour mettre votre chemin vers cmocka :
export CMOCKA = #Mettre l'adresse vers CMocka
#
# Organisation des sources.
#

#export SRCDIR = src
export TESTDIR = test
export BINDIR = bin

SUBDIRS = $(SRCDIR) $(TESTDIR)

#
# Définitions des outils.
#

export CC = gcc

export CCFLAGS  = -O0 
export CCFLAGS += -DNDEBUG

export CCFLAGS += -MMD -MP # Gestion automatique des dépendances.
export CCFLAGS += -D_BSD_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE -D_DEFAULT_SOURCE -D_GNU_SOURCE
export CCFLAGS += -std=c99 -Wall -pedantic
export CCFLAGS += -Wno-unused-function -Wno-unused-variable
export LDFLAGS  = -lpthread -lrt -L$(CMOCKA)/lib -lcmocka-static




#
# Définitions des binaires à générer.
#

export PROG = $(BINDIR)/ProSE
export TEST = $(BINDIR)/ProSE_test

#
# Règles du Makefile.
#

# Compilation.
all: 
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) $@); done

# Nettoyage.
.PHONY: clean

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) $@); done
	@rm -f $(PROG) $(TEST) core* $(BINDIR)/core*
