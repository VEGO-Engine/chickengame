#pragma once

#include <map>
#include <string>

#include "TextureEnumImplementation.h"

namespace chickengame
{
	namespace tiles
	{
		const std::map<int, std::pair<Textures, bool>> tileDictionary = {
			{1, {Textures::waterTile, true}},
			{2, {Textures::dirtTile, false}},
			{3, {Textures::grassTile, false}},
			{7, {Textures::grassWaterLeftTile, false}},
			{9, {Textures::grassWaterRightTile, false}}
		};
	}
}

