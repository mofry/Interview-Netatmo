#include <iostream>
#include <vector>


class World {

    int _width;
    int _height;
    std::vector<int> _units; 
    //contigous vector which represents the state of each cell


    public : 

        World();
        World(int width , int height ,double ratio);
        //ratio gives the percentage of chance to get 1
        //I've built two constructors. The second wich allow us to 
        //directly set the status of each cells according to the ratio
        ~World();

        //getters
        int getWidth() const;
        int getHeight() const;
        void getStatus() const;
        const std::vector<int>& getUnits() const;
        std::vector<int> getEnvironment(int) const; 


        void setStatus(int index , int status);
        


};


class Engine {

    public :
        Engine();
        ~Engine();
        
        void compute(World& w , std::vector<int> inactive_to_active_Rules  , std::vector<int> remain_active_Rules);
        //activeUnitsNumber is an array which define the rules for computations
        



};

class Rendering {

    public : 

        Rendering();
        ~Rendering();

        void render(const World&) const;




};






