#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

class TechniqueBarla : public RenderingTechnique
{
public:
	TechniqueBarla();
	virtual ~TechniqueBarla();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

private:
	void InitTextures();
	void InitShader();

	unsigned int mCurrentLookUp;
	unsigned int mLookUps[3];
	ShaderProgram mShader;


	///////////////// Constants /////////////////
	const string TEXTURE_NAME_1 = "ColorScheme1";
	const string TEXTURE_NAME_2 = "ColorScheme2";
	const string TEXTURE_NAME_3 = "ColorScheme3";

	const string SHADER_NAME = "Barla";
};

