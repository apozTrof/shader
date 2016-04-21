#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

class TechniqueMultiTexture : public RenderingTechnique
{
public:
	TechniqueMultiTexture();
	virtual ~TechniqueMultiTexture();

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
	const string TEXTURE_NAME_1 = "Earth_DayMap";
	const string TEXTURE_NAME_2 = "Earth_NightMap";
	const string TEXTURE_NAME_3 = "Earth_SpecMap";

	const string SHADER_NAME = "MultiTexture";
};
