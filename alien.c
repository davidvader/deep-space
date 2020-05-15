

#ifndef ____alien__
#define ____alien__

#include "ship.c"
#include "bullet.c"


struct Alien{
    
    //Maximum axis velocity of the bullet
    static const double ALIEN_VEL = 10.0;
    double ALIEN_PROPULSION;
    LTexture* alien_texture1 = NULL;
    LTexture* alien_texture2 = NULL;
    LTexture* alien_texture3 = NULL;
    LTexture* alien_texture4 = NULL;
    LTexture* alien_texture5 = NULL;
    //Initializes the variables
    Alien(double, double, double, double);
    
    //sets window and renderer
    void set_textures(LTexture*,LTexture*,LTexture*,LTexture*,LTexture*);
    
    //Moves the bullet, return -1 if good, else is the rock hit
    int move(Ship, int, int);
    
    //Shows the bullet on the screen
    void render();
    
    //checks for collisions with rocks or enemies
    int collide(Ship);
    
    
    //The X and Y offsets of the bullet
    double mPosX, mPosY;
    
    //The velocity of the bullet
    double mVelX, mVelY;
    
    //degrees of the bullet
    double degrees;
    double img_radius;
    int rotation;
    
    int hp;
    
};


Alien::Alien(double x, double y, double degree, double prop)
{
    img_radius = 45;
    degrees = degree;
    ALIEN_PROPULSION = prop;
    rotation = 0;
    //Initialize the velocity
    
    mVelX = cos((degrees) /(180.0 / M_PI)) * 10.0;
    mVelY = sin((degrees) /(180.0 / M_PI)) * 10.0;
    
    mPosX += mVelX * 5;
    mPosY += mVelY * 5;
    hp = 15;
}

void Alien::set_textures(LTexture* text1, LTexture* text2, LTexture* text3,LTexture* text4,LTexture* text5 )
{
    alien_texture1 = text1;
    alien_texture2 = text2;
    alien_texture3 = text3;
    alien_texture4 = text4;
    alien_texture5 = text5;
}
int Alien::move(Ship ship, int screen_w, int screen_h)
{
    //Move the bullet left or right
    
    if(hp < 6)
    {
        ALIEN_PROPULSION = 1;
        degrees -= 3;
    }
    
    degrees += 1;
    
    if(rotation == 50) degrees -= 45;
    if(rotation == 75) degrees += 30;
    if(rotation == 150) degrees -= 60;
    if(rotation == 200) degrees -= 45;
    
    mVelX = cos((degrees) /(180.0 / M_PI)) * ALIEN_VEL;
    mVelY = sin((degrees) /(180.0 / M_PI)) * ALIEN_VEL;
    
    double xVar = mVelX * ALIEN_PROPULSION;
    double yVar = mVelY * ALIEN_PROPULSION;
    
    mPosX += xVar; mPosY += yVar;

    if(mPosX < alien_texture1->mWidth*-1) {
        
        mPosX = screen_w;
    }
    
    if(( mPosX > screen_w )) {
        
        mPosX = alien_texture1->mWidth*-1;
        
    }
    
    if( mPosY < alien_texture1->mHeight*-1 ){
        
        mPosY = screen_h;
        
    }
    
    if ( mPosY > screen_h ){
        
        mPosY = alien_texture1->mHeight*-1;
        
    }
    rotation++;
    if(rotation > 199) rotation = 0;
    int col = collide(ship);
    return col;
}

void Alien::render()
{
    if(hp > 5)
    {
        if(rotation < 70) alien_texture1->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
        else if(rotation < 135) alien_texture2->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
        else alien_texture3->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else
    {
        if(rotation < 100) alien_texture4->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
        else alien_texture5->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    
    
}
int Alien::collide(Ship ship)
{
    
    //if int is -1 after loop, no collision
    int no_collision = -1;
    
    
    for(int i = 0; i < (int)ship.bullets.size(); i++)
    {
        int bullet_size = ship.bullets[i]->bullet_texture->mWidth;

        if(mPosX <= ship.bullets[i]->mPosX + bullet_size
           && mPosX + alien_texture1->mWidth >= ship.bullets[i]->mPosX)
        {
            if(mPosY <= ship.bullets[i]->mPosY + bullet_size
               && mPosY + alien_texture1->mHeight >= ship.bullets[i]->mPosY)
            {
                return i;
            }
        }
    }
    
    return no_collision;
}






#endif