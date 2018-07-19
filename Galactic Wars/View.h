#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicsController.h"
#include "AudioController.h"

using namespace std;
using namespace sf;

namespace project
{

	class View
	{
		public:
			virtual void show(); // Objaœnienie w ciele funkcji

		protected: // W przypadku u¿ycia 'private' wyskakuje b³¹d o braku dostêpu
			RenderWindow *window;
			GraphicsController *graphicsController;
			AudioController *audioController;
			GameInfo *gameInfo;
			Font *font;

			bool loadedData;
	};

}
