# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall

# Relative directories
ODIR = obj
IDIR = inc
SDIR = src
XDIR = extlibs

#Libraries to link to
LIBS = -lsfml-graphics -lsfml-window -lsfml-system



#### OBJECT FILES ####
# Engine Objects
_ENG_OBJ = state_stack.o state.o world_map_state.o main_menu_state.o ingame_state.o local_map_state.o combat_state.o frame_animation.o sprite_animation.o mobile_sprite.o character.o
ENG_OBJ = $(patsubst %, $(ODIR)/%, $(_ENG_OBJ))

#Actors Objects
_ACT_OBJ = actor.o sprite.o
ACT_OBJ = $(patsubst %, $(ODIR)/%, $(_ACT_OBJ))

# SfTileEngine Objects
_SFT_OBJ = sf_world.o sf_tilemap.o sf_tileset.o sf_layer.o sf_tile_layer.o sf_object_layer.o sf_object.o sf_camera.o sf_smart_camera.o sf_loader.o sf_entity.o
SFT_OBJ = $(patsubst %, $(ODIR)/%, $(_SFT_OBJ))

# External Libraries Objects
_EXT_OBJ = tinyxml2.o
EXT_OBJ = $(patsubst %, $(ODIR)/%, $(_EXT_OBJ))



#### DEPENDENCY HEADER FILES ####
# Engine Headers
_ENG_DEP = state_stack.hpp state.hpp frame_animation.hpp sprite_animation.hpp mobile_sprite.hpp character.hpp
ENG_DEP = $(patsubst %, $(IDIR)/engine/%, $(_ENG_DEP))

# Actors Headers
_ACT_DEP = actor.hpp sprite.hpp
ACT_DEP = $(patsubst %, $(IDIR)/actors/%, $(_ACT_DEP))

# SfTileEngine Headers
_SFT_DEP = sf_world.hpp sf_tilemap.hpp sf_tileset.hpp sf_tile.hpp sf_layer.hpp sf_tile_layer.hpp sf_object_layer.hpp sf_object.hpp sf_camera.hpp sf_smart_camera.hpp sf_loader.hpp sf_entity.hpp
SFT_DEP = $(patsubst %, $(IDIR)/tile_engine/%, $(_SFT_DEP))

# External Libraries Headers
_EXT_DEP = tinyxml2
EXT_DEP = $(foreach dep, $(_EXT_DEP), $(XDIR)/$(dep)/$(dep).hpp)
EXT_SRC = $(foreach dep, $(_EXT_DEP), $(XDIR)/$(dep)/$(dep).cpp)



#### RULES ####
# Links object files and libraries into executable
crawler: $(ENG_OBJ) $(SFT_OBJ) $(ACT_OBJ) $(EXT_OBJ) obj/main.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# Compiles engine from /src/engine/*
$(ODIR)/%.o: $(SDIR)/engine/%.cpp $(ENG_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles states from /src/engine/states/*
$(ODIR)/%.o: $(SDIR)/engine/states/%.cpp $(ENG_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles actors from /src/actors/*
$(ODIR)/%.o: $(SDIR)/actors/%.cpp $(ACT_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles tile engine from /src/tile_engine/*
$(ODIR)/%.o: $(SDIR)/tile_engine/%.cpp $(SFT_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles external libs from /extlibs/*/*
$(ODIR)/%.o: $(EXT_SRC) $(EXT_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles the main.cpp file and places the object
# file in the obj/ directory.
$(ODIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)



#### CLEANUP ####
# Ensures that the clean 'rule' isn't mistaken for
# a file name. If a file called 'clean' were made and
# this line wasn't present, the 'clean' file would not
# compile because it has no prerequisites and would be
# considered up-to-date all the time.
# 
# NOTE: Rules only activate if the dependant files
# (right side of colon) have changed since the last time
# the make was run.
.PHONY: clean

# Ran independantly.
# Deletes all object files and the executable.
clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
	rm -f crawler