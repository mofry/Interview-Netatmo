#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <thread>

#include "technical_test.hpp"

std::random_device rd; 
std::mt19937 gen(rd());

World::World() : _width(5) , _height(2) , _units(10){}

World::World(int width , int height , double ratio) : _width(width), _height(height) , _units(_width * _height){

    if (ratio<0.0 || ratio >1.0) {
        throw std::invalid_argument("ratio must be between 0.0 and 1.0");

    }
    std::bernoulli_distribution b(ratio);

    for( auto& i : _units) {

        i = b(gen);

    }
}

World::~World(){}

int World::getWidth() const {

    return _width;
}


int World::getHeight() const {

    return _height;
}


const std::vector<int>& World::getUnits() const {
    return _units;
}

void World::getStatus() const {

    for(auto& i : _units) std::cout<<i;

    std::cout << std::endl;

}

std::vector<int> World::getEnvironment(int index) const {

    std::vector<int> env;
    int size = _units.size();
    if (index < 0 || index >= size) {
        throw std::out_of_range("cell index is outside the world");
    }

    const int row = index / _width;
    const int column = index % _width;
    env.reserve(8);

    if (column > 0) {
        env.push_back(_units[index - 1]);
    }
    if (column + 1 < _width) {
        env.push_back(_units[index + 1]);
    }
    if (row > 0) {
        env.push_back(_units[index - _width]);
        if (column > 0) {
            env.push_back(_units[index - _width - 1]);
        }
        if (column + 1 < _width) {
            env.push_back(_units[index - _width + 1]);
        }
    }
    if (row + 1 < _height) {
        env.push_back(_units[index + _width]);
        if (column > 0) {
            env.push_back(_units[index + _width - 1]);
        }
        if (column + 1 < _width) {
            env.push_back(_units[index + _width + 1]);
        }
    }

    return env;

}

void World::setStatus(int index , int status) {

    _units[index] = status;

}



////Class Engine

Engine::Engine(){}

Engine::~Engine(){}
        
void Engine::compute(World& w , std::vector<int> inactive_to_active_Rules  , std::vector<int> remain_active_Rules) {

//parcourir chaque cellule.
//Voir environnement de chaque cellule
//avoir un compteur de 1

    World temp = w; 
    const std::vector<int> units = temp.getUnits();
    int size = static_cast<int>(units.size());

    for(int i = 0 ; i < size ; i++) {
        std::vector<int> env = temp.getEnvironment(i);
        int count_ones = std::count(env.begin(), env.end(), 1);

        if (units[i] == 0 ) {
            
            if (std::find(inactive_to_active_Rules.begin(), inactive_to_active_Rules.end(), count_ones) != inactive_to_active_Rules.end()) {
                    w.setStatus(i , 1 );
                } 
        } else {

            if (std::find(remain_active_Rules.begin(), remain_active_Rules.end(), count_ones) == remain_active_Rules.end()) {
                    w.setStatus(i , 0 );
                } 
        

        }




    }


}



////RENDERING


Rendering::Rendering(){}
Rendering::~Rendering(){}

 void Rendering::render(const World& w) const {


    std::cout << "\033[2J" << "\033[1;1H";

    const std::vector<int>& units = w.getUnits();
    std::size_t size = units.size();

    for(std::size_t i = 0 ; i < size ; i++) {



            
        if(units[i] == 1) {
            std::cout << 'O';
        } else {std::cout << ' ';}
        
        if(!((i+1) % w.getWidth()) ){
            std::cout << std::endl;
        }  
          
    }
    

 }















int main() {
   
    const int width = 30;
    const int height = 15;
    const double ratio = 0.8;

    const std::vector<int> inactive_to_active_Rules = {3, 6, 7, 8};
    const std::vector<int> remain_active_Rules = {3, 4, 6, 7, 8};

    World w(width, height, ratio);
    Engine engine;
    Rendering r;

    const int iterations = 50;

    // 2. Render initial state
    r.render(w);
    std::cout << "Iteration: 0 (Initial state)" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 3. Run simulation loop
    for (int step = 1; step <= iterations; ++step) {
        engine.compute(w, inactive_to_active_Rules, remain_active_Rules);

        r.render(w);
        std::cout << "Iteration: " << step << " / " << iterations << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    return 0;
}