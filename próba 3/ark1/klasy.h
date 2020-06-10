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


class Klocek :public sf::Sprite{
public:

    int max_dmg;
    int dmg;
    int pkty;
    bool usun=false;

    virtual void changeTexture1(std::vector<sf::Texture> w)=0;
    virtual void changeTexture2(std::vector<sf::Texture> w)=0;

};

class Klocek_bialy : public Klocek{
public:

    Klocek_bialy(){dmg=0; max_dmg = 1; pkty =10;}
    virtual void changeTexture1(std::vector<sf::Texture> w) override;
    virtual void changeTexture2(std::vector<sf::Texture> w) override;
};

class Klocek_fioletowy :public Klocek{
public:

    Klocek_fioletowy(){dmg=0; max_dmg = 2; pkty = 30;}
    void changeTexture1(std::vector<sf::Texture> w) override{
        if (dmg == max_dmg/2) {setTexture(w[4]);}
    };
    virtual void changeTexture2(std::vector<sf::Texture> w) override;
};

class Klocek_niebieski :public Klocek{
public:

    Klocek_niebieski(){dmg=0; max_dmg = 4; pkty = 80;}
    void changeTexture1(std::vector<sf::Texture> w) override {
        if (dmg== max_dmg/2) {setTexture(w[1]);}
    }
    void changeTexture2(std::vector<sf::Texture> w) override {
            if (dmg== 3*max_dmg/4) {setTexture(w[2]);}
        }
};
class Pilka:public AnimatedSprite{
public:
    float velx=2;
    float vely=-2;


    void bounce(Platforma &platforma, std::vector<Klocek*> w, std::vector<sf::Texture> w2 ) {
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
        for (auto x: w)
        if (getGlobalBounds().intersects(x->getGlobalBounds())){
               vely = -std::abs(vely);
               x->dmg++;
               std::cout<<x->dmg<<std::endl;
               std::cout<<x->usun<<std::endl;
               if (x->dmg==x->max_dmg) {x->usun = true;}
               x->changeTexture1(w2);
               x->changeTexture2(w2);
            }
    }

    void animate(Platforma platforma, std::vector<Klocek*> w, std::vector<sf::Texture> w2 ) {
        move(velx, vely);
        bounce(platforma, w, w2);



        }
    void setSpeed(float velocity_x, float velocity_y) {
        velx = velocity_x;
        vely = velocity_y;

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
