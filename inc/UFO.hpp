#pragma once
#include <SpaceObject.hpp>

namespace mt
{
	class UFO : public SpaceObject
	{
	public:
		UFO() = default;
		virtual ~UFO() {}

		void Attack() override
		{
			std::cout << "UFO Attack" << std::endl;
		}

		void SpecialAbility() override
		{
			std::cout << "HFO Special Ability" << std::endl;
		}
	};
}