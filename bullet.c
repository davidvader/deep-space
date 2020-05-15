
#ifndef ____blt__
#define ____blt__


#include "rock.c"
#include "LTexture.c"


/***********************************************************************/





struct Bullet{
    
    //Maximum axis velocity of the bullet
    static const double BULLET_VEL = 10.0;
    double BULLET_PROPULSION;
    LTexture* bullet_texture = NULL;
    //Initializes the variables
    Bullet(double, double, double, double);
    
    //sets window and renderer
    void set_texture(LTexture* text);
    
    //Moves the bullet, return -1 if good, else is the rock hit
    int move(std::vector<Rock*>& rocks, int, int);
    
    //Shows the bullet on the screen
    void render();
    
    //checks for collisions with rocks or enemies
    int collide(std::vector<Rock*>& rocks);
    
    
    //The X and Y offsets of the bullet
    double mPosX, mPosY;
    
    //The velocity of the bullet
    double mVelX, mVelY;
    
    //degrees of the bullet
    double degrees;
    double img_radius;
};



/***********************************************************************/
/***********************************************************************/


Bullet::Bullet(double x, double y, double degree, double prop)
{
    img_radius = 45;
    degrees = degree;
    if(prop * 3 > 0.8) BULLET_PROPULSION = prop * 3;
    else BULLET_PROPULSION = 0.8;
    // SHORTCODE: BULLET OFFSETS
    mPosX = x + 35;
    mPosY = y + 25;
    if(degrees >= 0 && degrees < 45)
    {
        mPosX -= 6;
        mPosY -= 4;

    }
    if(degrees > 44 && degrees < 120)
    {
        mPosX += 3;
        mPosY -= 7;
    }
    if(degrees > 119 && degrees < 179)
    {
        mPosX += 5;
        mPosY -= 3;
    }
    if(degrees > 180 && degrees < 180)
    {
        //mPosX += 5;
    }
    if(degrees > 270 && degrees < 320)
    {
        mPosY += 3;
    }
    //Initialize the velocity
    
    mVelX = cos((degrees) /(180.0 / M_PI)) * 10.0;
    mVelY = sin((degrees) /(180.0 / M_PI)) * 10.0;
    
    mPosX += mVelX * 5;
    mPosY += mVelY * 5;
    
}

void Bullet::set_texture(LTexture* text)
{
    bullet_texture = text;
}
int Bullet::move(std::vector<Rock*>& rocks, int screen_w, int screen_h)
{
    //Move the bullet left or right
    
    double xVar = mVelX * BULLET_PROPULSION;
    double yVar = mVelY * BULLET_PROPULSION;
    
    mPosX += xVar; mPosY += yVar;
    if(mPosX < -5) {
        
        return -2;
    }
    
    if(( mPosX > screen_w )) {
        
        return -2;
        
    }
    
    if( mPosY < -5 ){
        
        return -2;
        
    }
    
    if ( mPosY > screen_h ){
        
        return -2;
        
    }
    int col = collide(rocks);
    return col;
}

void Bullet::render()
{
    bullet_texture->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
}
int Bullet::collide(std::vector<Rock*>& rocks)
{
    //if int is -1 after loop, no collision
    int no_collision = -1;
    for(int i = 0; i < (int)rocks.size(); i++)
    {
        if(rocks[i]->size != 11)
        {
            if(mPosX <= rocks[i]->mPosX + rocks[i]->size*2.8
               && mPosX + bullet_texture->mWidth >= rocks[i]->mPosX)
            {
                if(mPosY <= rocks[i]->mPosY + rocks[i]->size*2.8
                   && mPosY + bullet_texture->mHeight >= rocks[i]->mPosY)
                {
                    return i;
                }
            }
        }
        else
        {
            if(mPosX <= rocks[i]->mPosX + rocks[i]->size*2
               && mPosX + bullet_texture->mWidth >= rocks[i]->mPosX)
            {
                if(mPosY <= rocks[i]->mPosY + rocks[i]->size*2
                   && mPosY + bullet_texture->mHeight >= rocks[i]->mPosY)
                {
                    return i;
                }
            }
        }
    }
    
    return no_collision;
}


/***********************************************************************/
#endif

