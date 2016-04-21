#include "TechniquePlainColor.h"


TechniquePlainColor::TechniquePlainColor()
	: mCurrentColorID(0)
{
	InitShader();
	InitColor();
}

TechniquePlainColor::~TechniquePlainColor()
{

}

void TechniquePlainColor::PreRender()
{
	//Activate the shader
	mShader.Activate();

	glBindFragDataLocation(mShader.ProgramId(), mCurrentColorID, "FragmentColor");

	//Add fragment color
	glUniform4f(
		glGetUniformLocation(mShader.ProgramId(), "FragmentColor"),
		mColors[mCurrentColorID].X(), mColors[mCurrentColorID].Y(), mColors[mCurrentColorID].Z(), 1.0
		);
}

void TechniquePlainColor::PostRender()
{
	//Deactivate the shader.
	mShader.Deactivate();
}

void TechniquePlainColor::ReceiveInput(char aKey)
{
	//Change the current plain color.
	switch (aKey)
	{
	case '1':	//100% Red
		mCurrentColorID = 0;
		break;

	case '2':	//100% Green
		mCurrentColorID = 1;
		break;

	case '3':	//100% Blue
		mCurrentColorID = 2;
		break;

	case '4':	//100% White
		mCurrentColorID = 3;
		break;

	case '5':	//100% Black
		mCurrentColorID = 4;
		break;

	default:
		break;
	}
}

void TechniquePlainColor::InitColor()
{
	//Note: All colors are set to 100% opacity (alpha = 1.0)

	mColors[0] = Red;
	mColors[1] = Green;
	mColors[2] = Blue;
	mColors[3] = White;
	mColors[4] = Black;
}

void TechniquePlainColor::InitShader()
{
	//Create shader objects.
	Shader* vertexShader = new Shader(Shader::Shader_Vertex);
	Shader* fragmentShader = new Shader(Shader::Shader_Fragment);

	//Load and compile the source code of shader file.
	if (!vertexShader->CompileSourceFile("Resources/" + SHADER_NAME + ".vx"))
	{
		printf("\nUnable to compile vertex shader source file: %s \n", SHADER_NAME.c_str());
		printf(mShader.Log().c_str());
		printf("\n");
		return;
	}
	if (!fragmentShader->CompileSourceFile("Resources/" + SHADER_NAME + ".fg"))
	{
		printf("\nUnable to compile fragment shader source file: %s \n", SHADER_NAME.c_str());
		printf(mShader.Log().c_str());
		printf("\n");
		return;
	}

	//Associate the shaders to the shader program.
	if (!mShader.AddShader(vertexShader, true))
	{
		printf("\nUnable to add vertex shader. \n");
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