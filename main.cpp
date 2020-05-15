#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <cmath>
#include <sstream> 
#include <cstdlib>
#include "ship.c"
#include "LTexture.c"
#include "black_hole.c"
#include "alien.c"
#include "game.c"

int main( int argc, char* args[] )
{

    Game deep_space;
    
    LTexture* textures[10][4];
    
    bool A_L = true;
    
    //Start up SDL and create window
    if( !deep_space.init() )
    {
        SDL_Log( "Failed to initialize!\n" );

    }
    else
    {

        //Load media
        if( !deep_space.loadMedia() )
        {
            SDL_Log( "Failed to load media!\n" );
            
        }
        else
        {
            //Main loop flag

            deep_space.ship.screenRect.w = deep_space.gScreenRect.w;
            deep_space.ship.screenRect.h = deep_space.gScreenRect.h;

            deep_space.touchLocation.x = deep_space.gScreenRect.w / 2;
            deep_space.touchLocation.y = deep_space.gScreenRect.h / 2;
            
            textures[0][0] = &deep_space.ship1_a;
            textures[0][1] = &deep_space.ship1_b;
            textures[0][2] = &deep_space.ship1_c;
            textures[0][3] = &deep_space.ship1_d;
            
            
            textures[1][0] = &deep_space.ship2_a;
            textures[1][1] = &deep_space.ship2_b;
            textures[1][2] = &deep_space.ship2_c;
            textures[1][3] = &deep_space.ship2_d;
            
            
            textures[2][0] = &deep_space.ship3_a;
            textures[2][1] = &deep_space.ship3_b;
            textures[2][2] = &deep_space.ship3_c;
            textures[2][3] = &deep_space.ship3_d;
            
            textures[3][0] = &deep_space.ship4_a;
            textures[3][1] = &deep_space.ship4_b;
            textures[3][2] = &deep_space.ship4_c;
            textures[3][3] = &deep_space.ship4_d;
            
            textures[4][0] = &deep_space.ship5_a;
            textures[4][1] = &deep_space.ship5_b;
            textures[4][2] = &deep_space.ship5_c;
            textures[4][3] = &deep_space.ship5_d;
            
            //While application is running
            while( !deep_space.quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &deep_space.e ) != 0 )
                {
                    deep_space.check_event();
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( deep_space.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( deep_space.gRenderer );
                

                
                
                deep_space.space_700.render(0, 0);


                
                if(deep_space.level == -3)
                {
                    deep_space.upgrades_menu(textures);
                }
                else if(deep_space.level == -2)
                {
                    deep_space.controls_menu();
                }
                else if(deep_space.level == -1)
                {
                    deep_space.start_menu();
                }
                else if(deep_space.level == 0)
                {
                    deep_space.initiate(textures);
                }
                else if(deep_space.level != 0)
                {
                    if(deep_space.holes.size() < 1)
                    {
                        deep_space.holes.push_back(new Black_Hole(deep_space.gScreenRect.w/2 - deep_space.black_hole.mWidth/2, deep_space.gScreenRect.h/2 - deep_space.black_hole.mHeight/2, 0, -1));
                        deep_space.holes.back()->set_texture(&deep_space.black_hole);
                    }
                
                    deep_space.level_one();
                }
            
                if(deep_space.level == 3 && deep_space.unlocks[1] == false)
                {
                    deep_space.fly_away_animation();
                    
                    deep_space.approach_planet(1);
                    
                    deep_space.unlocks[1] = true;
                    deep_space.ship.upgrade_level = 1;

  
                    deep_space.ship.set_texture_array(textures[1], &deep_space.yellow_bullet, &deep_space.blue_laser_bullet);
                    
                    deep_space.enter_zone();
                    
                    
                    
                }
                if(deep_space.level == 3 && deep_space.holes.size() < 2)
                {
                    deep_space.holes.push_back(new Black_Hole(deep_space.black_hole.mWidth/2, deep_space.black_hole.mHeight/2, 0, 1));
                    deep_space.holes.back()->set_texture(&deep_space.black_hole);
                }
                if(deep_space.level == 6 && deep_space.unlocks[2] == false)
                {
                    deep_space.fly_away_animation();
                    
                    deep_space.approach_planet(2);
                    
                    deep_space.unlocks[2] = true;
                    deep_space.ship.upgrade_level = 2;
                    
                    deep_space.ship.set_texture_array(textures[2], &deep_space.yellow_bullet, &deep_space.red_bullet);
                    
                    deep_space.enter_zone();
                    
                }
                if(deep_space.level == 6 && deep_space.holes.size() < 3)
                {
                    deep_space.holes.push_back(new Black_Hole(deep_space.gScreenRect.w - deep_space.gScreenRect.w*(1.0/3.0), deep_space.gScreenRect.h - deep_space.gScreenRect.h/2+deep_space.black_hole.mHeight/2, 0, -1));
                    deep_space.holes.back()->set_texture(&deep_space.black_hole);
                }
                if(deep_space.level == 9 && deep_space.unlocks[3] == false)
                {
                    deep_space.fly_away_animation();
                    
                    deep_space.approach_planet(3);
                    
                    deep_space.unlocks[3] = true;
                    deep_space.ship.upgrade_level = 3;
                    
                    deep_space.ship.set_texture_array(textures[3], &deep_space.purple_bullet, &deep_space.blue_bullet);
                    
                    deep_space.enter_zone();
                    
                }
                if(deep_space.level == 9 && deep_space.holes.size() < 4)
                {
                    deep_space.holes.push_back(new Black_Hole(deep_space.gScreenRect.w - deep_space.gScreenRect.w*(2.0/3.0), deep_space.gScreenRect.h - deep_space.gScreenRect.h/4+deep_space.black_hole.mHeight/2, 0, -1));
                    deep_space.holes.back()->set_texture(&deep_space.black_hole);
                }
                
                //Update screen
                SDL_RenderPresent( deep_space.gRenderer );
            }
        }
    }

    //Free resources and close SDL
    deep_space.close();
    
    return 0;
}





























/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
//texture

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
//ship
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
//rock

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
//bullet
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



