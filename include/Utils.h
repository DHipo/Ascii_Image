#pragma once
#include "SDL2/SDL.h"
#include <map>
#include <vector>
#include <map>

#define LOG(x) std::cout << x << std::endl;
#define LOG_ERROR(x) std::cout << "--> ERROR : " << x << std::endl;
#define LOG_ARR(arr) for(auto e : arr) std::cout << e.data() << std::endl;

#define DEBUG_MODE 1

namespace Utils {

	enum KeyBoard_Numbers
	{
		K_ONE = 49,
		K_TWO,
		K_THREE,
		K_FOUR,
	};

	inline struct Color
	{
		SDL_Color red = {255, 0, 0, 255};
		SDL_Color green = {0, 255, 0, 255};
		SDL_Color blue = {0, 0, 255, 255};
		SDL_Color black = {0, 0, 0, 255};
		SDL_Color gray = {125, 125, 125, 255};
		SDL_Color brown = {100, 50, 50, 255};
		SDL_Color yellow = {200, 200, 0, 255};
	} SColor;

	struct TimeInter {
		Uint32 t_start, t_end, p_start, p_end;
		Uint32 t_elapsed, p_elapsed;
		double deltaTime;
	};

	struct Vec2 {
		int x, y;
	};

	struct FVec2 {
		float x, y;
	};

	struct MouseInfo
	{
		Vec2 pos;
		Uint8 clicks;
		Uint8 button;
		Uint8 state;
	};

	inline bool checkPointInsideOfRect(const SDL_Rect _rect1, const Vec2 _point)
	{
		return (_point.x > _rect1.x && _point.x < _rect1.x + _rect1.w &&
				_point.y > _rect1.y && _point.y < _rect1.y + _rect1.h);
	};

	template <typename T>
	inline void swap(T &_e1, T &_e2)
	{
		T temp = _e1;
		_e1 = _e2;
		_e2 = temp;
	}

	inline SDL_Texture *GetAreaTexture(const SDL_Rect _rect, SDL_Renderer *_renderer, SDL_Texture *_source)
	{
		SDL_Texture *result = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
		SDL_SetRenderTarget(_renderer, result);
		SDL_RenderCopy(_renderer, _source, &_rect, NULL);
		// the folowing line should reset the target to default(the screen)
		SDL_SetRenderTarget(_renderer, NULL);
		// I also removed the RenderPresent funcion as it is not needed here
		return result;
	}

	inline long map_value(long x, long in_min, long in_max, long out_min, long out_max) {
  		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	template<typename T = int>
	inline T max(T _arg1, T _arg2, T _arg3) 
	{
		T maxNumber = _arg1;
		if (_arg2 > maxNumber) maxNumber = _arg2;
		if (_arg3 > maxNumber) maxNumber = _arg3;
		return maxNumber;
	}

	inline int promedio(std::vector<int> _args)
	{
		int result = 0;
		for (int arg : _args)
			result += arg;
		return int(result/_args.size());
	}
};