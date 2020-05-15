

#ifndef ____rock__
#define ____rock__


/***********************************************************************/
#include "LTexture.c"



struct Rock{
    
    //Maximum axis velocity of the bullet
    double ROCK_VEL;
    double ROCK_PROPULSION;
    LTexture* textures[4];
    //Initializes the variables
    Rock(double, double, double, int);
    
    //sets window and renderer
    void set_texture(LTexture*, LTexture*, LTexture*, LTexture*);
    
    //Moves the bullet
    bool move(int, int);
    
    //Shows the bullet on the screen
    void render();
    
    //The X and Y offsets of the bullet
    double mPosX, mPosY;
    
    //The velocity of the bullet
    double mVelX, mVelY;
    
    //degrees of the bullet
    double degrees;
    int size;
    
};






/***********************************************************************/

/***********************************************************************/




Rock::Rock(double x, double y, double degree, int s)
{
    ROCK_VEL = 10.0;
    ROCK_PROPULSION = 0.2;
    textures[0] = NULL;
    textures[1] = NULL;
    textures[2] = NULL;
    textures[3] = NULL;
    degrees = degree;
    size = s;
    //Initialize the offsets to center of image
    mPosX = x;
    mPosY = y;
    
    //Initialize the velocity
    
    mVelX = cos((degrees) /(180.0 / M_PI)) * 10.0;
    mVelY = sin((degrees) /(180.0 / M_PI)) * 10.0;
    
    mPosX += mVelX;
    mPosY += mVelY;
    
}

void Rock::set_texture(LTexture* text_100, LTexture* text_66, LTexture* text_33, LTexture* text_11)
{
    textures[0] = text_100;
    textures[1] = text_66;
    textures[2] = text_33;
    textures[3] = text_11;
}
bool Rock::move(int screen_w, int screen_h)
{
    // SHORTCODE: ROCK MOVE
    
    double xVar = mVelX * ROCK_PROPULSION;
    double yVar = mVelY * ROCK_PROPULSION;
    if(size == 100) degrees -= 1;
    if(size == 66) degrees += 1;
    if(size == 33) degrees -= 1;
    if(size == 11) degrees -= 1;
    mPosX += xVar; mPosY += yVar;
    if(mPosX <= size*-1) {
        
        mPosX = screen_w;
    }
    
    if(( mPosX > screen_w + 15)) {
        
        mPosX = 0;
        
    }
    
    if( mPosY <= size*-1 ){
        
        mPosY = screen_h;
        
    }
    
    if ( mPosY > screen_h + 15){
        
        mPosY = 0;
        
    }
    return true;
}

void Rock::render()
{
    if(size == 100)
    {
        textures[0]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else if(size == 66)
    {
        textures[1]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else if(size == 33)
    {
        textures[2]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
    else if(size == 11)
    {
        textures[3]->render( mPosX, mPosY, NULL, degrees, NULL, SDL_FLIP_NONE );
    }
}
           
#endif /* defined(____rock__) */

