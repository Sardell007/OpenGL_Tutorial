#pragma once
#include<vector>

class Light {
private:
	std::vector<float> position;
	std::vector<float> colour;
public:
	Light(std::vector<float> positioni, std::vector<float> colouri);
	inline std::vector<float> getPosition() { return position; };
	inline std::vector<float> getColour() { return colour; };
};