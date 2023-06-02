# commande de compilation
CC = gcc -Wall 
# commande de création de dossier
MK = mkdir
#commande copie
CP = cp -r
# commande de suppression
RM = rm -rf
# commande d'archive
TAR = tar -cvzf
# fichier source 
SRC = $(wildcard $(srcdir)*.c)
#fichier entete
HEAD = $(wildcard $(srcdir)*.h)
#fichier objet
OBJ = $(subst $(srcdir), $(bindir), $(SRC:.c=.o))
#nom du programme
PROG = $(bindir)exe
#fichier restauration 
RES = $(wildcard $(savedir)*)
# repertoire qui contient les sources, et les entetes du projet
srcdir = ./src/
#repertoire qui contient les objets, et executables du projet
bindir = ./bin/
# repertoire qui contient la documentation technique du projet
docdir = ./doc/
#repertoire qui contient les fichiers de sauvegarde du projet
savedir = ./save/
#repertoire d'archive 
archivedir = ./bernardadr-tp6-7

all : $(PROG)

$(PROG) : $(OBJ) # compilation du programme 
	$(CC) $^ -o $@

#compilation des objets
$(bindir)%.o : $(srcdir)%.c  
	$(CC) -c $^ -o $@
.PHONY : save 
save : $(SRC) $(HEAD)
	$(CP) $(SRC) $(savedir)
	$(CP) $(HEAD) $(savedir)

.PHONY : exe
exe : 
	$(bindir)./exe

.PHONY : doc 
doc : 
	doxygen $(docdir)Doxyfile
restore : $(RES)
	$(CP) $(RES) $(srcdir)

give : 
	
	$(MK) $(archivedir)
	$(CP) $(srcdir) $(archivedir)
	$(CP) $(savedir) $(archivedir)
	$(CP) $(docdir) $(archivedir)
	$(CP) $(bindir) $(archivedir)
	$(CP) Makefile $(archivedir)
	$(CP) readme.txt $(archivedir)
	$(TAR) $(archivedir).tar.gz $(archivedir)
	$(RM) $(archivedir)

.PHONY : clean

# effacement des objets
clean : 	
	$(RM) $(OBJ) $(PROG)
