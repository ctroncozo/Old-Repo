#include "AnimationClip.h"

AnimationClip::AnimationClip(){}

AnimationClip::~AnimationClip(){}

void AnimationClip::load(char* filename)
{
   Tokenizer tokenizer = *new Tokenizer();
   tokenizer.Open(filename);
   char name[256];
   tokenizer.GetToken(name);
    
	tokenizer.FindToken("{");

   tokenizer.FindToken("range");
   range[0] = tokenizer.GetFloat();
   range[1] = tokenizer.GetFloat();
   
	tokenizer.FindToken("numchannels");
   nunOfchannels = tokenizer.GetInt();
    
   for (int i = 0; i < nunOfchannels; i++)
   {
       Channel *ch = new Channel();
       ch->id = i;
       tokenizer.FindToken("channel {");
       tokenizer.FindToken("extrapolate");
       tokenizer.GetToken(name);
       ch->extrapolate[0] = std::string(name);
       tokenizer.GetToken(name);
       ch->extrapolate[1] = std::string(name);

       tokenizer.FindToken("keys");
       int numKeys = tokenizer.GetInt();
       
		 tokenizer.FindToken("{");
       for (int j = 0; j < numKeys; j++)
       {
           float time = tokenizer.GetFloat();
           float value = tokenizer.GetFloat();
           tokenizer.GetToken(name);
           std::string ri= std::string(name);
           tokenizer.GetToken(name);
           std::string ro = std::string(name);
           KeyFrame *k = new KeyFrame(time, value, ri, ro);
           k->ch = ch;
           ch->frames.push_back(k);
       }
		 ch->precompute();
         channels.push_back(ch);
   }
   tokenizer.Close();
}

void AnimationClip::evaluateTranslation(int idx, float time, Vector3D &pose)
{
    float dofx = channels.at(idx)->evaluate(time);
    float dofy = channels.at(idx+1)->evaluate(time);
    float dofz = channels.at(idx+2)->evaluate(time);
    
    pose = Vector3D(dofx, dofy, dofz);
}

void AnimationClip::evaluate(int jointIdx, float time, Vector3D &pose)
{

    jointIdx = (jointIdx + 1) * 3;
    
    float dofx = channels.at(jointIdx)->evaluate(time);
    float dofy = channels.at(jointIdx+1)->evaluate(time);
    float dofz = channels.at(jointIdx+2)->evaluate(time);
        
		pose = Vector3D(dofx, dofy, dofz);	
}

int AnimationClip::getNumOfChannels()
{
	return nunOfchannels;
}
