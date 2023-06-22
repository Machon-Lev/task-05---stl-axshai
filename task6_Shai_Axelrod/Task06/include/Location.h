#pragma once
struct Location
{
	float x;
	float y;

	bool operator<(const Location& loc2) const
	{
		return this->y < loc2.y;
	}
};