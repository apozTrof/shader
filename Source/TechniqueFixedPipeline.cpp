#include "TechniqueFixedPipeline.h"

TechniqueFixedPipeline::TechniqueFixedPipeline()
{
	InitShader();
}

TechniqueFixedPipeline::~TechniqueFixedPipeline()
{

}

void TechniqueFixedPipeline::PreRender()
{
	//Activate the shader
	mShader.Activate();
}

void TechniqueFixedPipeline::PostRender()
{
	//Deactivate the shader.
	mShader.Deactivate();
}

void TechniqueFixedPipeline::ReceiveInput(char aKey)
{
	
}

void TechniqueFixedPipeline::InitShader()
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
	if (!fragmentShader->CompileSourceFile("Resources/" + SHADER_NAME + ".fg"))
	{
		printf("\nUnable to compile fragment shader source file: %s \n", SHADER_NAME.c_str());
		return;
	}

	//Associate the shaders to the shader program.
	if (!mShader.AddShader(vertexShader, true))
	{
		printf("\nUnable to add fragment shader. \n");
		printf(mShader.Log().c_str());
		printf("\n");
		return;
	}
	if (!mShader.AddShader(fragmentShader, true))
	{
		printf("\nUnable to add fragment shader. \n");
		printf(mShader.Log().c_str());
		printf("\n");
		return;
	}

	//Link the program.
	if (!mShader.Link())
	{
		printf("\nUnable to link shaders. \n");
		printf(mShader.Log().c_str());
		printf("\n");
		return;
	}
}