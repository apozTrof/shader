#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"
#include "Vector3.h"

class TechniquePlainColor : public RenderingTechnique
{
public:

	TechniquePlainColor();
	virtual ~TechniquePlainColor();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

protected:
	void InitColor();
	void InitShader();

	unsigned int mCurrentColorID;
	Vector3 mColors[5];

	ShaderProgram mShader;


	///////////////// Constants /////////////////
	const Vector3 Red = Vector3(1.f, 0.f, 0.f);
	const Vector3 Green = Vector3(0.f, 1.f, 0.f);
	const Vector3 Blue = Vector3(0.f, 0.f, 1.f);
	const Vector3 White = Vector3(1.f, 1.f, 1.f);
	const Vector3 Black = Vector3(0.f, 0.f, 0.f);

	const string SHADER_NAME = "PlainColor";
};