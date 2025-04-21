#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <random>
#include <vector>
using namespace sf;
using namespace std;
struct Bullet
{
    Sprite sprite;
    Vector2f velocity;
    float angle;
    Clock lifetimeClock;
};



int main()
{
    int endingScore;
    cout<<"PLEASE ENTER AN ENDING SCORE:"<<'\n';
    cin>>endingScore;
    RenderWindow app(sf::VideoMode(900,900),"TANK GAME",sf::Style::Close);
    app.setFramerateLimit(60);
    Texture bl,t2;
    bl.loadFromFile("bullet.png");
    t2.loadFromFile("tank.png");
    Sprite sTankp(t2),sTanke(t2);
    RectangleShape verticalwall(Vector2f(10,90));
    RectangleShape horizontalwall(Vector2f(90,10));
    float x=700,y=700;
    float z=100,t=100;
    sTankp.setPosition(x,y);
    sTankp.setOrigin(30,30);
    sTanke.setPosition(z,t);
    sTanke.setOrigin(30,30);
    sTanke.setColor(Color::Cyan);
    const int ROW = 10;
    const int COL = 10;
    char gamemap[ROW][COL];
    float speedp1=0,speedp2=0,anglep1=0,anglep2=0;
    float maxSpeed=2.0;
    float acc=0.1,dec=0.15;
    float turnSpeed=0.06;
    float bulletSpeed=3.2;
    int levelred=0;
    int levelblue=0;
    int templevelred=levelred,templevelblue=levelblue;
    int detfactor;
    std::vector<Bullet> bullets;
    Clock bulletCooldown;



    Event e;
    while(app.isOpen())
    {
        while(app.pollEvent(e))
        {
            if(e.type==Event::Closed)
            {
                app.close();
            }
        }
//tank movement
        bool Upper=0,Right=0,Down=0,Left=0;//red tank's direction variables
        bool U=0,R=0,D=0,L=0;//cyan tank's direction variables
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            Upper=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            Right=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            Down=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            Left=1;
        }



        if(Upper&& speedp1<maxSpeed)
        {
            if(speedp1<0)
            {
                speedp1+=dec;
            }
            else
            {
                speedp1+=acc;
            }
        }
        if(Down&& speedp1> -maxSpeed)
        {
            if(speedp1>0)
            {
                speedp1-=dec;
            }
            else
            {
                speedp1-=acc;
            }
        }
        if(!Upper && !Down)
        {
            if(speedp1-dec>0)
            {
                speedp1-=dec;
            }
            else if(speedp1+dec<0)
            {
                speedp1+=dec;
            }

            else
            {
                speedp1 = 0;
            }
        }
        if(Right && speedp1!=0)
        {
            anglep1 += turnSpeed * speedp1/maxSpeed;
        }
        if(Left && speedp1!=0)
        {
            anglep1 -= turnSpeed * speedp1/maxSpeed;
        }
        if (Right && !Upper && !Down)
        {
            anglep1 += turnSpeed;
        }
        if (Left && !Upper && !Down)
        {
            anglep1 -= turnSpeed;
        }

        float newX = x + sin(anglep1) * speedp1;
        float newY = y - cos(anglep1) * speedp1;
        if (newX > 0 && newX < app.getSize().x && newY > 0 && newY < app.getSize().y)
        {
            x = newX;
            y = newY;
        }
        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            U=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            R=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            D=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            L=1;
        }



        if(U&& speedp2<maxSpeed)
        {
            if(speedp2<0)
            {
                speedp2+=dec;
            }
            else
            {
                speedp2+=acc;
            }
        }
        if(D&& speedp2> -maxSpeed)//d represents down
        {
            if(speedp2>0)
            {
                speedp2-=dec;
            }
            else
            {
                speedp2-=acc;
            }
        }
        if(!U && !D)
        {
            if(speedp2-dec>0)
            {
                speedp2-=dec;
            }
            else if(speedp2+dec<0)
            {
                speedp2+=dec;
            }
            else
            {
                speedp2 = 0;
            }
        }
        if(R && speedp2!=0)
        {
            anglep2 += turnSpeed * speedp2/maxSpeed;
        }
        if(L && speedp2!=0)
        {
            anglep2 -= turnSpeed * speedp2/maxSpeed;
        }
        if (R && !U && !D)
        {
            anglep2 += turnSpeed;
        }
        if (L && !U && !D)
        {
            anglep2 -= turnSpeed;
        }

        float newZ = z + sin(anglep2) * speedp2;
        float newT = t - cos(anglep2) * speedp2;
        if (newZ > 0 && newZ < app.getSize().x && newT > 0 && newT < app.getSize().y)
        {
            z = newZ;
            t = newT;
        }
//tank movement
//shooting
        if (Keyboard::isKeyPressed(Keyboard::M) && bulletCooldown.getElapsedTime().asSeconds() > 0.2f)
        {
            bulletCooldown.restart();
            Bullet bullet;
            bullet.sprite.setTexture(bl);
            bullet.sprite.setPosition(x+60 * std::sin(anglep1), y-60*std::cos(anglep1));
            bullet.sprite.setOrigin(8,8);
            bullet.sprite.setColor(Color::Blue);
            bullet.angle = anglep1;
            bullet.velocity = Vector2f(std::sin(anglep1) * bulletSpeed, -std::cos(anglep1) * bulletSpeed);
            bullets.push_back(bullet);
        }

        if (Keyboard::isKeyPressed(Keyboard::V) && bulletCooldown.getElapsedTime().asSeconds() > 0.2f)
        {
            bulletCooldown.restart();
            Bullet bullet;
            bullet.sprite.setTexture(bl);
            bullet.sprite.setPosition(z+60 * std::sin(anglep2), t-60*std::cos(anglep2));
            bullet.sprite.setOrigin(8, 8);
            bullet.sprite.setColor(Color::Blue);
            bullet.angle = anglep2;
            bullet.velocity = Vector2f(std::sin(anglep2) * bulletSpeed, -std::cos(anglep2) * bulletSpeed);
            bullets.push_back(bullet);
        }
//shooting
//collision
        for (size_t i = 0; i < bullets.size(); ++i)
        {
            if (bullets[i].sprite.getGlobalBounds().intersects(sTankp.getGlobalBounds()))//bullet-tank collision starts here
            {
                levelblue+=1;
                bullets.erase(bullets.begin()+i);
            }

            if (bullets[i].sprite.getGlobalBounds().intersects(sTanke.getGlobalBounds()))
            {
                levelred+=1;
                bullets.erase(bullets.begin() + i);
            }

            if (bullets[i].sprite.getPosition().x < 0 || bullets[i].sprite.getPosition().x > app.getSize().x ||
                    bullets[i].sprite.getPosition().y < 0 || bullets[i].sprite.getPosition().y > app.getSize().y )
            {
                bullets.erase(bullets.begin() + i);
            }//bullet_tank collision ends here
        }
        if (sTankp.getGlobalBounds().intersects(sTanke.getGlobalBounds()))//this checks tank-tank collision
        {
            speedp1 = 0;
            speedp2 = 0;
            float overlap = 1.0f;
            float dx = x - z;
            float dy = y - t;
            float angle = atan2(dy, dx);
            x += overlap * cos(angle);
            y += overlap * sin(angle);
            z -= overlap * cos(angle);
            t -= overlap * sin(angle);
        }//tank-tank collision ends here
        //for tank-wall collision, please check the code segment that is written for map design
        //tank-wall collision

//collision
//level changing
        if(templevelblue!=levelblue||templevelred!=levelred)
        {
            detfactor=rand()%3;
            app.clear(Color::White);
            if(templevelblue!=levelblue)
            {
                templevelblue=levelblue;
                std::cout<<"levelblue is: "<<levelblue<<'\n';
                x=rand()%600,y=rand()%600,z=rand()%600,t=rand()%600;
            }
            if(templevelred!=levelred)
            {
                templevelred=levelred;
                std::cout<<"levelred is: "<<levelred<<'\n';
                x=rand()%800,y=rand()%800,z=rand()%800,t=rand()%800;
            }
            bullets.clear();
        }
        if(levelblue==endingScore){
            std::cout<<"BLUE TANK WON."<<'\n';
            app.close();

        }
        else if (levelred==endingScore){
            std::cout<<"RED TANK WON."<<'\n';
            app.close();
        }
//level changing
// for drawing map
        app.clear(Color::White);
        for (size_t i = 0; i < bullets.size(); ++i)
        {
            bullets[i].sprite.move(bullets[i].velocity);
            app.draw(bullets[i].sprite);
            if (bullets[i].lifetimeClock.getElapsedTime().asSeconds() > 12)
            {
                bullets.erase(bullets.begin() + i);
            }

        }
        char map1[ROW][COL]=
        {
            {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '_', '_', '_', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', '_', '_', '_', '_', '_', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '_', '#', '_', '_', ' ', '_', '#', ' ', '#'},
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', ' '}
        };
        char map2[ROW][COL]=
        {
            {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
            {'#', '_', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', '#', '_', '_', '_', '#', '_', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', '#', '#', '_', '#'},
            {'#', ' ', '_', ' ', '#', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '_', '_', '_', '#', '_', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '_', '_', '_', ' ', '_', '#', ' ', '#'},
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', ' '}

        };
        char map3[ROW][COL]=
        {
            {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
            {'#', '_', '#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '_', '_', '_', '#', '_', '#'},
            {'#', '_', '#', ' ', ' ', '#', ' ', '#', '#', '#'},
            {'#', '#', ' ', ' ', '#', '_', '#', '#', '_', '#'},
            {'#', '#', '_', ' ', '#', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '_', ' ', '_', '#', '_', '#'},
            {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', '#', '_', '#', ' ', '#'},
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', ' '}

        };

        switch(detfactor)
        {
        case 0:
            for (int i = 0; i < ROW; ++i)
            {
                for (int j = 0; j < COL; ++j)
                {
                    gamemap[i][j] = map1[i][j];
                }
            }

            break;
        case 1:
            for (int i = 0; i < ROW; ++i)
            {
                for (int j = 0; j < COL; ++j)
                {
                    gamemap[i][j] = map2[i][j];
                }
            }

            break;
        case 2:
            for (int i = 0; i < ROW; ++i)
            {
                for (int j = 0; j < COL; ++j)
                {
                    gamemap[i][j] = map3[i][j];
                }
            }

            break;
        default:
            for (int i = 0; i < ROW; ++i)
            {
                for (int j = 0; j < COL; ++j)
                {
                    gamemap[i][j] = map1[i][j];
                }
            };


        }
        for(int i = 0; i < ROW; i++)
        {
            for(int j = 0; j < COL; j++)
            {
                verticalwall.setPosition(j * 90, i * 90);
                horizontalwall.setPosition(j * 90, i * 90);
                if (gamemap[i][j] == '#')
                {
                    verticalwall.setFillColor(sf::Color::Black);
                    app.draw(verticalwall);
                    if(sTanke.getGlobalBounds().intersects(verticalwall.getGlobalBounds())){
                        speedp2 = 0.2;
                        float overlap = 1.0f;
                        float dx = verticalwall.getPosition().x - z;
                        float dy = verticalwall.getPosition().y - t;
                        float angle = atan2(dy, dx);
                        z -= overlap * cos(angle);
                        t -= overlap * sin(angle);
                    }
                    if(sTankp.getGlobalBounds().intersects(verticalwall.getGlobalBounds())){
                        speedp1 = 0.2;
                        float overlap = 1.0f;
                        float dx = verticalwall.getPosition().x - x;
                        float dy = verticalwall.getPosition().y - y;
                        float angle = atan2(dy, dx);
                        x -= overlap * cos(angle);
                        y -= overlap * sin(angle);
                    }
                    if(i==0&&j==0)
                    {
                        horizontalwall.setFillColor(Color::Black);
                        app.draw(horizontalwall);

                    }
                }
                else if(gamemap[i][j]== '_')
                {
                    horizontalwall.setFillColor(Color::Black);
                    app.draw(horizontalwall);
                    if(sTanke.getGlobalBounds().intersects(horizontalwall.getGlobalBounds())){
                        speedp2 = 0.2;
                        float overlap = 1.0f;
                        float dx = horizontalwall.getPosition().x - z;
                        float dy = horizontalwall.getPosition().y - t;
                        float angle = atan2(dy, dx);
                        z -= overlap * cos(angle);
                        t -= overlap * sin(angle);
                    }
                    if(sTankp.getGlobalBounds().intersects(horizontalwall.getGlobalBounds())){
                        speedp1 = 0.2;
                        float overlap = 1.0f;
                        float dx = horizontalwall.getPosition().x - x;
                        float dy = horizontalwall.getPosition().y - y;
                        float angle = atan2(dy, dx);
                        x -= overlap * cos(angle);
                        y -= overlap * sin(angle);
                    }

                }

            }
        }
for (size_t i = 0; i < bullets.size(); ++i)
{
    for(int row = 0; row < ROW; row++)
    {
        for(int col = 0; col < COL; col++)
        {
            if (gamemap[row][col] == '#')
            {
                // Check collision with vertical walls
                verticalwall.setPosition(col * 90, row * 90);
                if (bullets[i].sprite.getGlobalBounds().intersects(verticalwall.getGlobalBounds()))
                {

                    bullets[i].velocity.x *= -1;
                    bullets[i].sprite.move(bullets[i].velocity.x * 0.5f, 0);
                }
            }
            if(gamemap[row][col]=='_'){
                // Check collision with horizontal walls
                horizontalwall.setPosition(col * 90, row * 90);
                if (bullets[i].sprite.getGlobalBounds().intersects(horizontalwall.getGlobalBounds()))
                {
                    bullets[i].velocity.y *= -1;
                    bullets[i].sprite.move(0, bullets[i].velocity.y * 0.5f);
                }
            }
        }
    }
}


//drawing map



        sTankp.setPosition(x,y);
        sTankp.setRotation(anglep1*180/3.141592);
        sTankp.setColor(Color::Red);
        app.draw(sTankp);
        sTanke.setPosition(z,t);
        sTanke.setRotation(anglep2*180/3.141592);
        app.draw(sTanke);

        app.display();
    }
    return 0;
}
