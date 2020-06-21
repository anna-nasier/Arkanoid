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

    Klocek_bialy(Textures &obj){dmg=0; max_dmg = 1; pkty =10; setTexture(obj.textures[5]); setScale(0.67, 0.67);}
    ~Klocek_bialy(){};
    virtual void changeTexture1(Textures &obj) override{};
    virtual void changeTexture2(Textures &obj) override{};
};

class Klocek_fioletowy :public Klocek{
public:

    Klocek_fioletowy(Textures &obj){dmg=0; max_dmg = 2; pkty = 30; setTexture(obj.textures[3]); setScale(0.67, 0.67);}
    ~Klocek_fioletowy(){};
    void changeTexture1(Textures &obj) override{
        auto Ptr = &obj.textures[4];
        if (dmg == max_dmg/2) {setTexture(*Ptr);}
    };
    virtual void changeTexture2(Textures &obj) override{};
};

class Klocek_niebieski :public Klocek{
public:

    Klocek_niebieski(Textures &obj){dmg=0; max_dmg = 4; pkty = 80; setTexture(obj.textures[0]); setScale(0.67, 0.67); }
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
    int points=0;
    int zycia=3;

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
        if (bounds.top + bounds.width > bound_bot) {
            zycia--;
            setPosition(640,500);
            vely=-std::abs(vely);
        }
        if (platforma.getGlobalBounds().intersects(bounds)){
            vely = -std::abs(vely);
        }
        for(auto &x: w){
                if (x->getGlobalBounds().intersects(bounds)){

                    if(x->getGlobalBounds().top < getPosition().y && x->getGlobalBounds().left<getPosition().x &&
                       x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x){
                       vely = -vely;
                        //std::cout<<"a"<<std::endl;
                    }

                   else if (x->getGlobalBounds().top + x->getGlobalBounds().height>getPosition().y &&
                        x->getGlobalBounds().left < getPosition().x &&
                        x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x)
                       {vely=-vely;

                       }
                    //zderzenie od lewej
                   else if (x->getGlobalBounds().left < getPosition().x && x->getGlobalBounds().top < getPosition().y &&
                        x->getGlobalBounds().top+x->getGlobalBounds().height > getPosition().y){
                        velx=-velx;

                    }
                    //zderzenie od prawej
                   else if (x->getGlobalBounds().left + x->getGlobalBounds().width > getPosition().x &&
                        x->getGlobalBounds().top <getPosition().y &&
                        x->getGlobalBounds().top + x->getGlobalBounds().height > getPosition().y)
                    {velx=-velx;
                        //std::cout<<"d"<<std::endl;
                           }
                       x->dmg++;
                       if (x->dmg==x->max_dmg) {x->usun = true; points = points + x->pkty;}
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

class Modyfikator:public AnimatedSprite{
public:
    Modyfikator(Textures &obj, sf::Vector2f pos){
                      setPosition(pos);
                      int los =rand()%4;
                      switch(los){
                      case(0):{
                          type = typ::slower;
                          setTexture(obj.textures[0]);
                      break;}
                      case(1):{
                          type = typ::faster;
                          setTexture(obj.textures[1]);
                      break;}
                      case(2):{
                          type = typ::death;
                          setTexture(obj.textures[2]);
                      break;}
                      case(3):{
                          type = typ::point;
                          setTexture(obj.textures[3]);
                          setScale(0.06, 0.06);
                      break;}
                      }};


    bool usun=false;
    void animate(){move(0, 1);}
    enum typ {slower, faster, death, point};
    int type;
    void make_bonus(Platforma &platforma, Pilka &pilka){
       auto bounds = this->getGlobalBounds();
       if(platforma.getGlobalBounds().intersects(bounds)){
        if(type == typ::slower){pilka.velx = pilka.velx/2; pilka.vely = pilka.vely/2;}
        if(type == typ::faster){pilka.velx= pilka.velx*2; pilka.vely = pilka.vely*2;}
        if(type == typ::death) {pilka.zycia --;}
        if(type == typ::point) {pilka.points = pilka.points+100;}
        usun=true;
    }
    if (bounds.top+bounds.width>bound_bot) usun=true;
    }

};


class Klocek_niespodzianka:public Klocek {
public:
    Klocek_niespodzianka(Textures &obj){dmg=0; max_dmg=1; pkty =0; setTexture(obj.textures[7]); setScale(0.67, 0.67);}
    virtual void changeTexture1(Textures &obj) override{};
    virtual void changeTexture2(Textures &obj) override{};

};



class Klocek_cegla : public Klocek{
public:
    Klocek_cegla(Textures &obj){dmg=0; max_dmg=1000000000; pkty=0; setTexture(obj.textures[6]); setScale(0.67, 0.67);}
    ~Klocek_cegla(){};
    virtual void changeTexture1(Textures &obj) override{};
    virtual void changeTexture2(Textures &obj) override{};

};





#endif // KLASY_H
