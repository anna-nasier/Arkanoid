#include <iostream>
#include <SFML/Graphics.hpp>
#include "klasy.h"
<<<<<<< Updated upstream
=======
#include<fstream>
#include <algorithm>
>>>>>>> Stashed changes


int width = 1280;
int height = 720;


void lvl_loading(std::vector<std::fstream*> &poziomy, std::vector<std::unique_ptr<Klocek>> &klocki, int nr_poziomu, Textures &obj){
    std::string rzadek;
    int j=0;
    int it=0;
    while(getline(*poziomy[nr_poziomu],rzadek)){
        std::vector<int> rzad = split(rzadek, ';');
        for(unsigned int i=0; i<rzad.size(); i++){
            switch(rzad[i]){
            case(0):{
                klocki.emplace_back(std::make_unique<Klocek_niebieski>(obj));
                klocki[it]->setPosition(405+i*43,15+ 21.5*j);
            break;}
            case(1):{
                klocki.emplace_back(std::make_unique<Klocek_fioletowy>(obj));
                klocki[it]->setPosition(405+i*43,15+ 21.5*j);
            break;}
            case(2):{
                klocki.emplace_back(std::make_unique<Klocek_bialy>(obj));
                klocki[it]->setPosition(405+i*43,15+ 21.5*j);
            break;
            }
            case(3):{
                klocki.emplace_back(std::make_unique<Klocek_niespodzianka>(obj));
                klocki[it]->setPosition(405+i*43,15+ 21.5*j);
            break;
            }
            case(4):{
                klocki.emplace_back(std::make_unique<Klocek_cegla>(obj));
                klocki[it]->setPosition(405+i*43,15+ 21.5*j);
            break;
            }}
            it++;}
        j++;}
}
bool blocks_left(std::unique_ptr<Klocek> &klocek){
    Klocek_cegla * c = dynamic_cast<Klocek_cegla*>(klocek.get());
    if (c != nullptr)return true;
        else return false;

}

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

    NapisTextures napisTxt(toLoad);

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

    // platfotma

    sf::Texture platforma_normalna;
    if (!platforma_normalna.loadFromFile("platforma_normalna.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    Platforma platforma;
    platforma.setTexture(platforma_normalna);
    platforma.setScale(1.0, 1.0);
    platforma.setPosition(430, 700);


    sf::Texture pilka;
    if (!pilka.loadFromFile("pilka.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    Pilka pilka_;
    pilka_.setTexture(pilka);
    pilka_.setScale(0.2,0.2);
    pilka_.setTextureRect(sf::IntRect(0,0,110,112));
    pilka_.setPosition(640, 500);


<<<<<<< Updated upstream
    size_t napisType = 0;
    sf::Clock clock;

    std::vector<Klocek*> wsk_obiekty;
=======

    //modyfikatory

    std::vector<sf::Texture> modifiers;

    sf::Texture slow;
    if (!slow.loadFromFile("snail.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    modifiers.emplace_back(slow);

    sf::Texture fast;
    if (!fast.loadFromFile("rabbit.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    modifiers.emplace_back(fast);
    sf::Texture death;
    if (!death.loadFromFile("skull.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    modifiers.emplace_back(death);


    sf::Texture points;
    if (!points.loadFromFile("gold.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    modifiers.emplace_back(points);

    Textures modyf(modifiers);


    //napisy

    sf::Font font;
    if (!font.loadFromFile("Acme-Regular.ttf")){
        std::cout<<"Could not load font" <<std::endl;
    }

    sf::Text pu;
    pu.setFont(font);
    pu.setPosition(40,120);
    std::string pi="PUNKTY:";
    pu.setString(pi);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setPosition(170,120);

    sf::Text zycie1;
    zycie1.setFont(font);
    zycie1.setPosition(40, 150);
    std::string z="ZYCIA:";
    zycie1.setString(z);

    sf::Text zycie2;
    zycie2.setFont(font);
    zycie2.setPosition(140, 150);

    sf::Text koniec;
    koniec.setFont(font);
    koniec.setPosition(400, 260);
    koniec.setCharacterSize(100);
    std::string konie="PRZEGRANA!";
    koniec.setString(konie);

    sf::Text koniec2;
    koniec2.setFont(font);
    koniec2.setPosition(400, 360);
    koniec2.setCharacterSize(50);
    std::string konie2="Escape, aby wyjsc!";
    koniec2.setString(konie2);

    //poziom!

    std::vector<std::fstream *> poziomy;

    std::fstream poziom1;
    poziom1.open("poz.txt", std::ios::in);
    if(!poziom1.good()){
        std::cout<<"Nie udało się wczytać gry!"<<std::endl;
        window.close();
    }

    std::fstream * poz1 = &poziom1;
    poziomy.emplace_back(poz1);

    std::fstream poziom2;
    poziom2.open("poz2.txt", std::ios::in);
    if(!poziom2.good()){
        std::cout<<"Nie udało się wczytać gry!"<<std::endl;
        window.close();
    }
    std::fstream * poz2 = &poziom2;
    poziomy.emplace_back(poz2);

    int nr_poziomu =0;

    std::vector<std::unique_ptr<Klocek>> obiekty;
    size_t napisType = 0;
    sf::Clock clock;


/*    for(int i=0; i<20; i++){
        obiekty.emplace_back(std::make_unique<Klocek_niebieski>(klocuchy));
        obiekty[i]->setPosition(405+i*43, 15);
    }
    for(int i=20; i<40; i++){
        obiekty.emplace_back(std::make_unique<Klocek_fioletowy>(klocuchy));
        obiekty[i]->setPosition(405+(i-20)*43, 36.5);
    }
    for(int i=40; i<60; i++){
        obiekty.emplace_back(std::make_unique<Klocek_bialy>(klocuchy));
        obiekty[i]->setPosition(405+(i-40)*43, 58);
    }

    for(int i =60; i<80; i++){
        obiekty.emplace_back(std::make_unique<Klocek_niespodzianka>(klocuchy));
        obiekty[i]->setPosition(405+(i-60)*43, 79.5);
    }

    for(int i=80; i<85; i++){
        obiekty.emplace_back(std::make_unique<Klocek_cegla>(klocuchy));
        obiekty[i]->setPosition(405+(i-80)*43, 101);
    }
    */



    int pnkty;
    int zy;
    lvl_loading(poziomy, obiekty, nr_poziomu, klocuchy);
    std::vector<std::unique_ptr<Modyfikator>> modyfikatory;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
        for(int i=0; i<10; i++){
            Klocek_niebieski kloc;
            kloc.setTexture(klocek_80);
            kloc.setPosition(405+i*64, 15);
            wsk_obiekty.emplace_back(&kloc);
=======
        if(obiekty.size()==0 || std::any_of(obiekty.begin(), obiekty.end(), blocks_left)){
            nr_poziomu++;
            lvl_loading(poziomy, obiekty, nr_poziomu, klocuchy);

        }






        //punkty
        pnkty = pilka_.points;
        std::string p = std::to_string(pnkty);
        punkty.setString(p);

        //zycia

        zy= pilka_.zycia;
        std::string zycka = std::to_string(zy);
        zycie2.setString(zycka);


>>>>>>> Stashed changes

        }




        pilka_.animate(platforma);
        window.draw(tlo_);
        window.draw(napis);
        window.draw(platforma);
        for(auto x : wsk_obiekty){
            window.draw(*x);
        }
        window.draw(pilka_);

        window.display();

    }

    return 0;
}
