

#ifndef ____ship__
#define ____ship__

//ship.c
#include "bullet.c"
#include "rock.c"
#include "LTexture.c"
#include <SDL_mixer.h>
#include <cmath>

class Ship
{
public:
    //The dimensions of the ship
    static const int SHIP_WIDTH = 90;
    static const int SHIP_HEIGHT = 60;
    
    //Maximum axis velocity of the ship
    static const double SHIP_VEL = 10.0;
    double SHIP_PROPULSION;
    
    LTexture* bulletTexture;
    LTexture* blue_laser_bullet;
    
    LTexture* textures[4];
    
    int jet;
    
    bool fire;
    
    std::vector<Bullet*> bullets;

    SDL_Rect screenRect;
    
    Mix_Chunk *bullet_sound;

    //Initializes the variables
    Ship();
    
    void set_texture_array(LTexture* texts[], LTexture* bullet, LTexture* bullet2);
    
    
    //Takes key presses and adjusts the ship velocity
    void handleEvent(bool buttons[]);
    
    //Moves the ship
    int move(std::vector<Rock*>& rocks);
    
    //Shows the ship on the screen
    void render();
    
    //clear bullets vector
    void clear_bullets();
    
    int collide(std::vector<Rock*>& rocks);
    
    //The X and Y offsets of the ship
    double mPosX, mPosY;
    
    //The velocity of the ship
    double mVelX, mVelY;
    
    //degrees of the ship
    double degrees;
    
    int upgrade_level;
    
    int charge;

};


Ship::Ship()
{
    //Initialize the offsets
    mPosX = screenRect.w / 2;
    mPosY = screenRect.h / 2;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    degrees = 270;
    
    charge = 0;
    
    SHIP_PROPULSION = 0.0;
    bulletTexture = NULL;
    bullet_sound = NULL;
    textures[0] = NULL;
    textures[1] = NULL;
    textures[2] = NULL;
    textures[3] = NULL;
    jet = 0;
    fire = true;
    upgrade_level = 0;
    
}

void Ship::set_texture_array(LTexture* texts[], LTexture* bullet, LTexture* bullet2)
{
    for(int i = 0; i < 4; i++)
    {
        textures[i] = texts[i];
    }
    bulletTexture = bullet;
    blue_laser_bullet = bullet2;
    bullet_sound = Mix_LoadWAV( "sounds/Laser_Shoot8.wav" );
    
}

void Ship::handleEvent(bool buttons[])
{
    
    // SHORTCODE: SHIP SHOOTING VARIATIONS

    if(buttons[1] && buttons[3])
    {
        SHIP_PROPULSION += 0.025;
    }
    else if(buttons[1] && buttons[2])
    {
        degrees -= 5;
        
        if(degrees < 0) degrees += 360;
        if(fire)
        {
            Mix_PlayChannel( -1, bullet_sound, 0 );
            if(upgrade_level == 0)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
            }
            else if(upgrade_level == 1)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees+5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees-5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
                if(charge < 50) charge += 2;
            }
            else if(upgrade_level == 2)
            {
                double tempx = mPosX;
                double tempy = mPosY;
                
                while((tempx > -1 && tempx < screenRect.w) &&
                      (tempy > -1 && tempy < screenRect.h) && fire)
                {
                    
                    bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION*(1.25)));
                    bullets.back()->set_texture(blue_laser_bullet);
                    
                    tempx += cos((degrees) /(180.0 / M_PI)) * 10.0;
                    tempy += sin((degrees) /(180.0 / M_PI)) * 10.0;
                    if((int)bullets.size() > 150)
                    {
                        fire = false;
                    }
                    
                }
                
                if(charge < 50) charge += 3;
            }
            else if(upgrade_level == 3)
            {
                
                double tempx = mPosX;
                double tempy = mPosY;

                double xVar = cos((degrees) /(180.0 / M_PI)) * 15.0;
                double yVar = sin((degrees) /(180.0 / M_PI)) * 15.0;
                
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                xVar = cos((degrees + 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees + 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx -= xVar;
                tempy -= yVar;
                
                
                xVar = cos((degrees - 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees - 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                fire = false;
                if(charge < 50) charge += 2;
            }
            
        }
    }
    else if(buttons[2] && buttons[3])
    {
        degrees += 5;
        
        if(degrees >= 360) degrees -= 360;
        if(fire)
        {
            Mix_PlayChannel( -1, bullet_sound, 0 );
            if(upgrade_level == 0)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
            }
            else if(upgrade_level == 1)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees+5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees-5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
                if(charge < 50) charge += 2;
            }
            else if(upgrade_level == 2)
            {
                double tempx = mPosX;
                double tempy = mPosY;
                
                while((tempx > -1 && tempx < screenRect.w) &&
                      (tempy > -1 && tempy < screenRect.h) && fire)
                {
                    
                    bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION*(1.25)));
                    bullets.back()->set_texture(blue_laser_bullet);
                    
                    tempx += cos((degrees) /(180.0 / M_PI)) * 10.0;
                    tempy += sin((degrees) /(180.0 / M_PI)) * 10.0;
                    if((int)bullets.size() > 250)
                    {
                        fire = false;
                    }
                    
                }
                
                if(charge < 50) charge += 3;
            }
            else if(upgrade_level == 3)
            {
                
                double tempx = mPosX;
                double tempy = mPosY;
                
                double xVar = cos((degrees) /(180.0 / M_PI)) * 15.0;
                double yVar = sin((degrees) /(180.0 / M_PI)) * 15.0;
                
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                xVar = cos((degrees + 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees + 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx -= xVar;
                tempy -= yVar;
                
                
                xVar = cos((degrees - 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees - 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                fire = false;
                if(charge < 50) charge += 2;
            }
        }
    }
    else if(buttons[2])
    {
        if(fire)
        {
            Mix_PlayChannel( -1, bullet_sound, 0 );
            if(upgrade_level == 0)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
            }
            else if(upgrade_level == 1)
            {
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees+5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                bullets.push_back(new Bullet(mPosX, mPosY, degrees-5, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                fire = false;
                if(charge < 50) charge++;
            }
            else if(upgrade_level == 2)
            {
                double tempx = mPosX;
                double tempy = mPosY;
                
                while((tempx > -1 && tempx < screenRect.w) &&
                      (tempy > -1 && tempy < screenRect.h) && fire)
                {

                    bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION*(1.25)));
                    bullets.back()->set_texture(blue_laser_bullet);
                    
                    tempx += cos((degrees) /(180.0 / M_PI)) * 10.0;
                    tempy += sin((degrees) /(180.0 / M_PI)) * 10.0;
                    if((int)bullets.size() > 150)
                    {
                        fire = false;
                    }
                    
                }
                
                if(charge < 50) charge += 3;
            }
            else if(upgrade_level == 3)
            {
                
                
                double tempx = mPosX;
                double tempy = mPosY;
                
                double xVar = cos((degrees) /(180.0 / M_PI)) * 15.0;
                double yVar = sin((degrees) /(180.0 / M_PI)) * 15.0;
                
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                xVar = cos((degrees + 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees + 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                
                tempx -= xVar;
                tempy -= yVar;
                
                
                xVar = cos((degrees - 90) /(180.0 / M_PI)) * 15.0;
                yVar = sin((degrees - 90) /(180.0 / M_PI)) * 15.0;
                
                tempx += xVar;
                tempy += yVar;
                
                bullets.push_back(new Bullet(tempx, tempy, degrees, SHIP_PROPULSION));
                bullets.back()->set_texture(bulletTexture);
                
                tempx -= xVar;
                tempy -= yVar;
                
                
                fire = false;
                if(charge < 50) charge += 2;
            }
        }
    }
    else if(buttons[3])
    {
        degrees += 5;
        
        if(degrees >= 360) degrees -= 360;
    }
    else if(buttons[1])
    {
        degrees -= 5;
        
        if(degrees < 0) degrees += 360;
    }
    if(buttons[0])
    {
        SHIP_PROPULSION -= 0.05;
        if(SHIP_PROPULSION < 0) SHIP_PROPULSION = 0;
        if(upgrade_level == 1)
        {
            if(charge > 0)
            {
                Mix_PlayChannel( -1, bullet_sound, 0 );
                bullets.push_back(new Bullet(mPosX, mPosY, degrees, 1));
                bullets.back()->set_texture(blue_laser_bullet);
                charge--;
            }
        }
        else if(upgrade_level == 2)
        {
            if(charge > 49)
            {
                Mix_PlayChannel( -1, bullet_sound, 0 );
                
                int temp_degrees = degrees;
                while(temp_degrees < degrees + 360)
                {
                
                    bullets.push_back(new Bullet(mPosX, mPosY, temp_degrees, 1));
                    bullets.back()->set_texture(bulletTexture);
                
                    temp_degrees+=10;
                }
                
                charge = 0;
            }
        }
    }
    
}

int Ship::move(std::vector<Rock*>& rocks)
{
    //Move the ship left or right
    
    mVelX = cos((degrees) /(180.0 / M_PI)) * SHIP_VEL;
    mVelY = sin((degrees) /(180.0 / M_PI)) * SHIP_VEL;
    
    double xVar = mVelX * SHIP_PROPULSION;
    double yVar = mVelY * SHIP_PROPULSION;
    
    mPosX += xVar; mPosY += yVar;
    if(mPosX < 0) {
        
        mPosX = screenRect.w;
    }
    
    if(( mPosX > screenRect.w )) {
        
        mPosX = 0;
        
    }
    
    if( mPosY < 0 ){
        
        mPosY = screenRect.h;
        
    }
    
    if ( mPosY > screenRect.h ){
        
        mPosY = 0;
        
    }
    
    SHIP_PROPULSION -= 0.002;
    if(SHIP_PROPULSION < 0.1) SHIP_PROPULSION = 0.14;
    
    int col = collide(rocks);
    return col;
}

void Ship::render()
{
    //Show the ship
    
    if(SHIP_PROPULSION < 0.1) {
        textures[0]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else if(SHIP_PROPULSION < 0.2){
        textures[1]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else
    {
        if(jet < 10)
        {
            textures[3]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
            jet++;
        }
        else
        {
            textures[2]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
            jet = 0;
        }
    }
    
    
}

void Ship::clear_bullets()
{
    for(int i = (int)bullets.size() - 1; i >= 0; i--)
    {
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
    }
}

int Ship::collide(std::vector<Rock*>& rocks)
{
    //if int is -1 after loop, no collision
    int no_collision = -1;
    for(int i = 0; i < (int)rocks.size(); i++)
    {
        if(rocks[i]->size != 11)
        {
            if(mPosX <= rocks[i]->mPosX + rocks[i]->size*2.5
               && mPosX + SHIP_WIDTH*(2.0/3.0) >= rocks[i]->mPosX)
            {
                if(mPosY <= rocks[i]->mPosY + rocks[i]->size*2.5
                   && mPosY + SHIP_HEIGHT*(2.0/3.0) >= rocks[i]->mPosY)
                {
                    return -2;
                }
            }
        }
        else
        {
            if(mPosX <= rocks[i]->mPosX + rocks[i]->size*1.8
               && mPosX + SHIP_WIDTH*(2.0/3.0) >= rocks[i]->mPosX)
            {
                if(mPosY <= rocks[i]->mPosY + rocks[i]->size*1.8
                   && mPosY + SHIP_HEIGHT*(2.0/3.0) >= rocks[i]->mPosY)
                {
                    return i;
                }
            }
        }
    }
    
    return no_collision;
}

#endif
