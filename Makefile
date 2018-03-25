#OBJS specifies which files to compile as part of the project
OBJS = game_utils.cpp texture_atlas.cpp sound_atlas.cpp font_atlas.cpp gui_widget.cpp gui_button.cpp gui_img_button.cpp gui_window.cpp pause_dialog.cpp spritesheet.cpp animation_sequence.cpp animation_player.cpp animation_engine.cpp item.cpp consumable.cpp gun.cpp pistol_ammo.cpp attack.cpp punch.cpp sword_swing.cpp fired_bullet.cpp sword.cpp item_stack.cpp item_drop.cpp inventory.cpp sprite_action.cpp move_in_dir_action.cpp follow_path_action.cpp idle_action.cpp wander_action.cpp follow_sprite_action.cpp health_regen_action.cpp knockback_action.cpp healthbar.cpp player_hud.cpp sprite.cpp sprite_controller.cpp player_sprite_controller.cpp civilian_sprite_controller.cpp sound.cpp player_sprite.cpp civilian_sprite.cpp map_chunk.cpp map.cpp test_c_game.cpp 

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