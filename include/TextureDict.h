#pragma once

#include <map>
#include <string>
namespace chickengame
{
	namespace tiles
	{
		const std::map<int, std::pair<std::string, bool>> tileDictionary = {
			{1, {"assets/water.png", true}},
			{2, {"assets/dirt.png", false}},
			{3, {"assets/grass.png", false}},
			{7, {"assets/grass_water_left.png", false}},
			{9, {"assets/grass_water_right.png", false}}
		};
	}
}

