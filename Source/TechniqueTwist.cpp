#include "TechniqueTwist.h"

#include <iostream>

TechniqueTwist::TechniqueTwist()
	: mTparam(0.f)
{
	InitShader();
}

TechniqueTwist::~TechniqueTwist()
{

}

void TechniqueTwist::PreRender()
{
	//Activate the shader
	mShader.Activate();

	glBindAttribLocation(mShader.ProgramId(), 0, "tparam");

	glVertexAttrib1f(
		glGetAttribLocation(mShader.ProgramId(), "tparam"),
		mTparam
		);
}

void TechniqueTwist::PostRender()
{
	//Deactivate the shader.
	mShader.Deactivate();
}

void TechniqueTwist::ReceiveInput(char aKey)
{
	switch (aKey)
	{
	case 'q':
		mTparam += 0.1;
		break;

	case 'a':
		mTparam -= 0.1;
		break;

	//Reset to default
	case 'r':
		mTparam = 0.f;
		break;

	default:
		break;
	}

	printf("\rtParam: %2.1f     ", mTparam);
}

void TechniqueTwist::InitShader()
{
	//Create shader objects.
	Shader* vertexShader = new Shader(Shader::Shader_Vertex);
	Shader* fragmentShader = new Shader(Shader::Shader_Fragment);

	//Load and compile the source code of shader file.
	if (!vertexShader->CompileSourceFile("Resources/" + SHADER_NAME + ".vx"))
	{
		printf("\nUnable to compile vertex shader source file: %s \n", SHADER_NAME.c_str());
		return;
	}
	//Phong shading source file
	if (!fragmentShader->CompileSourceFile("Resources/FixedPipeline.fg"))
	{
		printf("\nUnable to compile fragment shader source file: %s \n", SHADER_NAME.c_str());
		return;
	}

	//Associate the shaders to the shader program.
	if (!mShader.AddShader(vertexShader, true))
	{
		printf("\nUnable to add vertex shader. \n");
		return;
	}
	if (!mShader.AddShader(fragmentShader, true))
	{
		printf("\nUnable to add fragment shader. \n");
		return;
	}

	//Link the program.
	if (!mShader.Link())
	{
		printf("\nUnable to link shaders. \n");
		return;
	}
}