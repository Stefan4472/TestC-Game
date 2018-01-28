#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = game_utils.cpp texture_atlas.cpp sound_atlas.cpp font_atlas.cpp gui_widget.cpp gui_button.cpp gui_img_button.cpp gui_window.cpp pause_dialog.cpp spritesheet.cpp item.cpp consumable.cpp attack.cpp sword_swing.cpp bullet.cpp sword.cpp pistol.cpp inventory.cpp action.cpp trigger.cpp action_set.cpp healthbar.cpp player_hud.cpp sprite.cpp sprite_controller.cpp sound.cpp player_sprite.cpp civilian_sprite.cpp map_chunk.cpp map.cpp test_c_game.cpp 

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test_c_game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)