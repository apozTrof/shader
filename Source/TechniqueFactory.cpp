#include "TechniqueFactory.h"

#include <cstdlib>

#include "TechniqueToon.h"
#include "TechniquePlainColor.h"
#include "TechniqueBarla.h"
#include "TechniqueBonus.h"
#include "TechniqueFixedPipeline.h"
#include "TechniqueMultiTexture.h"
#include "TechniqueTwist.h"
#include "TechniqueBonus2.h"

RenderingTechnique* TechniqueFactory::CreateTechnique(Technique aTech)
{
    switch(aTech)
    {
    case Technique_ToonShader :
        return new TechniqueToon();
    case Technique_BarlaShader :
		return new TechniqueBarla();
    case Technique_PlainColor :
		return new TechniquePlainColor();
    case Technique_FixedPipeline :
		return new TechniqueFixedPipeline();
    case Technique_Twist :
		return new TechniqueTwist();
    case Technique_MultiTexture :
		return new TechniqueMultiTexture();
    case Technique_Bonus :
		return new TechniqueBonus();
	case Technique_Bonus2 :
		return new TechniqueBonus2();
    default:
        return NULL;
    }
}