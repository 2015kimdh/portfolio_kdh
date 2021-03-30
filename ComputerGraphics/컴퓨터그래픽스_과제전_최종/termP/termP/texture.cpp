#include "pch.h"
#include "texture.h"

c_texture::c_texture()
{
}

c_texture::~c_texture()
{
}

void c_texture::set()
{
	glGenTextures(2, texture_object);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = LoadDIBitmap("test.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);

	//텍스처 활성화

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//glBindTexture(GL_TEXTURE_2D, texture_object[1]);

	////2차원상의 텍스처 이미지 정의
	//TexBits = LoadDIBitmap("test2.bmp", &texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	
	////텍스처 활성화

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	////glEnable(GL_TEXTURE_GEN_S);
	////glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glEnable(GL_TEXTURE_2D);

}