#
# Makefile des tests du projet.
#
# @author Ibrahima
#

#
# Organisation des sources de test.
#

# Packages.
PACKAGES = comDSSupervisor \
	processorSupervisor \
	sensorManager 

# Wrap des méthodes du Stock pour bouchonage.
LDWRAP  = -Wl,--wrap=
LDWRAP += -Wl,--wrap=
LDWRAP += -Wl,--wrap= 

# Deux niveaux de packages sont accessibles
SRC  = $(wildcard */*.c)
SRC += $(wildcard */*/*.c)

OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = mainTest.c

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Executable à générer.
EXEC = ../$(TEST)

# Inclusion depuis le niveau du package.
CCFLAGS += -I. -I$(CMOCKA)/include

# Liens pour les tests.
LDFLAGS += -L$(CMOCKA)/lib

# Utilisation de la librairie static CMocka
LDFLAGS += -lcmocka-static
# Force l'utilisation d'une librairie statique pour CMocka.
# LDFLAGS += -Wl,-static -lcmocka-static -Wl,-Bdynamic


#
# Règles du Makefile.
#

# Compilation.
all:
	@for p in $(PACKAGES); do (cd $$p && $(MAKE) $@); done
	$(MAKE) $(EXEC)

$(EXEC): $(OBJ) $(MAIN)
	$(CC) $(CCFLAGS) $(LDWRAP) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS)

# Nettoyage.
.PHONY: clean

clean:
	@for p in $(PACKAGES); do (cd $$p && $(MAKE) $@); done
	@rm -f $(DEP)

-include $(DEP)

