#pragma once
// ���� ���丮
#define DIR_WORMS_PARENTS "Worms_Armageddon"
#define DIR_RESOURCES "Resources"
#define DIR_IMAGE "Image"
#define DIR_EFFECTS "Effects"
#define DIR_FONT "Font"
#define DIR_MAP "Map"
#define DIR_WEAPONS "Weapons"
#define DIR_WORMS "Worms"
#define DIR_MISC "Misc"
#define DIR_UI "UI"


//#define DIR_HIT "hit"
//#define DIR_NOTUSED "notUsed"


//#define DIR_AIM_TAGET "Aim_Taget"
//#define DIR_CURSOR "Cursor"
//#define DIR_GRAVE "Grave"
//#define DIR_ITEM "Item"
//#define DIR_PLAYER_ARROW "Player_arrow"


//#define DIR_BUTTONBORDERS "ButtonBorders"
//#define DIR_CREATETEAM "CreateTeam"
//#define DIR_GAMEOPTIONS "gameoptions"
//#define DIR_HPBAR "Hpbar"
//#define DIR_MENU "Menu"
//#define DIR_MULTIPLAY "Multiplay"
//#define DIR_SELECTMAP "SelectMap"
//#define DIR_TIMER "Timer"
//#define DIR_WEAPON_ICONS "Weapon_icons"




// ���� Ȯ����
#define FILE_EXT_BMP "Bmp"

// �÷��̾� ������
#define PLAYER_DIR_LEFT "Left"
#define PLAYER_DIR_RIGHT "Right"
#define PLAYER_SIZE_X 12.0f
#define PLAYER_SIZE_Y 25.0f
#define PLAYER_SPEED 50.0f
#define PLAYER_SPEED_FALL 200.0f
#define PLAYER_SPEED_FALL_MAX 300.0f
#define PLAYER_MAX_NUMBER 8

// ����
#define LEVEL_TITLE_LEVEL "TitleLevel"
#define LEVEL_LOBBY_LEVEL "LobbyLevel"
#define LEVEL_PLAY_LEVEL "PlayLevel"

// Ű
#define KEY_CHANGE_PLAYLEVEL "ChangePlayLevel"
#define KEY_CHANGE_LOBBYLEVEL "ChangeLobbyLevel"
#define KEY_CHANGE_PIXELMODE "ChangePixelMode"
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_JUMP "MoveJump"
#define KEY_MOVE_BACKFLIP "MoveBackflip"
#define KEY_ANGLE_UP "AngleUp"
#define KEY_ANGLE_DOWN "AngleDown"
#define KEY_FIRE "PlayerAction"

#define KEY_WEAPON_BAZ "WeaponBaz"
#define KEY_WEAPON_GRENADE "WeaponGrenade"

// ���콺
#define KEY_MOUSE_LEFT "ClickLeft"
#define KEY_MOUSE_MID "ClickMid"
#define KEY_MOUSE_RIGHT "ClickRight"

// �̹��� �̸�
#define IMG_GRADIENT "gradient.bmp"
#define IMG_MAPBOOKS "MapBooks.bmp"
#define IMG_MIDGROUND "Midground.bmp"
#define IMG_MAPBOOKS_GROUND "MapBooks_Ground.bmp"

#define IMG_EFFECT_BOOM "Boom.bmp"

// �̹��� ������
#define SCALE_GRADIENT_X 1280.0f
#define SCALE_GRADIENT_Y 720.0f
#define SCALE_MAPBOOKS_X 3840.0f
#define SCALE_MAPBOOKS_Y 1392.0f
#define SCALE_MAPBOOKS_GROUND_X 3840.0f
#define SCALE_MAPBOOKS_GROUND_Y 1392.0f
#define SCALE_MAPBOOKS_LOBBY_X 3840.0f
#define SCALE_MAPBOOKS_LOBBY_Y 1392.0f

#define SCALE_EFFECT_BOOM_X 100.0f
#define SCALE_EFFECT_BOOM_Y 100.0f

// �÷��̾� �̹���
#define IMG_PLAYER_IDLE_LEFT "idleLeft.bmp"
#define IMG_PLAYER_IDLE_RIGHT "idleRight.bmp"
#define IMG_PLAYER_JUMPRDY_LEFT "jumpReadyLeft.bmp"
#define IMG_PLAYER_JUMPRDY_RIGHT "jumpReadyRight.bmp"
#define IMG_PLAYER_FLYLINK_LEFT "flyLinkLeft.bmp"
#define IMG_PLAYER_FLYLINK_RIGHT "flyLinkRight.bmp"
#define IMG_PLAYER_FLYDOWN_LEFT "flyDownLeft.bmp"
#define IMG_PLAYER_FLYDOWN_RIGHT "flyDownRight.bmp"
#define IMG_PLAYER_BACKFLIP_LEFT "backflipLeft.bmp"
#define IMG_PLAYER_BACKFLIP_RIGHT "backflipRight.bmp"
#define IMG_PLAYER_WALK_LEFT "WalkLeft.bmp"
#define IMG_PLAYER_WALK_RIGHT "WalkRight.bmp"


// �ִϸ��̼� Ű����
#define ANIM_KEYWORD_PLAYER_IDLE "idle"
#define ANIM_KEYWORD_PLAYER_JUMPRDY "jumpReady"
#define ANIM_KEYWORD_PLAYER_FLYLINK "flyLink"
#define ANIM_KEYWORD_PLAYER_FLYDOWN "flyDown"
#define ANIM_KEYWORD_PLAYER_BACKFLIP "backflip"
#define ANIM_KEYWORD_PLAYER_WALK "Walk"
#define ANIM_KEYWORD_PLAYER_JUMP "Jump"

#define ANIM_KEYWORD_DIR_LEFT "Left"
#define ANIM_KEYWORD_DIR_RIGHT "Right"

// �ִϸ��̼� �̸�
#define ANIM_NAME_PLAYER_IDLE_LEFT "idleLeft"
#define ANIM_NAME_PLAYER_IDLE_RIGHT "idleRight"
#define ANIM_NAME_PLAYER_JUMPRDY_LEFT "jumpReadyLeft"
#define ANIM_NAME_PLAYER_JUMPRDY_RIGHT "jumpReadyRight"
#define ANIM_NAME_PLAYER_FLYLINK_LEFT "flyLinkLeft"
#define ANIM_NAME_PLAYER_FLYLINK_RIGHT "flyLinkRight"
#define ANIM_NAME_PLAYER_FLYDOWN_LEFT "flyDownLeft"
#define ANIM_NAME_PLAYER_FLYDOWN_RIGHT "flyDownRight"
#define ANIM_NAME_PLAYER_BACKFLIP_LEFT "backflipLeft"
#define ANIM_NAME_PLAYER_BACKFLIP_RIGHT "backflipRight"
#define ANIM_NAME_PLAYER_WALKLEFT "WalkLeft"
#define ANIM_NAME_PLAYER_WALKRIGHT "WalkRight"
#define ANIM_NAME_PLAYER_JUMPRIGHT "JumpRight"
#define ANIM_NAME_PLAYER_JUMPLEFT "JumpLeft"


#define ANIM_NAME_WEAPON_ON_LEFT "bazOnLeft"
#define ANIM_NAME_WEAPON_ON_RIGHT "bazOnRight"
#define ANIM_NAME_WEAPON_OFF_LEFT "bazOffLeft"
#define ANIM_NAME_WEAPON_OFF_RIGHT "bazOffRight"

// ���� �̹���
#define IMG_BAZ_AIM_LEFT "bazAimLeft.bmp"
#define IMG_BAZ_AIM_RIGHT "bazAimRight.bmp"
#define IMG_HOMING_AIM_LEFT "homingAimLeft.bmp"
#define IMG_HOMING_AIM_RIGHT "homingAimRight.bmp"
#define IMG_BAZ_ON_LEFT "bazOnLeft.bmp"
#define IMG_BAZ_ON_RIGHT "bazOnRight.bmp"
#define IMG_BAZ_OFF_LEFT "bazOffLeft.bmp"
#define IMG_BAZ_OFF_RIGHT "bazOffRight.bmp"
#define IMG_MISSILE "missile.bmp"

// ����Ʈ
#define IMG_FX_EXFOOM "exfoom.bmp"
#define IMG_FX_CIRCLE50 "circle50.bmp"
#define IMG_FX_ELIPSE50 "elipse50.bmp"

// ����Ʈ �ִϸ��̼�
#define ANIM_NAME_FX_EXFOOM "exfoomAnim"
#define ANIM_NAME_FX_CIRCLE50 "circle50Anim"
#define IMG_MISSILE "missile.bmp"

// �ݸ��� �׷�
#define COL_GROUP_BUTTON "Button"
#define COL_GROUP_MOUSE "Mouse"