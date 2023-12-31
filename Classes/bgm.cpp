#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

auto audio = SimpleAudioEngine::getInstance();

audio->playBackgroundMusic("BGMusic.mp3", true);