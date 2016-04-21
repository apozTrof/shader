#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

/* Bump-Mapping shader */
class TechniqueBonus : public RenderingTechnique
{
public:
	TechniqueBonus();
	virtual ~TechniqueBonus();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

private:
	void InitTextures();
	void InitShader();

	unsigned int mCurrentLookUp;
	unsigned int mLookUps[2];

	ShaderProgram mShader;

	///////////////// Constants /////////////////
	const string TEXTURE_NAME_1 = "WireWeave_Texture";
	const string TEXTURE_NAME_2 = "WireWeave_Bump2";

	const string SHADER_NAME = "BumpMapping";
};