#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

class TechniqueTwist : public RenderingTechnique
{

public:
	TechniqueTwist();
	virtual ~TechniqueTwist();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

protected:
	void InitShader();

	float mTparam;

	ShaderProgram mShader;

	const string SHADER_NAME = "Twist";
};