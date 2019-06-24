#ifndef ANIMATION_H
#define ANIMATION_H

#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;    
	Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying=true;
		flip=false;
		loop=true;
	}
	int getFrames() const{
		return frames.size();
	}
	
	void tick(const float& time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;
		
		if (currentFrame > frames.size()) { currentFrame -= frames.size();
		                                    if (!loop) {isPlaying=false; return;}
		                                  }

		int i = currentFrame;
		sprite.setTextureRect( frames[i] );
		if (flip) sprite.setTextureRect( frames_flip[i] );
	}

};



class AnimationManager
{

public:
    std::string currentAnim;
	std::map<std::string, Animation> animList;

	AnimationManager()
	{}

	~AnimationManager()
	{ animList.clear();
	}
	
  
	//loop =false if its dont conect to player
	void create(std::string& name, Texture &texture, int& x, int& y, int& w, int& h, int& count, float& speed, int step=0, bool Loop=true)
	{
		Animation a;
		a.speed = speed;
		a.loop = Loop;
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(0,h);
		///////////////////////////////////////////
		////create animation like walk and lump////
		///  image                            ////
		for (int i=0;i<count;i++)
		{
			a.frames.push_back( IntRect(x+i*step, y, w, h)  );
			a.frames_flip.push_back( IntRect(x+i*step+w, y, -w, h)  );
		}
		animList[name] = a;
		currentAnim = name;
	}

	//
	bool loadFromXML(const std::string& fileName,Texture &t,const sf::Vector2f&a)
	{
		TiXmlDocument animFile(fileName.c_str());

		if(!animFile.LoadFile())return false;

		TiXmlElement *head;
		head = animFile.FirstChildElement("sprites");

		TiXmlElement *animElement;
		animElement = head->FirstChildElement("animation");
		while(animElement)
		{
			Animation anim;
			anim.sprite.scale(a);
			currentAnim = animElement->Attribute("title");
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = 1.0/delay; anim.sprite.setTexture(t);

			TiXmlElement *cut;
			cut = animElement->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));

				anim.frames.push_back( IntRect(x,y,w,h) );
				anim.frames_flip.push_back( IntRect(x+w,y,-w,h)  );
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0,anim.frames[0].height);

			animList[currentAnim] = anim;
			animElement = animElement->NextSiblingElement("animation");
		}
		return true;
	}

	void set(const std::string& name)
	{
		currentAnim = name;
		animList[currentAnim].flip=0;
	}

	void draw(RenderWindow &window,int x=0, int y=0)
	{
		animList[currentAnim].sprite.setPosition(x,y);
		window.draw( animList[currentAnim].sprite );
	}

	void flip(bool b=1) {animList[currentAnim].flip = b;}

	void tick(const float& time)	 {animList[currentAnim].tick(time);}

	void pause() {animList[currentAnim].isPlaying=false;}

	void play()  {animList[currentAnim].isPlaying=true;}

	void play(const std::string& name)  {animList[name].isPlaying=true;}

	bool isPlaying()  {return animList[currentAnim].isPlaying;}

	float getH()  {return float (animList[currentAnim].frames[0].height);}

	float getW() {return float( animList[currentAnim].frames[0].width);}

};

#endif ANIMATION_H
