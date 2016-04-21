#include "TechniqueBonus2.h"

#include "Image.h"
#include "BitmapHandling.h"
#include "TextureHandling.h"

TechniqueBonus2::TechniqueBonus2()
	: mTparam(0.f), mIsPaused(false)
{
	InitTextures();
	InitShader();
}

TechniqueBonus2::~TechniqueBonus2()
{
	FreeTexture(mLookUp);
}

void TechniqueBonus2::PreRender()
{
	//Activate the shader
	mShader.Activate();

	//Set the texture stages and load the lookup textures into it.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mLookUp);

	glUniform1i(
		glGetUniformLocation(mShader.ProgramId(), "Texture"),
		0);

	glBindFragDataLocation(mShader.ProgramId(), 0, "Time");

	if (!mIsPaused)
		mTparam++;

	glUniform1f(
		glGetUniformLocation(mShader.ProgramId(), "Time"),
		mTparam / 30.f
		);
}

void TechniqueBonus2::PostRender()
{
	//Deactivate the shader.
	mShader.Deactivate();

	//Unload textures from texture stages.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void TechniqueBonus2::ReceiveInput(char aKey)
{
	switch (aKey)
	{
	case 'p':
		mIsPaused = !mIsPaused;
		break;
		
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

void TechniqueBonus2::InitTextures()
{
	Image<ColorRGB> tmpImage;

	//Load the color scheme #1 image and send it to the GPU as a texture.
	LoadBmp("Resources/" + TEXTURE_NAME_1 + ".bmp", tmpImage);
	mLookUp = LoadTexture(tmpImage);
}

void TechniqueBonus2::InitShader()
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
	//Phong shading source fileResources/" + SHADER_NAME + ".vx"
	if (!fragmentShader->CompileSourceFile("Resources/" + SHADER_NAME + ".fg"))
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