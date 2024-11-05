#pragma once

#include <map>
#include <string>

#include "TextureEnumImplementation.h"

namespace chickengame
{
	namespace tiles
	{
		const std::map<int, std::pair<TexturesEnum, bool>> tileDictionary = {
			{1, {TexturesEnum::waterTile, true}},
			{2, {TexturesEnum::dirtTile, false}},
			{3, {TexturesEnum::grassTile, false}},
			{7, {TexturesEnum::grassWaterLeftTile, false}},
			{9, {TexturesEnum::grassWaterRightTile, false}}
		};
	}
}

