#pragma once
// 파일 디렉토리
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




// 파일 확장자
#define FILE_EXT_BMP "Bmp"

// 플레이어 설정값
#define PLAYER_DIR_LEFT "Left"
#define PLAYER_DIR_RIGHT "Right"
#define PLAYER_SIZE_X 12.0f
#define PLAYER_SIZE_Y 25.0f
#define PLAYER_SPEED 50.0f
#define PLAYER_SPEED_FALL 200.0f
#define PLAYER_SPEED_FALL_MAX 300.0f
#define PLAYER_MAX_TEAM 6
#define PLAYER_MAX_NUMBER 8

// 카메라 설정값

// 레벨
#define LEVEL_TITLE_LEVEL "TitleLevel"
#define LEVEL_LOBBY_LEVEL "LobbyLevel"
#define LEVEL_PLAY_LEVEL "PlayLevel"

// 키
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
#define DEBUG_KEY "Debug"

#define KEY_WEAPON_BAZ "WeaponBaz"
#define KEY_WEAPON_GRENADE "WeaponGrenade"
#define KEY_WEAPON_AIRSTRIKE "WeaponAirStrike"
#define KEY_WEAPON_SUPERSHEEP "WeaponSuperSheep"

// 마우스
#define IMG_MOUSE_CURSOR "Cursor.bmp"
#define KEY_MOUSE_LEFT "ClickLeft"
#define KEY_MOUSE_MID "ClickMid"
#define KEY_MOUSE_RIGHT "ClickRight"

// 이미지 이름
#define IMG_GRADIENT "gradient.bmp"
#define IMG_MAPBOOKS "MapBooks.bmp"
#define IMG_MIDGROUND "Midground.bmp"
#define IMG_MAPBOOKS_GROUND "MapBooks_Ground.bmp"

#define IMG_EFFECT_BOOM "Boom.bmp"

// 이미지 스케일
#define SCALE_GRADIENT_X 1280.0f
#define SCALE_GRADIENT_Y 720.0f
#define SCALE_MAPBOOKS_X 5000.0f * 0.4f
#define SCALE_MAPBOOKS_Y 3200.0 * 0.4f
#define SCALE_MAPBOOKS_GROUND_X 5000.0f * 0.4f
#define SCALE_MAPBOOKS_GROUND_Y 3200.0 * 0.4f

// 이펙트용 스케일
#define SCALE_EFFECT_BOOM_X 100.0f
#define SCALE_EFFECT_BOOM_Y 100.0f

// 카메라용 스케일
#define SCALE_CAMERA_MAPMOOKS_X 5000.0f * 0.4f
#define SCALE_CAMERA_MAPMOOKS_Y 3200.0 * 0.4f + 100.0f

// 플레이어 이미지
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
#define IMG_PLAYER_FALL "wtwang.bmp"


// 애니메이션 키워드
#define ANIM_KEYWORD_PLAYER_IDLE "idle"
#define ANIM_KEYWORD_PLAYER_JUMPRDY "jumpReady"
#define ANIM_KEYWORD_PLAYER_FLYLINK "flyLink"
#define ANIM_KEYWORD_PLAYER_FLYDOWN "flyDown"
#define ANIM_KEYWORD_PLAYER_BACKFLIP "backflip"
#define ANIM_KEYWORD_PLAYER_WALK "Walk"
#define ANIM_KEYWORD_PLAYER_JUMP "Jump"
#define ANIM_KEYWORD_PLAYER_FALL "Falled"


#define ANIM_KEYWORD_DIR_LEFT "Left"
#define ANIM_KEYWORD_DIR_RIGHT "Right"

// 애니메이션 이름
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
#define ANIM_NAME_PLAYER_FALL "Falled"


#define ANIM_NAME_WEAPON_ON_LEFT "bazOnLeft"
#define ANIM_NAME_WEAPON_ON_RIGHT "bazOnRight"
#define ANIM_NAME_WEAPON_OFF_LEFT "bazOffLeft"
#define ANIM_NAME_WEAPON_OFF_RIGHT "bazOffRight"

// 무기 이미지
#define IMG_BAZ_AIM_LEFT "bazAimLeft.bmp"
#define IMG_BAZ_AIM_RIGHT "bazAimRight.bmp"
#define IMG_HOMING_AIM_LEFT "homingAimLeft.bmp"
#define IMG_HOMING_AIM_RIGHT "homingAimRight.bmp"
#define IMG_BAZ_ON_LEFT "bazOnLeft.bmp"
#define IMG_BAZ_ON_RIGHT "bazOnRight.bmp"
#define IMG_BAZ_OFF_LEFT "bazOffLeft.bmp"
#define IMG_BAZ_OFF_RIGHT "bazOffRight.bmp"
//#define IMG_MISSILE "missile.bmp"
#define IMG_AIRJET_GREEN_LEFT "airjetg.bmp"
#define IMG_AIRJET_GREEN_RIGHT "airjetgRight.bmp"
#define IMG_AIRJET_AIRBOMB_SPIN "airBomb.bmp"
#define IMG_AIRJET_AIRBOMB_FILTER "airBombFilter.bmp"
#define IMG_SHEEP_BULLET_LEFT "sheepwlkLeft.bmp"
#define IMG_SHEEP_BULLET_RIGHT "sheepwlk.bmp"

// 무기 애니메이션
#define ANIM_NAME_SHEEP_LEFT "sheepwlkAnimLeft"
#define ANIM_NAME_SHEEP_RIGHT "sheepwlkAnimRight"

// 이펙트
#define IMG_FX_EXFOOM "exfoom.bmp"
#define IMG_FX_CIRCLE50 "circle50.bmp"
#define IMG_FX_ELIPSE50 "elipse50.bmp"

// 이펙트 애니메이션
#define ANIM_NAME_FX_EXFOOM "exfoomAnim"
#define ANIM_NAME_FX_CIRCLE50 "circle50Anim"
#define ANIM_NAME_FX_ELIPSE50 "Elipse50Anim"

// 콜리전 그룹
#define COL_GROUP_BUTTON "Button"
#define COL_GROUP_MOUSE "Mouse"


//무기 사이즈
#define BAZ_COL_SIZE {15.0f,15.0f}
#define COL_GROUP_MOUSE "Mouse"

// 무기 설정값
#define WEAPON_DEFAULT_SHOT_ANGLE {0.0f, -5.0f}
#define WEAPON_DEFAULT_SHOT_POWER 0.0f
#define WEAPON_MAX_SHOT_POWER 500.0f
#define WEAPON_MIN_SHOT_ANGLE {0.0f, -0.1f}
#define WEAPON_MAX_SHOT_ANGLE {0.0f, -9.8f}
#define WEAPON_AIRFLY_HIGHT 0.0f
#define WEAPON_AIRFLY_SPEED 500.0f
#define WEAPON_AIRFLY_START_LEFT -500.0f
#define WEAPON_AIRFLY_START_RIGHT 2100.0f
