// SFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>
#include <random>
#include <list>
#include <string>
#include <filesystem>


using namespace std;
class Light {
public:
    float Power;
    float Range;
    sf::Vector2i Pos;
   
    Light(float P, float R, sf::Vector2i Posit) {
        Power = P;
        Range = R;
        Pos = Posit;
       
    }
};

class LightEnviro {
public:
    std::vector<reference_wrapper<Light>> LightsInScene;

};
class LightablePixel {
public:
    sf::Vector2<float> Scale;
    sf::Vector2<float> Pos;
    sf::Color Colour;
    float LightAmount = 0;
public:
    LightablePixel(sf::Vector2<float> P, sf::Vector2<float> S, sf::Color C) {
        Pos = P;
        Scale = S;
        Colour = C;
    }
    sf::RectangleShape RenderMe(LightEnviro& Env) {
        sf::RectangleShape s;
        s.setSize(Scale);
        s.setPosition(Pos);
        LightAmount = 0;
        //Get the lighting
        for (size_t i = 0; i < Env.LightsInScene.size(); i++)
        {

            //Distance Gotten
            float Distance = (abs(Pos.x - Env.LightsInScene.at(i).get().Pos.x) + abs(Pos.y - Env.LightsInScene.at(i).get().Pos.y));
            if (Distance == 0) {
                Distance = 1;
            }
            float PwrApplied = Env.LightsInScene.at(i).get().Range / Distance;
            if (PwrApplied > 1) {
                PwrApplied = 1;
            }
            LightAmount += Env.LightsInScene.at(i).get().Power * PwrApplied;
            
            
        }
        int TotalColor = Colour.r + Colour.b + Colour.g;
        
        
        float ColorMod = LightAmount / TotalColor;
        Colour = sf::Color(Colour.r * ColorMod, Colour.g * ColorMod, Colour.b * ColorMod);
        s.setFillColor(Colour);
        return s;
    }
};


class Shape2D {
public:
    sf::Vector2<float> Pos;
    sf::Vector2<int> Scale;
    
    sf::Color Color;
    Shape2D(sf::Vector2<int> s, sf::Vector2<float> P, sf::Color c) {
        Color = c;
        Pos = P;
        Scale = s;
    }
    void RenderMe(sf::RenderWindow& wind, LightEnviro& Env) {
       
        
        for (size_t x = 0; x < Scale.x; x++)
        {
            for (size_t y = 0; y < Scale.y; y++)
            {
                LightablePixel p(sf::Vector2<float>(Pos.x+x, Pos.y+y), sf::Vector2<float>(1, 1), Color);
                wind.draw(p.RenderMe(Env));
            }
            
          
        }
        
    }

};
class Border {
public:
    std::vector<sf::Vector2f> Verticies;
   
    
   
};







class Province;
class Feature;
class Terrain;
class Unit;
class Selectable {
public:
    float SelectDist;
    bool IsSelected;
    sf::Vector2f Position;
    void OnLClick() {

    }
    void OnRClick() {

    }
   
};
class GameManager {
public:
    bool IsRunningDebug;    
    int Year, Month, Day;
    sf::Texture GameMap;
    vector<Selectable> Selectables;
    vector<Province> GameProvinces;
    void Tick() {
        //Advance Time
        Day += 1;
        if (Day > 30) {
            Day = 1;
            Month += 1;
            if (Month > 12) {
                Month = 0;
                Year += 1;
            }
        }
    }

};
/// <summary>
/// A very primitive nation, all it will be used for is owning provinces, other logic will be game-specific
/// </summary>
class Nation: public Selectable {
    vector<Province> ContainedProvs;
    void OnMonthTick() {

    }
    void OnDayTick() {

    }
    void OnYearTick() {

    }
    void OnRClick() {
        
    }
};
class Terrain {
    sf::Image Picture;

};
class Feature {
public:
   
    sf::Texture MapIcon;
    sf::Image MenuIcon;
    std::string Name;

    void OnMonthTick(Province& ProvIn) {

    }
    void OnDayTick(Province& ProvIn) {

    }
    void OnYearTick(Province& ProvIn) {

    }



};
#include <unordered_map>
class Province: public Selectable {
public:

    //Higher Data (The Player Can Directly See this)
    Terrain terra;
    std::vector<reference_wrapper<Feature>> Features;
    Nation Owner;
    //Middling Data (Internally stored, externally displayed, so its not immediatly obvious)
    std::vector<Province> Adjacencies;
    //Low Data
    std::unordered_map < std::string , sf::Vector2f > FeaturePlacements;
    sf::Vector2f UnitPlacement;
    sf::Vector2f Position;


    
    void OnMonthTick() {

    }
    void OnDayTick() {

    }
    void OnYearTick() {

    }
    void RenderFeatures(sf::RenderWindow& Renderer);
          
      
};


class Unit{
    Province provIn;
    void OnMonthTick() {

    }
    void OnDayTick() {

    }
    void OnYearTick() {

    }
    void OnSelect() {

    }
    void OnMoveProv() {

    }
};





inline void Province::RenderFeatures(sf::RenderWindow& Renderer) {
    for (Feature& feature : Features) {
        sf::Sprite FeatureDecor;
        FeatureDecor.setTexture(feature.MapIcon);
        FeatureDecor.setPosition(Position + FeaturePlacements[feature.Name]);
        Renderer.draw(FeatureDecor);
    }
}




int main()
{
   
    
    sf::View Camera;
   
        //Prepare
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Proj");
        sf::Sprite WorldMap;
        GameManager manager;
        manager.GameMap.loadFromFile("./Debug/Circ.png");
        WorldMap.setScale(sf::Vector2f(5, 5));
        WorldMap.setTexture(manager.GameMap);
        



        //Test Setup
        Province TestProv;
        TestProv.Position = sf::Vector2f(40, 40);
        Feature TestHouse;
        TestHouse.MapIcon.loadFromFile("./Testhouse.png");
        
        TestProv.FeaturePlacements[TestHouse.Name] = sf::Vector2f(3, 3);
        TestProv.Features.emplace_back(TestHouse);
        manager.Selectables.emplace_back(TestProv);
        manager.GameProvinces.emplace_back(TestProv);
        manager.IsRunningDebug = true;
        
       
        

      


       
   
             

        while (window.isOpen())
        {
            
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            window.clear();
            window.draw(WorldMap);
            manager.Tick();
            for (Province& prov : manager.GameProvinces)
            {
                prov.RenderFeatures(window);
                if (manager.IsRunningDebug) {
                    sf::CircleShape dot(1.f);
                    dot.setPosition(prov.Position);
                    window.draw(dot);
                }
            }
          
           
            window.display();
        }

        return 0;
        
   
    
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
