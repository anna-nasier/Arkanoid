#include <iostream>
#include <SFML/Graphics.hpp>
#include "klasy.h"
#include<fstream>
#include <algorithm>


int width = 1280;
int height = 720;

std::vector<int> split(std::string rzadek, char separator=' '){
    size_t position1=0;
    size_t position2=0;
    std::vector<int> kloc;
    std::string nr;
    int kl_poj;
    while ((position1 = rzadek.find(separator, position1 + 1)) != std::string::npos){
        //std:: cout <<"2: " <<position2<<std::endl;
        //std::cout <<"1: "<< position1 << std::endl;
        //std:: cout << "3: "<< position1-position2 <<std::endl;
        nr = rzadek.substr(position2,position1-position2);
        std::cout<<nr<<std::endl;
        kl_poj = atoi(nr.c_str());
        std::cout<<kl_poj<<std::endl;
        kloc.emplace_back(kl_poj);
        position2=position1+1;
    };
     nr = rzadek.substr(position2,rzadek.length()-position2);
     kl_poj = atoi(nr.c_str());
     kloc.emplace_back(kl_poj);
     return kloc;
};


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
    poziomy[nr_poziomu]->close();
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


    //pilka

    sf::Texture pilka;
    if (!pilka.loadFromFile("pilka.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    Pilka pilka_;
    pilka_.setTexture(pilka);
    pilka_.setScale(0.2,0.2);
    pilka_.setPosition(640, 500);



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


    sf::Text koniec3;
    koniec3.setFont(font);
    koniec3.setPosition(400, 260);
    koniec3.setCharacterSize(100);
    std::string konie3="WYGRANA!";
    koniec3.setString(konie3);


    sf::Text koniec4;
    koniec4.setFont(font);
    koniec4.setPosition(400, 360);
    koniec4.setCharacterSize(50);
    std::string konie4="Escape, aby wyjsc!";
    koniec4.setString(konie4);
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


    std::fstream poziom3;
    poziom3.open("poz3.txt", std::ios::in);
    if(!poziom3.good()){
        std::cout<<"Nie udało się wczytać gry!"<<std::endl;
        window.close();
    }

    std::fstream * poz3 = &poziom3;
    poziomy.emplace_back(poz3);

    std::vector<std::unique_ptr<Klocek>> obiekty;
    size_t napisType = 0;
    sf::Clock clock;



    int nr_poziomu = 0;
    int max_nr_poz = 3;
    int pnkty;
    int zy;
    lvl_loading(poziomy, obiekty, nr_poziomu, klocuchy);
    std::vector<std::unique_ptr<Modyfikator>> modyfikatory;

    while(window.isOpen()){
      if(pilka_.zycia>0)  {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed) {window.close();}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}
            if(event.type==sf::Event::MouseMoved) {
               platforma.animate(window);
               platforma.bounce();
            }
        }



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



        //punkty
        pnkty = pilka_.points;
        std::string p = std::to_string(pnkty);
        punkty.setString(p);

        //zycia

        zy= pilka_.zycia;
        std::string zycka = std::to_string(zy);
        zycie2.setString(zycka);




        pilka_.animate(platforma, obiekty, klocuchy);
        for (size_t i=0; i<obiekty.size(); ++i){
            if (obiekty[i]->usun){
                Klocek_niespodzianka * nies = dynamic_cast<Klocek_niespodzianka*>(obiekty[i].get());
                if (nies != nullptr){
                   auto pos = obiekty[i]->getPosition();
                    modyfikatory.emplace_back(std::make_unique<Modyfikator>(modyf, pos));


                }
                obiekty.erase(obiekty.begin()+i);
            }}

        for(size_t i=0; i<modyfikatory.size(); i++){
            modyfikatory[i]->animate();
            modyfikatory[i]->make_bonus(platforma, pilka_);
            if (modyfikatory[i]->usun){
                modyfikatory.erase(modyfikatory.begin()+i);
            }
        }

        window.clear();

        window.draw(tlo_);
        window.draw(napis);
        window.draw(platforma);
        for(auto &x : obiekty){
            window.draw(*x);
        }
        for(auto &y : modyfikatory){
            window.draw(*y);
        }
        window.draw(pilka_);
        window.draw(pu);
        window.draw(punkty);
        window.draw(zycie1);
        window.draw(zycie2);
        if(obiekty.size()==0 || std::all_of(obiekty.begin(), obiekty.end(), blocks_left)){
            obiekty.clear();
            if (nr_poziomu<max_nr_poz){
                nr_poziomu++;
                lvl_loading(poziomy, obiekty, nr_poziomu, klocuchy);
                pilka_.vely = - pilka_.vely;
                pilka_.setPosition(500, 500);
            }
            else{
                window.clear();
                pu.setPosition(400, 460);
                punkty.setPosition(570, 460);
                zycie1.setPosition(650,490);
                zycie2.setPosition(750,460);
                zycie1.setPosition(650,460);
                zycie2.setPosition(750,460);
                window.draw(zycie1);
                window.draw(zycie2);
                window.draw(pu);
                window.draw(punkty);
                window.draw(koniec3);
                window.draw(koniec4);
            }

        }
    }
        else{
           window.clear();
           pu.setPosition(400, 460);
           punkty.setPosition(530, 460);
           window.draw(pu);
           window.draw(punkty);
           window.draw(koniec);
           window.draw(koniec2);
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}
        }

        window.display();

    }

    return 0;
}
