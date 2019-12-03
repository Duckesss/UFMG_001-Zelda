ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include
O_FLAGS=Entity.o	Game.o	Hitbox.o	Player.o	Instance.o	Zelda.o	Zone.o

all:	zelda.exe

zelda.exe:	$(O_FLAGS)
	g++	-o zelda.exe $(O_FLAGS)	$(PATH_ALLEGRO)$(LIB_ALLEGRO)

Entity.o:	Entity.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Entity.cpp

Game.o:	Game.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Game.cpp

Hitbox.o:	Hitbox.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Hitbox.cpp

Player.o:	Player.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Player.cpp

Instance.o:	Instance.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Instance.cpp

Zelda.o:	Zelda.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Zelda.cpp

Zone.o:	Zone.cpp
	g++	-I	$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)	-c	Zone.cpp

clean:
	del Instance.o
	del Player.o
	del Game.o
	del Entity.o
	del hitbox.o
	del Zelda.o
	del Zone.o
	del Zelda.exe
