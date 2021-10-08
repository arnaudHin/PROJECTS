#
# Organisation des sources.
#

# Packages du projet (à compléter si besoin est).
PACKAGES = comDSMonitorSupervisor
PACKAGES += comDSMonitorApp
PACKAGES += monitor

# Un niveau de package est accessible.
SRC  = $(wildcard */*.c)
# Pour ajouter un second niveau :		
# SRC += $(wildcard */*/*.c)

OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = StarterDSMonitor.c
MAIN_OBJ = $(MAIN:.c=.o)

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Exécutable à générer.
EXEC = ../bin/DSMonitor.elf

# Inclusion depuis le niveau du package.
export CCFLAGS  = -O0 
export CCFLAGS += -DNDEBUG
export CCFLAGS += -MMD -MP # Gestion automatique des dépendances.
export CCFLAGS += -D_BSD_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE -D_DEFAULT_SOURCE -D_GNU_SOURCE
export CCFLAGS += -std=c99 -Wall -pedantic
export CCFLAGS += -Wno-unused-function -Wno-unused-variable

export LDFLAGS  = -lpthread -lrt


#
# Règles du Makefile.
#

# Compilation.
all:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done
	@$(MAKE) CCFLAGS="$(CCFLAGS)" LDFLAGS="$(LDFLAGS)" $(EXEC)

$(EXEC): $(OBJ) $(MAIN_OBJ)
	@$(CC) $(CCFLAGS) $(OBJ) $(MAIN_OBJ) -MF -MMD -o $(EXEC) $(LDFLAGS)

$(MAIN_OBJ) : $(MAIN)
	@$(CC) $(CCFLAGS) -c $(MAIN) -o $(MAIN_OBJ)

# Nettoyage.
.PHONY: clean

clean:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done
	@rm -f $(DEP) $(MAIN_OBJ)
	@rm -f $(EXEC)

-include $(DEP)

