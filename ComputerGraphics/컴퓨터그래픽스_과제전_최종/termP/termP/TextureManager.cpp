#include "pch.h"
#include "TextureManager.h"

std::vector<GLubyte> GetCImageBits(const CImage & Cimg)
{
	// 리턴값
	std::vector<GLubyte> retval;

	// 비트맵(DDB) 정보 얻기
	BITMAP bmp;
	GetObject(Cimg, sizeof(BITMAP), &bmp);

	// 비트맵(DIB) 정보 설정
	BITMAPINFOHEADER bmih{ 0 };

	// bitmap header는 고정 길이
	bmih.biSize = sizeof(BITMAPINFOHEADER);

	bmih.biWidth = bmp.bmWidth;    // 가로
	bmih.biHeight = bmp.bmHeight;  // 세로

	// 대상 장치에 대한 면의 수. 무조건 1로 지정.
	bmih.biPlanes = 1;
	// 픽셀 당 비트 수(Bit per Pixel).
	// R8G8B8 = 24가 기본이지만 아이콘은 A8이 붙어서 32를 사용한다.
	bmih.biBitCount = Cimg.GetBPP();
	// RGB 포맷. 32 BPP일 경우 BI_BITFIELDS가 유효
	bmih.biCompression = (BI_RGB);

	// 비트맵(DIB) 데이터 추출
	// 데이터의 크기를 알아낸다.
	HDC hDC = ::GetDC(NULL);
	{
		// 이미지의 크기를 확인하기 위해 lpvBits를 NULL로 주고
		// bitmap header의 biSizeImage에 값을 입력받는다.
		::GetDIBits(hDC, Cimg, 0, bmp.bmHeight, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		// 획득한 비트맵 사이즈를 받고
		// 데이터 저장 공간을 확보한다.
		retval.resize(bmih.biSizeImage);
		// 배열에 픽셀 정보가 저장된다.
		::GetDIBits(hDC, Cimg, 0, bmp.bmHeight, &(retval[0]), (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	}
	::ReleaseDC(NULL, hDC);

	return retval;
}
CTextureManager::CTextureManager()
{
	LoadTexture(ENUM_TEXTURE::START_SCENE, "resource/start_scene.png");
	LoadTexture(ENUM_TEXTURE::PLAYER1_WIN_SCENE, "resource/Player1_win_scene.png");
	LoadTexture(ENUM_TEXTURE::PLAYER2_WIN_SCENE, "resource/Player2_win_scene.png");
	LoadTexture(ENUM_TEXTURE::GEAR0, "resource/Gear0.png");
	LoadTexture(ENUM_TEXTURE::GEAR1, "resource/Gear1.png");
	LoadTexture(ENUM_TEXTURE::GEAR2, "resource/Gear2.png");
	LoadTexture(ENUM_TEXTURE::GEAR3, "resource/Gear3.png");
	LoadTexture(ENUM_TEXTURE::GEAR4, "resource/Gear4.png");
	LoadTexture(ENUM_TEXTURE::POINT, "resource/point.png");
	LoadTexture(ENUM_TEXTURE::NIDDLE, "resource/niddle.png");
	LoadTexture(ENUM_TEXTURE::EXPLOTION, "resource/explotion.png");
	LoadTexture(ENUM_TEXTURE::READY, "resource/ready.png");

}

CTextureManager::~CTextureManager()
{

}

bool CTextureManager::EnableTextur(ENUM_TEXTURE id) const
{
	auto& tmpID = m_ObjectID.find(id)->second;
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	return	tmpID.EnableTexture();

}

void CTextureManager::DisableTextur(ENUM_TEXTURE id, bool EnableTexturRetrun) const
{
	auto& tmpID = m_ObjectID.find(id)->second;
	tmpID.DisableTexture(EnableTexturRetrun);

	glDisable(GL_TEXTURE_2D);
}
