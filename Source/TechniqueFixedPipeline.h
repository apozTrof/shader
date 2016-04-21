#pragma once

#include "RenderingTechnique.h"
#include "ShaderProgram.h"

class TechniqueFixedPipeline : public RenderingTechnique
{
public:
	TechniqueFixedPipeline();
	virtual ~TechniqueFixedPipeline();

	virtual void PreRender();
	virtual void PostRender();
	virtual void ReceiveInput(char aKey);

protected:
	void InitShader();

	ShaderProgram mShader;

	const string SHADER_NAME = "FixedPipeline";

};