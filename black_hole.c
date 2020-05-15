

#ifndef __bh_
#define __bh_

#include "ship.c"
#include "bullet.c"


struct Black_Hole{
    
    //Maximum axis velocity of the bullet
    static const double HOLE_VEL = 10.0;
    double HOLE_PROPULSION;
    LTexture* hole_texture = NULL;

    //Initializes the variables
    Black_Hole(double, double, double, int);
    
    //sets window and renderer
    void set_texture(LTexture*);
    
    //Moves the bullet, return -1 if good, else is the rock hit
    int move(Ship);
    
    //Shows the bullet on the screen
    void render();
    
    //checks for collisions with rocks or enemies
    int collide(Ship);
    
    
    //The X and Y offsets of the bullet
    double mPosX, mPosY;
    
    //degrees of the bullet
    double degrees;
    double img_radius;
    int roto;
};


Black_Hole::Black_Hole(double x, double y, double degree, int d)
{
    img_radius = 45;
    degrees = degree;
    HOLE_PROPULSION = 0;
    //Initialize the velocity
    
    mPosX = x;
    mPosY = y;
    
    roto = d;
    
}

void Black_Hole::set_texture(LTexture* text1)
{
    hole_texture = text1;
}
int Black_Hole::move(Ship ship)
{
    //Move the bullet left or right

    
    
    if(roto == -1)degrees -= 1;
    if(roto == 1)degrees += 1;
    
    int col = collide(ship);
    return col;
}

void Black_Hole::render()
{
    if(roto == -1)hole_texture->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    else hole_texture->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_VERTICAL );
}
int Black_Hole::collide(Ship ship)
{
    
    // SHORTCODE: BLACKHOLE COLLISION
    
    if(mPosX + 75 <= ship.mPosX + ship.SHIP_WIDTH
       && mPosX - 75 + hole_texture->mWidth >= ship.mPosX)
    {
        if(mPosY + 75 <= ship.mPosY + ship.SHIP_HEIGHT
           && mPosY - 75 + hole_texture->mHeight >= ship.mPosY)
        {
            return 1;
        }
    }
    return -1;
}









#endif