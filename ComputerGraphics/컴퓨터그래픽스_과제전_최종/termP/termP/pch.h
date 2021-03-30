// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

#ifndef PCH_H
#define PCH_H

#define PI 3.141592

#include <GL/freeglut.h>
#include <iostream>
#include <minmax.h>

#include <time.h>
#include <math.h>

#include "Camera.h"
#include "c_background.h"
#include "c_ship.h"
#include "texture.h"
#include "Sound.h"
#include "c_missile.h"
#include "objloader.h"
#include "c_light.h"
#include "c_scene.h"
#include "c_ui.h"
#include "c_weather.h"

#include <filesystem>
#define typePATH std::experimental::filesystem::path
//?????여긴가???


#define TextureInstance  CTextureManager::GetInstance()
#define TEXTURE_NUM 11

enum class ENUM_TEXTURE {
	START_SCENE,
	PLAYER1_WIN_SCENE,
	PLAYER2_WIN_SCENE,
	GEAR0,
	GEAR1,
	GEAR2,
	GEAR3,
	GEAR4,
	NIDDLE,
	POINT,
	EXPLOTION,
	READY
};

#define SCENE_NUM 5

enum ENUM_SCENE
{
	SCENE_START,
	SCENE_PLAYING,
	SCENE_PLAYER1_WIN,
	SCENE_PLAYER2_WIN,
	SCENE_SELECT
};



// TODO: 여기에 미리 컴파일하려는 헤더 추가

#endif //PCH_H
