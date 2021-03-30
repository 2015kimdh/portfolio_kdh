#include "pch.h"
#include "TextureManager.h"

std::vector<GLubyte> GetCImageBits(const CImage & Cimg)
{
	// ���ϰ�
	std::vector<GLubyte> retval;

	// ��Ʈ��(DDB) ���� ���
	BITMAP bmp;
	GetObject(Cimg, sizeof(BITMAP), &bmp);

	// ��Ʈ��(DIB) ���� ����
	BITMAPINFOHEADER bmih{ 0 };

	// bitmap header�� ���� ����
	bmih.biSize = sizeof(BITMAPINFOHEADER);

	bmih.biWidth = bmp.bmWidth;    // ����
	bmih.biHeight = bmp.bmHeight;  // ����

	// ��� ��ġ�� ���� ���� ��. ������ 1�� ����.
	bmih.biPlanes = 1;
	// �ȼ� �� ��Ʈ ��(Bit per Pixel).
	// R8G8B8 = 24�� �⺻������ �������� A8�� �پ 32�� ����Ѵ�.
	bmih.biBitCount = Cimg.GetBPP();
	// RGB ����. 32 BPP�� ��� BI_BITFIELDS�� ��ȿ
	bmih.biCompression = (BI_RGB);

	// ��Ʈ��(DIB) ������ ����
	// �������� ũ�⸦ �˾Ƴ���.
	HDC hDC = ::GetDC(NULL);
	{
		// �̹����� ũ�⸦ Ȯ���ϱ� ���� lpvBits�� NULL�� �ְ�
		// bitmap header�� biSizeImage�� ���� �Է¹޴´�.
		::GetDIBits(hDC, Cimg, 0, bmp.bmHeight, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		// ȹ���� ��Ʈ�� ����� �ް�
		// ������ ���� ������ Ȯ���Ѵ�.
		retval.resize(bmih.biSizeImage);
		// �迭�� �ȼ� ������ ����ȴ�.
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
