#include "TechniqueToon.h"

#include "Image.h"
#include "BitmapHandling.h"
#include "TextureHandling.h"

TechniqueToon::TechniqueToon()
:   mCurrentLookup(0)
{
    InitTextures();
    InitShader();
}

//////////////////////////////////////////////////////////////////////////

void TechniqueToon::PreRender()
{   
    //Activate the shader
    mShader.Activate();

    //Set the current texture stage to 0 and load the
    //current lookup texture into it.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mLookups[mCurrentLookup]);

    //Tell the shader that the look has been loaded in
    //texture stage 0.
    glUniform1i(
        glGetUniformLocation(mShader.ProgramId(),"LookupSampler"),
        0);

}

//////////////////////////////////////////////////////////////////////////

void TechniqueToon::PostRender()
{
    //Deactivate the shader.
    mShader.Deactivate();

    //Unload the texture from texture stage 0.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,NULL);
}

//////////////////////////////////////////////////////////////////////////

void TechniqueToon::ReceiveInput(char aKey)
{
    //Change the current lookup texture if the user
    //presses keys 1, 2 or 3 on the keyboard.
    switch(aKey)
    {
    case '1':
        mCurrentLookup = 0;
        break;
    case '2' :
        mCurrentLookup = 1;
        break;
    case '3' :
        mCurrentLookup = 2;
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////////////////////////////////

void TechniqueToon::InitTextures()
{
    Image<ColorRGB> TmpImage;

    //Load the color scheme #1 image and send it to the GPU as a texture.
    LoadBmp("Resources/ToonScheme1.bmp",TmpImage);
    mLookups[0] = LoadTexture(TmpImage);

    //Load the color scheme #2 image and send it to the GPU as a texture.
    LoadBmp("Resources/ToonScheme2.bmp",TmpImage);
    mLookups[1] = LoadTexture(TmpImage);

    //Load the color scheme #3 image and send it to the GPU as a texture.
    LoadBmp("Resources/ToonScheme3.bmp",TmpImage);
    mLookups[2] = LoadTexture(TmpImage);
}

//////////////////////////////////////////////////////////////////////////

void TechniqueToon::InitShader()
{
    //Create two shader objects.
    Shader* VertexShader    = new Shader(Shader::Shader_Vertex);
    Shader* FragmentShader  = new Shader(Shader::Shader_Fragment);

    //Load and compile the source code for each shader.
    VertexShader->CompileSourceFile("Resources/Toon.vx");
    FragmentShader->CompileSourceFile("Resources/Toon.fg");

    //Associate the shaders to our Toon shader program.
    mShader.AddShader(VertexShader,true);
    mShader.AddShader(FragmentShader,true);

    //Link the program.
    mShader.Link();
}

//////////////////////////////////////////////////////////////////////////


TechniqueToon::~TechniqueToon()
{
    //Delete the color schemes loaded during
    //initialization.
    FreeTexture(mLookups[0]);
    FreeTexture(mLookups[1]);
    FreeTexture(mLookups[2]);
}
