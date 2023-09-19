#include <iostream>

#include <SFML/Graphics.hpp>
#include <list>
using namespace std;
#pragma once

class Light {
public:
    float Power;
    float Range;
    sf::Vector2<int> Pos;
    // LightEnviro LightEnviroment;
    Light(float P, float R, sf::Vector2<int> Posit, LightEnviro& env) {
        Power = P;
        Range = R;
        Pos = Posit;

        env.LightsInScene.push_back(*this);
    }
};

