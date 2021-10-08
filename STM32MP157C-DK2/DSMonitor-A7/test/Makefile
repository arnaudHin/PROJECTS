#
# Makefile des sources du projet.
#

#
# Organisation des sources.
#

# Wrap des méthodes pour bouchonnage.
LDWRAP  =  -Wl,--wrap=DispatcherDSMS_run 
LDWRAP +=  -Wl,--wrap=ProxyMeasuresProcessorApp_storeMeasuresArray
LDWRAP +=  -Wl,--wrap=ProxySessionArchiver_storeMetaMeasures
LDWRAP +=  -Wl,--wrap=ProxySessionArchiver_storeEndSession
LDWRAP +=  -Wl,--wrap=ProxyMeasuresProcessorSupervisor_askStopSession
LDWRAP +=  -Wl,--wrap=ProxyMeasuresProcessorSupervisor_askStartSession
LDWRAP +=  -Wl,--wrap=ProxySessionArchiver_storeBeginSession

# Packages.
PACKAGES = comDSMonitorApp Monitor comDSMonitorSupervisor

# Méthodes bouchonnées pour des besoins internes à un module.

# Un niveau de package est accessible.
SRC = $(wildcard */*.c)		
OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = main_test.c

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Executable à générer
EXEC = ../$(TEST)

# Inclusion depuis le niveau du package.
CCFLAGS += -I. -I$(CMOCKA)/include 

# Liens pour les tests.
LDFLAGS += -L$(CMOCKA)/lib

# Utilisation de la librairie static CMocka
LDFLAGS += -lcmocka-static
#
# Règles du Makefile.
#

# Compilation.
all:
	@for p in $(PACKAGES); do (cd $$p && $(MAKE) $@); done
	@$(MAKE) $(EXEC)

$(EXEC): $(OBJ) $(MAIN)
	$(CC) $(CCFLAGS) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS) $(LDWRAP)

# Nettoyage.
.PHONY: clean

clean:
	@for p in $(PACKAGES); do (cd $$p && $(MAKE) $@); done
	@rm -f $(DEP)

-include $(DEP)

