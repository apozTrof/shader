#include "TechniqueMultiTexture.h"

#include "Image.h"
#include "BitmapHandling.h"
#include "TextureHandling.h"

TechniqueMultiTexture::TechniqueMultiTexture()
	: mCurrentLookUp(0)
{
	InitTextures();
	InitShader();
}

TechniqueMultiTexture::~TechniqueMultiTexture()
{
	FreeTexture(mLookUps[0]);
	FreeTexture(mLookUps[1]);
	FreeTexture(mLookUps[2]);
}

void TechniqueMultiTexture::PreRender()
{
	//Activate the shader
	mShader.Activate();
	
	//Set the texture stages and load the lookup textures into it.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mLookUps[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mLookUps[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mLookUps[2]);

	//Tell the shader that the look has been loaded in
	//texture stage 0.
	glUniform1i(
		glGetUniformLocation(mShader.ProgramId(), "TextureDay"),
		0); 
	glUniform1i(
		glGetUniformLocation(mShader.ProgramId(), "TextureNight"),
		1);
	glUniform1i(
		glGetUniformLocation(mShader.ProgramId(), "MaskSpec"),
		2);
}

void TechniqueMultiTexture::PostRender()
{
	//Deactivate the shader.
	mShader.Deactivate();

	//Unload textures from texture stages.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, NULL);	
}

void TechniqueMultiTexture::ReceiveInput(char aKey)
{

}

void TechniqueMultiTexture::InitTextures()
{
	Image<ColorRGB> tmpImage;

	//Load the color scheme #1 image and send it to the GPU as a texture.
	LoadBmp("Resources/" + TEXTURE_NAME_1 + ".bmp", tmpImage);
	mLookUps[0] = LoadTexture(tmpImage);

	//Load the color scheme #2 image and send it to the GPU as a texture.
	LoadBmp("Resources/" + TEXTURE_NAME_2 + ".bmp", tmpImage);
	mLookUps[1] = LoadTexture(tmpImage);

	//Load the color scheme #3 image and send it to the GPU as a texture.
	LoadBmp("Resources/" + TEXTURE_NAME_3 + ".bmp", tmpImage);
	mLookUps[2] = LoadTexture(tmpImage);
}

void TechniqueMultiTexture::InitShader()
{
	//Create two shader objects.
	Shader* vertexShader = new Shader(Shader::Shader_Vertex);
	Shader* fragmentShader = new Shader(Shader::Shader_Fragment);

	//Load and compile the source code for each shader.
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
		printf("\nUnable to add Vertex shader. \n");
		return;
	}
	if (!mShader.AddShader(fragmentShader, true))
	{
		printf("\nUnable to add Fragment shader. \n");
		return;
	}

	//Link the program.
	if (!mShader.Link())
	{
		printf("Unable to link shader. \n");
		return;
	}
}