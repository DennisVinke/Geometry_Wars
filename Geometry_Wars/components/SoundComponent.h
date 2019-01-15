#pragma once

#include "engine/Component.h"



class SoundManager;




class SoundComponent : public Component
{

public:


    SoundComponent(SoundManager& sound_manager);



private:
    
    SoundManager& sound_manager;


};
