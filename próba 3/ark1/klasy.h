#ifndef KLASY_H
#define KLASY_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>

class Textures{
public:
    Textures(std::vector<sf::Texture>&textures_){std::copy(textures_.begin(),textures_.end(),std::back_inserter(textures));}
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
    virtual ~Klocek()= default;
    int max_dmg;
    int dmg;
    int pkty;
    bool usun=false;

    virtual void changeTexture1(Textures &obj)=0;
    virtual void changeTexture2(Textures &obj)=0;

};

class Klocek_bialy : public Klocek{
public:

    Klocek_bialy(){dmg=0; max_dmg = 1; pkty =10;}
    ~Klocek_bialy(){};
    virtual void changeTexture1(Textures &obj) override{};
    virtual void changeTexture2(Textures &obj) override{};
};

class Klocek_fioletowy :public Klocek{
public:

    Klocek_fioletowy(){dmg=0; max_dmg = 2; pkty = 30;}
    ~Klocek_fioletowy(){};
    void changeTexture1(Textures &obj) override{
        auto Ptr = &obj.textures[4];
        if (dmg == max_dmg/2) {setTexture(*Ptr);}
    };
    virtual void changeTexture2(Textures &obj) override{};
};

class Klocek_niebieski :public Klocek{
public:

    Klocek_niebieski(){dmg=0; max_dmg = 4; pkty = 80;}
    ~Klocek_niebieski(){};
    void changeTexture1(Textures &obj) override {
        auto Ptr = &obj.textures[1];
        if (dmg== max_dmg/2) {setTexture(*Ptr);}
    }
    void changeTexture2(Textures &obj) override {
        auto Ptr = &obj.textures[2];
            if (dmg== 3*max_dmg/4) {setTexture(*Ptr);}
        }
};
class Pilka:public AnimatedSprite{
public:
    float velx=2;
    float vely=-2;


    void bounce(Platforma &platforma, std::vector<std::unique_ptr<Klocek>> &w, Textures &obj) {
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
        for(auto &x: w){
                if (   x->getGlobalBounds().intersects(bounds)){
                    //zderzenie od góry
                    if(x->getGlobalBounds().top < getPosition().y && x->getGlobalBounds().left<getPosition().x &&
                       x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x){
                       vely = -std::abs(vely);}
                    //zderzenie od dołu
                    if (x->getGlobalBounds().top + x->getGlobalBounds().height>getPosition().y &&
                        x->getGlobalBounds().left < getPosition().x &&
                        x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x)
                       {vely=std::abs(vely);}
                    //zderzenie od lewej
                    if (x->getGlobalBounds().left < getPosition().x && x->getGlobalBounds().top < getPosition().y &&
                        x->getGlobalBounds().top+x->getGlobalBounds().height > getPosition().y){
                        velx=-std::abs(velx);
                    }
                    //zderzenie od prawej
                    if (x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x &&
                        x->getGlobalBounds().top <getPosition().y &&
                        x->getGlobalBounds().top + x->getGlobalBounds().height > getPosition().y)
                    {velx=std::abs(velx);}
                       x->dmg++;
                       std::cout<<x->dmg<<std::endl;
                       std::cout<<x->usun<<std::endl;
                       if (x->dmg==x->max_dmg) {x->usun = true;}
                       x->changeTexture1(obj);
                       x->changeTexture2(obj);
                }
    }
    }

    void animate(Platforma platforma, std::vector<std::unique_ptr<Klocek>> &w, Textures &obj) {
        move(velx, vely);
        bounce(platforma, w, obj);
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
