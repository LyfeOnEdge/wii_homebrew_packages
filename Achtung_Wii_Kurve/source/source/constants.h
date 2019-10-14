#ifndef __constants
#define __constants

#include <wiiuse/wpad.h>

#ifdef __cplusplus
extern "C" {
#endif

// Colors
const u32 C_WHITE=0xFFFFFFFF;
const u32 C_GRAY=0x7F7F7FFF;
const u32 C_BLACK=0x000000FF;
const u32 C_RED=0xFF0000FF;
const u32 C_LIME=0x00FF00FF;
const u32 C_PINK=0xFF007FFF;
const u32 C_PURPLE=0xFF00FFFF;
const u32 C_YELLOW=0xFFFF00FF;
const u32 C_CYAN=0x00FFFFFF;
const u32 C_MILK_BLUE=0x7F7FFF;
const u32 C_GREEN=0x007F00FF;
const u32 C_ORANGE=0xFF7F00FF;
const u32 C_VIOLET=0x7F007FFF;

// Color Array
const u32 COLOR_ARRAY[12]={
C_RED,
C_CYAN,
C_YELLOW,
C_LIME,
C_PINK,
C_PURPLE,
C_MILK_BLUE,
C_GREEN,
C_ORANGE,
C_VIOLET,
C_GRAY,
C_WHITE
};

// Math
const f32 PI=3.14159265358979;

// Music Length
const int MAX_MUSIC_VOLUME=70;
const int MIN_MUSIC_VOLUME=25;

// Game
const int GRID_WIDTH = 270;
const int GRID_HEIGHT = 160;

// Cursor image size
const int CURSOR_IMAGE_SIZE=96;
const int CURSOR_IMAGE_HYPOTENUSE=68;

// Stick
enum Stick {STICK_NUNCHUK,STICK_CLASSIC_LEFT,STICK_CLASSIC_RIGHT};

// Control
enum Control {CONTROL_POINT,CONTROL_TILT,CONTROL_STICK_CLASSIC,CONTROL_STICK_SPECIAL};

// AI
enum AI_TurnType {AI_TURN_LEFT,AI_TURN_RIGHT,AI_DONT_TURN};

// Program states
enum State {STATE_MENU, STATE_PLAYERS, STATE_GAME, STATE_WINNER, STATE_CREDITS, STATE_PREFERENCES};

// Selectables interger constants

	// Menu
	const int SELECT_MENU_START=0;
	const int SELECT_MENU_PREFERENCES=1;
	const int SELECT_MENU_CREDITS=2;
	const int SELECT_MENU_QUIT=3;
	const int MAX_SELECT_MENU=3;

	// Preferences
	const int SELECT_PREFERENCES_COMPS=0;
	const int SELECT_PREFERENCES_SPEED=1;
	const int SELECT_PREFERENCES_TURNING_RADIUS=2;
	const int SELECT_PREFERENCES_HOLE_SIZE=3;
	const int SELECT_PREFERENCES_HOLE_SEPARATION=4;
	const int SELECT_PREFERENCES_GOAL_FACTOR=5;
	const int SELECT_PREFERENCES_BOARDERS=6;
	const int SELECT_PREFERENCES_RUMBLE=7;
	const int SELECT_PREFERENCES_SOUND_EFFECTS=8;
	const int SELECT_PREFERENCES_BACKGROUND_MUSIC=9;
	const int SELECT_PREFERENCES_SAVE_PREFERENCES=10;
	const int SELECT_PREFERENCES_LOAD_PREFERENCES=11;
	const int SELECT_PREFERENCES_RESTORE_DEFAULTS=12;
	const int SELECT_PREFERENCES_BACK=13;
	const int MAX_SELECT_PREFERENCES=13;

#ifdef __cplusplus
}
#endif

#endif
