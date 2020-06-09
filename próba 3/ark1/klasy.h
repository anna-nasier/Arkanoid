#ifndef KLASY_H
#define KLASY_H

#include <SFML/Graphics.hpp>
#include<iostream>

class NapisTextures{
public:
    NapisTextures(std::vector<sf::Texture>&textures_){std::copy(textures_.begin(),textures_.end(),std::back_inserter(textures));}
    std::vector<sf::Texture>textures;
};

class AnimatedSprite:public sf::Sprite{
protected:
   const int bound_left = 405;
   const int bound_right= 1265;
   const int bound_top =15;
   const int bound_bot = 720;

};




class Platforma:public AnimatedSprite{
public:
    void bounce() {
        auto bounds = getGlobalBounds();
        if (bounds.left < bound_left) {
            setPosition(bound_left,700);
        }
        if (bounds.left + bounds.width > bound_right) {
            setPosition(bound_right -  bounds.width,700);
        }
    }
    void animate(sf::RenderWindow &window){
        auto pozycja= sf::Mouse::getPosition(window).x;
        //std::cout << pozycja<<std::endl;
        setPosition(pozycja,700);

  }

};
class Pilka:public AnimatedSprite{
public:
    float velx=2;
    float vely=-2;


    void bounce(Platforma &platforma) {
        auto bounds = getGlobalBounds();
        if (bounds.left < bound_left) {
            velx = std::abs(velx);
        }
        if (bounds.left + bounds.width > bound_right) {
            velx = -std::abs(velx);
        }
        if (bounds.top < bound_top) {
            vely = std::abs(vely);
        }
        if (platforma.getGlobalBounds().intersects(bounds)){
            vely = -std::abs(vely);
        }

    }

    void animate(Platforma platforma) {
        move(velx, vely);
        bounce(platforma);



        }
    void setSpeed(float velocity_x, float velocity_y) {
        velx = velocity_x;
        vely = velocity_y;

    }

};




class Klocek :public sf::Sprite{
public:

    int max_dmg;
    int dmg=0;
    int pkty;
    bool usun=false;

    void collision(Pilka pilka, std::vector<sf::Texture> w) {
        if (getGlobalBounds().intersects(pilka.getGlobalBounds())){
           pilka.vely = std::abs(pilka.vely);
           dmg++;
           if (dmg==max_dmg) {usun = true;}
           changeTexture1(w);
           changeTexture2(w);
        }
    };

    virtual void changeTexture1(std::vector<sf::Texture> w)=0;
    virtual void changeTexture2(std::vector<sf::Texture> w)=0;

};

class Klocek_bialy : public Klocek{
public:

    Klocek_bialy(){max_dmg = 1; pkty =10;}
    virtual void changeTexture1(std::vector<sf::Texture> w) override;
    virtual void changeTexture2(std::vector<sf::Texture> w) override;
};

class Klocek_fioletowy :public Klocek{
public:

    Klocek_fioletowy(){max_dmg = 2; pkty = 30;}
    void changeTexture1(std::vector<sf::Texture> w) override{
        if (dmg == max_dmg/2) {setTexture(w[4]);}
    };
    virtual void changeTexture2(std::vector<sf::Texture> w) override;
};

class Klocek_niebieski :public Klocek{
public:

    Klocek_niebieski(){max_dmg = 4; pkty = 80;}
    void changeTexture1(std::vector<sf::Texture> w) override {
        if (dmg== max_dmg/2) {setTexture(w[1]);}
    }
    void changeTexture2(std::vector<sf::Texture> w) override {
            if (dmg== 3*max_dmg/4) {setTexture(w[2]);}
        }
};

/*
class Klocek_niespodzianka:public Klocek {

    virtual void changeTexture2(std::vector<sf::Texture> w) override;


};

class Klocek_cegla : public sf::Sprite{

};

*/



#endif // KLASY_H
