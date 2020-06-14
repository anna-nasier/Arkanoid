#include <iostream>
#include <SFML/Graphics.hpp>
#include "klasy.h"
#include<algorithm>
#include<vector>


int width = 1280;
int height = 720;



int main(){

    sf::RenderWindow window(sf::VideoMode(width,height),"Arkanoid");
    window.setFramerateLimit(120);

    std::vector<sf::Texture>toLoad;

    //tlo napis i sprite

    sf::Texture tlo;
    if (!tlo.loadFromFile("tlo4_szersze.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite tlo_;
    tlo_.setScale(1.0, 1.0);
    tlo_.setTextureRect(sf::IntRect(0, 0, width , height));
    tlo_.setTexture(tlo);

    //napis tekstury i sprite

    sf::Texture napis1;
    napis1.loadFromFile("napis1.png");
    toLoad.emplace_back(napis1);

    sf::Texture napis2;
    napis2.loadFromFile("napis2.png");
    toLoad.emplace_back(napis2);

    sf::Texture napis3;
    napis3.loadFromFile("napis3.png");
    toLoad.emplace_back(napis3);

    sf::Texture napis4;
    napis4.loadFromFile("napis4.png");
    toLoad.emplace_back(napis4);

    Textures napisTxt(toLoad);

    sf::Sprite napis;
    napis.setPosition(55,0);

    // klocki - tekstury
    std::vector<sf::Texture> klocki;
    // 80 pktow - niebieski - w wektorze [0]-[2]

    sf::Texture klocek_80;
    if (!klocek_80.loadFromFile("brick_blue_80.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_80);

    sf::Texture klocek_80_podpsuty;
    if (!klocek_80_podpsuty.loadFromFile("brick_blue_80_podpsuty.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_80_podpsuty);

    sf::Texture klocek_80_zepsuty;
    if (!klocek_80_zepsuty.loadFromFile("brick_blue_80_zepsuty.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_80_zepsuty);

    //30 pktow - fioletowy - w wektorze [3],[4]
    sf::Texture klocek_30;
    if (!klocek_30.loadFromFile("brick_purple_30.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_30);

    sf::Texture klocek_30_zepsuty;
    if (!klocek_30_zepsuty.loadFromFile("brick_purple_30_zepsuty.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_30_zepsuty);
    // 10pktow - bialy - w wektorze [5]
    sf::Texture klocek_10;
    if (!klocek_10.loadFromFile("bialy.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_10);

    // niezniszczalny - w wektorze [6]
    sf::Texture klocek_niezniszczalny;
    if (!klocek_niezniszczalny.loadFromFile("cegla.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_niezniszczalny);

    // klocek niespodzianka - 100pkt/modyfikator - w wektorze [7]

    sf::Texture klocek_niespodzianka;
    if (!klocek_niespodzianka.loadFromFile("brick_niespodzianka.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    klocki.emplace_back(klocek_niespodzianka);
    Textures klocuchy(klocki);

    // platfotma

    sf::Texture platforma_normalna;
    if (!platforma_normalna.loadFromFile("platforma_normalna.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    Platforma platforma;
    platforma.setTexture(platforma_normalna);
    platforma.setPosition(430, 700);


    sf::Texture pilka;
    if (!pilka.loadFromFile("pilka.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    Pilka pilka_;
    pilka_.setTexture(pilka);
    pilka_.setScale(0.2,0.2);
    pilka_.setPosition(640, 500);


    size_t napisType = 0;
    sf::Clock clock;

    std::vector<std::unique_ptr<Klocek>> obiekty;
    for(int i=0; i<10; i++){
        obiekty.emplace_back(std::make_unique<Klocek_niebieski>());
        obiekty[i]->setTexture(klocek_80);
        obiekty[i]->setPosition(405+i*64, 15);
        obiekty[i]->setScale(1.0, 1.0);
    }
    for(int i=10; i<20; i++){
        obiekty.emplace_back(std::make_unique<Klocek_fioletowy>());
        obiekty[i]->setTexture(klocek_30);
        obiekty[i]->setPosition(405+(i-10)*64, 47);
        obiekty[i]->setScale(1.0, 1.0);
    }
    for(int i=20; i<30; i++){
        obiekty.emplace_back(std::make_unique<Klocek_bialy>());
        obiekty[i]->setTexture(klocek_10);
        obiekty[i]->setPosition(405+(i-20)*64, 79);
        obiekty[i]->setScale(1.0, 1.0);
    }

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed) {window.close();}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {window.close();}
            if(event.type==sf::Event::MouseMoved) {
               platforma.animate(window);
               platforma.bounce();
            }
        }

        window.clear();

        sf::Time time = clock.getElapsedTime();
        float time_ = time.asSeconds();

        //napis Arkanoid - 'animacja'

        if (time_ > 0.1) {
        napisType++;
        if(napisType>toLoad.size()-1){napisType=0;}
        auto txtPtr = &napisTxt.textures[napisType];
        napis.setTexture(*txtPtr);
        clock.restart();
        }
        // koniec


        pilka_.animate(platforma, obiekty, klocuchy);
        for (size_t i=0; i<obiekty.size(); ++i){
            if (obiekty[i]->usun){
                obiekty.erase(obiekty.begin()+i);
            }}
        window.draw(tlo_);
        window.draw(napis);
        window.draw(platforma);
        for(auto &x : obiekty){
            window.draw(*x);
        }
        window.draw(pilka_);

        window.display();

    }

    return 0;
}
