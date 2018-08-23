#OBJS specifies which files to compile as part of the project
OBJS = game_utils.cpp engine/texture_atlas.cpp engine/sound_atlas.cpp engine/font_atlas.cpp engine/controller_adapter.cpp gui/gui_widget.cpp gui/gui_button.cpp gui/gui_img_button.cpp gui/gui_window.cpp gui/pause_dialog.cpp engine/spritesheet.cpp engine/animation_sequence.cpp engine/animation_player.cpp engine/animation_engine.cpp item/item.cpp item/consumable.cpp item/gun.cpp item/pistol_ammo.cpp sprite/attack.cpp attack/punch.cpp attack/sword_swing.cpp attack/fired_bullet.cpp item/sword.cpp item/item_stack.cpp item/item_drop.cpp sprite/inventory.cpp action/sprite_action.cpp action/move_in_dir_action.cpp action/follow_path_action.cpp action/idle_action.cpp action/wander_action.cpp action/follow_sprite_action.cpp action/health_regen_action.cpp action/knockback_action.cpp sprite/healthbar.cpp engine/player_hud.cpp sprite/sprite.cpp sprite/sprite_controller.cpp sprite/player_sprite_controller.cpp sprite/civilian_sprite_controller.cpp engine/sound.cpp map/map_chunk.cpp map/map_terrain.cpp map/map.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++11

INCLUDE=-Iengine -Iitem -Isprite -Imap -Igui -Iaction -Iattack -I.

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test_c_game

#This is the target that compiles our executable
all : main_game test_anim test_keymap test_sound

main_game: $(OBJS)
	$(CC) test_c_game.cpp $(OBJS) $(COMPILER_FLAGS) $(INCLUDE) $(LINKER_FLAGS) -o $(OBJ_NAME)

test_anim: $(OBJS)
	$(CC) test/test_animation.cpp $(OBJS) $(COMPILER_FLAGS) $(INCLUDE) $(LINKER_FLAGS) -o test_anim

test_keymap: $(OBJS)
	$(CC) test/test_controller_adapter.cpp $(OBJS) $(COMPILER_FLAGS) $(INCLUDE) $(LINKER_FLAGS) -o test_keymap

test_sound: $(OBJS)
	$(CC) test/test_sound.cpp $(OBJS) $(COMPILER_FLAGS) $(INCLUDE) $(LINKER_FLAGS) -o test_sound

test_map: $(OBJS)
	$(CC) test/test_map.cpp $(OBJS) $(COMPILER_FLAGS) $(INCLUDE) $(LINKER_FLAGS) -o test_sound
