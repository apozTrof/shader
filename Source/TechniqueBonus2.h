#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

class TechniqueBonus2 : public RenderingTechnique
{

public:
	TechniqueBonus2();
	virtual ~TechniqueBonus2();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

protected:
	void InitTextures();
	void InitShader();

	float mTparam;
	unsigned int mLookUp;
	bool mIsPaused;

	ShaderProgram mShader;

	///////////////// Constants /////////////////
	const string TEXTURE_NAME_1 = "ColorScheme1";

	const string SHADER_NAME = "Bonus2";
};