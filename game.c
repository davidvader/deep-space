

#ifndef ____game__
#define ____game__


struct Game{
    
    
    Game(){
        quit = false;
        
        level = -1;
        
        left_right = false;
        
        buttons_status[0] = false;
        buttons_status[1] = false;
        buttons_status[2] = false;
        buttons_status[3] = false;
        buttons_status[4] = false;
        
        unlocks[0] = true;
        for(int i = 1; i < 10; i++)
        {
            unlocks[i] = false;
        }
        menu_pointer = 0;
    }
    
    //Starts up SDL and creates window
    bool init();
    
    //Loads media
    bool loadMedia();
    
    //Frees media and shuts down SDL
    void close();
    
    void level_one();

    void start_menu();

    void controls_menu();

    void check_event();

    void initiate(LTexture* textures[][4]);
    
    void render_buttons(bool, bool, bool, bool, bool);
    
    void fly_away_animation();
    
    void approach_planet(int);
    
    void enter_zone();
    
    void enter_hole(Ship&, Black_Hole*);
    
    void upgrades_menu(LTexture* [][4]);

    void restart_game();
    
    void clear_rocks();
    
    void clear_holes();
    //The window we'll be rendering to
    SDL_Window* gWindow;
    
    //The window renderer
    SDL_Renderer* gRenderer;
    
    //Screen dimensions
    SDL_Rect gScreenRect;
    
    
    SDL_Event e;
    
    SDL_Point touchLocation;
    
    
    //audio variables
    
    //The music that will be played
    Mix_Music *gMusic;
    
    //The sound effects that will be used
    
    TTF_Font *gFont;
    
    //font texture
    LTexture gTextTexture;
    
    LTexture level_num_texture;
    
    LTexture message_red;
    
    // SHORTCODE: TEXTURES DECLARATION

    LTexture space_700;
    LTexture ship1_a, ship1_b, ship1_c, ship1_d;
    LTexture ship2_a, ship2_b, ship2_c, ship2_d;
    LTexture ship3_a, ship3_b, ship3_c, ship3_d;
    LTexture ship4_a, ship4_b, ship4_c, ship4_d;
    LTexture ship5_a, ship5_b, ship5_c, ship5_d;
    LTexture rock_100, rock_66, rock_33, rock_11;
    LTexture yellow_bullet, blue_bullet, purple_bullet, red_bullet;
    LTexture blue_laser_bullet;
    LTexture brown_planet, blue_planet, green_planet;
    LTexture black_hole;
    //stringstream to hold level number for rendering
    std::stringstream level_num;
    
    
    Ship ship;
    
    std::vector<Rock*> rocks_1;
    
    std::vector<Black_Hole*> holes;
    
    bool quit;
    
    int level;
    
    int progress;
    
    double multipos[10][2];
    
    bool buttons_status[5];
    
    bool unlocks[10];
    
    bool left_right;
    
    int menu_pointer;
    
    SDL_Rect button;
    
    SDL_Rect message_box;

};


bool Game::init()
{
    // SHORTCODE: INITIALIZE SDL
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO  ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            SDL_Log( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Get device display mode
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            gScreenRect.w = displayMode.w;
            gScreenRect.h = displayMode.h;
            
            button.w = displayMode.w/4;
            button.h = displayMode.h/10;
            
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    SDL_Log( "SDL_image could not initialize! %s\n", IMG_GetError() );
                    success = false;
                }
                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool Game::loadMedia()
{
    
    
    
    // SHORTCODE: LOAD MEDIA
    level_num_texture.setWindows(gWindow, gRenderer);
    gTextTexture.setWindows(gWindow, gRenderer);
    message_red.setWindows(gWindow, gRenderer);
    space_700.setWindows(gWindow, gRenderer);
    ship1_a.setWindows(gWindow, gRenderer);
    ship1_b.setWindows(gWindow, gRenderer);
    ship1_c.setWindows(gWindow, gRenderer);
    ship1_d.setWindows(gWindow, gRenderer);
    ship2_a.setWindows(gWindow, gRenderer);
    ship2_b.setWindows(gWindow, gRenderer);
    ship2_c.setWindows(gWindow, gRenderer);
    ship2_d.setWindows(gWindow, gRenderer);
    ship3_a.setWindows(gWindow, gRenderer);
    ship3_b.setWindows(gWindow, gRenderer);
    ship3_c.setWindows(gWindow, gRenderer);
    ship3_d.setWindows(gWindow, gRenderer);
    ship4_a.setWindows(gWindow, gRenderer);
    ship4_b.setWindows(gWindow, gRenderer);
    ship4_c.setWindows(gWindow, gRenderer);
    ship4_d.setWindows(gWindow, gRenderer);
    ship5_a.setWindows(gWindow, gRenderer);
    ship5_b.setWindows(gWindow, gRenderer);
    ship5_c.setWindows(gWindow, gRenderer);
    ship5_d.setWindows(gWindow, gRenderer);
    rock_100.setWindows(gWindow, gRenderer);
    rock_66.setWindows(gWindow, gRenderer);
    rock_33.setWindows(gWindow, gRenderer);
    rock_11.setWindows(gWindow, gRenderer);
    yellow_bullet.setWindows(gWindow, gRenderer);
    red_bullet.setWindows(gWindow, gRenderer);
    blue_bullet.setWindows(gWindow, gRenderer);
    purple_bullet.setWindows(gWindow, gRenderer);
    blue_laser_bullet.setWindows(gWindow, gRenderer);
    brown_planet.setWindows(gWindow, gRenderer);
    green_planet.setWindows(gWindow, gRenderer);
    blue_planet.setWindows(gWindow, gRenderer);
    black_hole.setWindows(gWindow, gRenderer);

    
    //Loading success flag
    bool success = true;
    
    //Load splash textures
    
    if( !space_700.loadFromFile( "images/space_700x700.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship1_a.loadFromFile( "images/cyan_ship_a.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship1_b.loadFromFile( "images/cyan_ship_b.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship1_c.loadFromFile( "images/cyan_ship_c.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship1_d.loadFromFile( "images/cyan_ship_d.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship2_a.loadFromFile( "images/red_ship_a.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship2_b.loadFromFile( "images/red_ship_b.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship2_c.loadFromFile( "images/red_ship_c.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship2_d.loadFromFile( "images/red_ship_d.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship3_a.loadFromFile( "images/purple_ship_a.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship3_b.loadFromFile( "images/purple_ship_b.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship3_c.loadFromFile( "images/purple_ship_c.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship3_d.loadFromFile( "images/purple_ship_d.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship4_a.loadFromFile( "images/blue_ship_a.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship4_b.loadFromFile( "images/blue_ship_b.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship4_c.loadFromFile( "images/blue_ship_c.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship4_d.loadFromFile( "images/blue_ship_d.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship5_a.loadFromFile( "images/green_ship_a.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship5_b.loadFromFile( "images/green_ship_b.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship5_c.loadFromFile( "images/green_ship_c.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !ship5_d.loadFromFile( "images/green_ship_d.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !rock_100.loadFromFile( "images/rock_100.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !rock_66.loadFromFile( "images/rock_66.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !rock_33.loadFromFile( "images/rock_33.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !rock_11.loadFromFile( "images/rock_11.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !yellow_bullet.loadFromFile( "images/bullet_yellow.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !red_bullet.loadFromFile( "images/bullet_red.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !blue_laser_bullet.loadFromFile( "images/bullet_long_blue.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !blue_bullet.loadFromFile( "images/bullet_blue.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !purple_bullet.loadFromFile( "images/bullet_purple.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !brown_planet.loadFromFile( "images/brown_planet.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !blue_planet.loadFromFile( "images/blue_planet.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !green_planet.loadFromFile( "images/green_planet.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }
    if( !black_hole.loadFromFile( "images/black_hole3.png" ) )
    {
        SDL_Log( "Failed to load touch up texture!\n" );
        success = false;
    }

    
    space_700.mWidth = gScreenRect.w;
    space_700.mHeight = gScreenRect.h;
    
    ship1_a.mWidth *= 3;
    ship1_a.mHeight *= 3;
    
    ship1_b.mWidth *= 3;
    ship1_b.mHeight *= 3;
    
    ship1_c.mWidth *= 3;
    ship1_c.mHeight *= 3;
    
    ship1_d.mWidth *= 3;
    ship1_d.mHeight *= 3;
    
    ship2_a.mWidth *= 3;
    ship2_a.mHeight *= 3;
    
    ship2_b.mWidth *= 3;
    ship2_b.mHeight *= 3;
    
    ship2_c.mWidth *= 3;
    ship2_c.mHeight *= 3;
    
    ship2_d.mWidth *= 3;
    ship2_d.mHeight *= 3;
    
    ship3_a.mWidth *= 3;
    ship3_a.mHeight *= 3;
    
    ship3_b.mWidth *= 3;
    ship3_b.mHeight *= 3;
    
    ship3_c.mWidth *= 3;
    ship3_c.mHeight *= 3;
    
    ship3_d.mWidth *= 3;
    ship3_d.mHeight *= 3;
    
    ship4_a.mWidth *= 3;
    ship4_a.mHeight *= 3;
    
    ship4_b.mWidth *= 3;
    ship4_b.mHeight *= 3;
    
    ship4_c.mWidth *= 3;
    ship4_c.mHeight *= 3;
    
    ship4_d.mWidth *= 3;
    ship4_d.mHeight *= 3;
    
    ship5_a.mWidth *= 3;
    ship5_a.mHeight *= 3;
    
    ship5_b.mWidth *= 3;
    ship5_b.mHeight *= 3;
    
    ship5_c.mWidth *= 3;
    ship5_c.mHeight *= 3;
    
    ship5_d.mWidth *= 3;
    ship5_d.mHeight *= 3;
    
    rock_100.mWidth *= 3;
    rock_100.mHeight *= 3;
    
    rock_66.mWidth *= 3;
    rock_66.mHeight *= 3;
    
    rock_33.mWidth *= 3;
    rock_33.mHeight *= 3;
    
    rock_11.mWidth *= 3;
    rock_11.mHeight *= 3;
    
    yellow_bullet.mWidth *= 3;
    yellow_bullet.mHeight *= 3;
    
    red_bullet.mWidth *= 3;
    red_bullet.mHeight *= 3;
    
    
    purple_bullet.mWidth *= 3;
    purple_bullet.mHeight *= 3;
    
    blue_bullet.mWidth *= 3;
    blue_bullet.mHeight *= 3;
    
    blue_laser_bullet.mWidth *= 3;
    blue_laser_bullet.mHeight *= 3;
    
    black_hole.mWidth /= 2;
    black_hole.mHeight /= 2;
    
    //loading audio media
    
    
    //Load music
    
    gMusic = Mix_LoadMUS( "sounds/arcade-music-loop.wav" );
    
    
    //loading 8bit font
    
    gFont = TTF_OpenFont( "text/font.ttf", 80 );
    gTextTexture.font = gFont;
    message_red.font = gFont;
    level_num_texture.font = gFont;
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
        if( !gTextTexture.loadFromRenderedText( "deep space", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !message_red.loadFromRenderedText( "collected red crystal", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !level_num_texture.loadFromRenderedText( "1", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    
    
    
    return success;
}

void Game::close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


void Game::level_one()
{
    // SHORTCODE: LEVEL_ONE
    
    render_buttons(true, true, true, true, true);
    
    level_num_texture.render( ( gScreenRect.w - level_num_texture.mWidth ), 0 );
    
    //rendering button word
    
    SDL_Color textColor = { 255, 255, 255 };
    
    gTextTexture.loadFromRenderedText( "upgrades", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w / 40, (gScreenRect.h/20 - gTextTexture.mHeight/2));
    
    ship.handleEvent(buttons_status);
    int m = ship.move(rocks_1);
    
    if(m == -2)
    {
        enter_hole(ship, holes[0]);
        clear_holes();
        ship.clear_bullets();
        return;
    }
    else if(m != -1)
    {
        rocks_1.erase(rocks_1.begin() + m);
    }
    ship.render();

    int idx = (int)ship.bullets.size() - 1;
    for(int j = (int)rocks_1.size() - 1; j >= 0; j--)
    {
        rocks_1[j]->move(gScreenRect.w, gScreenRect.h);
    }
    for(int i = idx; i >= 0 ; i--)
    {
        int move = ship.bullets[i]->move(rocks_1, gScreenRect.w, gScreenRect.h);
        if(move == -1) ship.bullets[i]->render();
        else if(move == -2)
        {
            delete ship.bullets[i];
            ship.bullets.erase(ship.bullets.begin() + i);
        }
        else
        {
            if(rocks_1[move]->size == 100)
            {
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX + 50, rocks_1[move]->mPosY + 50, ship.bullets[i]->degrees+45, 66) );
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX - 50, rocks_1[move]->mPosY - 50, ship.bullets[i]->degrees, 66));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX + 50, rocks_1[move]->mPosY - 50, ship.bullets[i]->degrees-45, 66));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                
            }
            else if(rocks_1[move]->size == 66)
            {
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX + 33, rocks_1[move]->mPosY + 33, ship.bullets[i]->degrees-90, 33));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX - 30, rocks_1[move]->mPosY - 30, ship.bullets[i]->degrees+90, 33));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
            }
            else if(rocks_1[move]->size == 33)
            {
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX + 12, rocks_1[move]->mPosY + 12, ship.bullets[i]->degrees+45, 11));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX + 15, rocks_1[move]->mPosY - 15, ship.bullets[i]->degrees, 11));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
                
                rocks_1.push_back(new Rock(rocks_1[move]->mPosX - 17, rocks_1[move]->mPosY + 17, ship.bullets[i]->degrees-115, 11));
                rocks_1.back()->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
            }
            delete rocks_1[move];
            rocks_1.erase(rocks_1.begin() + move);
            
            delete ship.bullets[i];
            ship.bullets.erase(ship.bullets.begin() + i);
        }
    }
    for(int i = (int)rocks_1.size() - 1; i >= 0; i--)
    {
        rocks_1[i]->render();
    }
    for(int l = 0; l < (int)holes.size(); l++)
    {
        holes[l]->render();
        if(holes[l]->move(ship) == 1)
        {
            enter_hole(ship, holes[l]);
            clear_holes();
            ship.clear_bullets();
            break;
        }

    }
    
    if(rocks_1.size() == 0)
    {
        progress++;
        level++;
        for(int i = 0; i < level - 1; i++)
        {
            rocks_1.push_back(new Rock(gScreenRect.w/5 * i , gScreenRect.h/5 * i, 45*i*(-1*i), 100));
            rocks_1[i]->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
        }
        level_num.str( "" );
        level_num << level;
        SDL_Color textColor = { 255, 255, 255 };
        level_num_texture.loadFromRenderedText( level_num.str().c_str(), textColor );
    }
    if(buttons_status[4]) {
    
        progress = level;
        level = -3;
        buttons_status[4] = false;
        SDL_Delay( 150 );
        
    }

    
    
}

void Game::start_menu()
{
    // SHORTCODE: START MENU

    render_buttons(false, true, false, true, false);
    
    SDL_Color textColor = { 255, 255, 255 };
    
    
    
    
    
    gTextTexture.loadFromRenderedText( "deep space", textColor );
    
    gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
    
    
    
    
    gTextTexture.loadFromRenderedText( "controls", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w - gScreenRect.w/8 - gTextTexture.mWidth/2, (gScreenRect.h - gScreenRect.h/20) - gTextTexture.mHeight/2);
    
    
    
    gTextTexture.loadFromRenderedText( "play", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w / 8 - gTextTexture.mWidth/2, (gScreenRect.h - gScreenRect.h/20) - gTextTexture.mHeight/2);
    
    
    
    if(buttons_status[1]) level++;
    if(buttons_status[3]) level--; // switch level to CONTROLS menu
}

void Game::controls_menu()
{
    render_buttons(true, true, true, true, true );
    
    SDL_Color textColor = { 255, 255, 255 };
    
    gTextTexture.loadFromRenderedText( "play", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w / 8 - gTextTexture.mWidth/2, (gScreenRect.h/20 - gTextTexture.mHeight/2));
    
    
    if(buttons_status[0])
    {
        std::stringstream ss;
        ss << "charge shot";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
        
    }
    else if(buttons_status[1] && buttons_status[3])
    {
        std::stringstream ss;
        ss << "ignition";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        
        
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
        
    }
    else if(buttons_status[1])
    {
        std::stringstream ss;
        ss << "rotate left";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        
        
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
        
        int h_ = gTextTexture.getHeight();
        
        ss.str("");
        ss << "left + right = ignition";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        gTextTexture.mWidth /= 3;
        gTextTexture.mHeight /= 3;
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, (( gScreenRect.h - gTextTexture.getHeight() ) / 2) + h_ );
        
    }
    else if(buttons_status[2])
    {
        std::stringstream ss;
        ss << "fire";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
        
    }
    else if(buttons_status[3])
    {
        std::stringstream ss;
        ss << "rotate right";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        
        
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 2 );
        
        int h_ = gTextTexture.getHeight();
        
        ss.str("");
        ss << "left + right = ignition";
        gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
        gTextTexture.mWidth /= 3;
        gTextTexture.mHeight /= 3;
        gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, (( gScreenRect.h - gTextTexture.getHeight() ) / 2) + h_ );
        
    }
    
    
    
    if(buttons_status[4])
    {
        // play
        level = 0;
        buttons_status[4] = false;
        SDL_Delay( 500 );
    }
}


void Game::check_event()
{
    // SHORTCODE: TOUCH SCREEN

    //User requests quit
    if( e.type == SDL_QUIT )
    {
        quit = true;
    }
    //Window event
    else if( e.type == SDL_WINDOWEVENT )
    {
        //Window resize/orientation change
        if( e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
        {
            //Get screen dimensions
            gScreenRect.w = e.window.data1;
            gScreenRect.h = e.window.data2;
            
            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    }
    //Touch down
    else if( e.type == SDL_MULTIGESTURE )
    {
        multipos[0][0] = -10;
        multipos[0][1] = -10;
        multipos[1][0] = -10;
        multipos[1][1] = -10;
        SDL_TouchID device=SDL_GetTouchDevice(0);
        for(int i=0;i<SDL_GetNumTouchFingers(device);++i)
        {
            SDL_Finger *finger = SDL_GetTouchFinger(device,i);
            if(finger!=NULL)
            {
                multipos[i][0]=finger->x * gScreenRect.w;
                multipos[i][1]=finger->y * gScreenRect.h;
            }
        }
        
        if(multipos[0][0] > multipos[1][0] && multipos[1][0] != -10) // set multipos[0] to be left finger
        {
            double leftx, lefty, rightx, righty;
            
            rightx = multipos[0][0];
            righty = multipos[0][1];
            
            leftx = multipos[1][0];
            lefty = multipos[1][1];
            
            
            
            multipos[0][0] = leftx;
            multipos[0][1] = lefty;
            
            multipos[1][0] = rightx;
            multipos[1][1] = righty;
            
            
        }
        
        
        
        
        //left FINGER 1
        if(multipos[0][0] >= 0 && multipos[0][0] <= gScreenRect.w / 4)
        {
            if(multipos[0][1] >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && multipos[0][1] <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                buttons_status[0] = true;
            }
            else if(multipos[0][1] >= gScreenRect.h - (gScreenRect.h/10)
                    && multipos[0][1] <= gScreenRect.h)
            {
                buttons_status[1] = true;
            }
            else if(multipos[0][1] >= 0 && multipos[0][1] <= gScreenRect.h / 10)
            {
                buttons_status[4] = true;
            }
            else
            {
                //turn left buttons off
                buttons_status[0] = false;
                buttons_status[1] = false;
                buttons_status[4] = false;
            }
        }
        else
        {
            //turn left buttons off
            buttons_status[0] = false;
            buttons_status[1] = false;
            buttons_status[4] = false;
        }
        
        //right finger
        if(multipos[1][0] != -10){
            if(multipos[1][0] >= gScreenRect.w - gScreenRect.w / 4 && multipos[1][0] <= gScreenRect.w)
            {
                if(multipos[1][1] >= gScreenRect.h - (gScreenRect.h/10)*2.5
                   && multipos[1][1] <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
                {
                    buttons_status[2] = true;
                    
                }
                else if(multipos[1][1] >= gScreenRect.h - (gScreenRect.h/10)
                        && multipos[1][1] <= gScreenRect.h)
                {
                    buttons_status[3] = true;
                }
                else
                {
                    buttons_status[2] = false;
                    buttons_status[3] = false;
                }
            }
            else
            {
                buttons_status[2] = false;
                buttons_status[3] = false;
            }
        }
    }
    else if( e.type == SDL_FINGERDOWN )
    {
        touchLocation.x = e.tfinger.x * gScreenRect.w;
        touchLocation.y = e.tfinger.y * gScreenRect.h;
        if(touchLocation.x >= 0 && touchLocation.x <= gScreenRect.w / 4)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                buttons_status[0] = true;
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[1] = true;
            }
            else if(touchLocation.y >= 0
                    && touchLocation.y <= gScreenRect.h / 10)
            {
                buttons_status[4] = true;
            }
            else
            {
                buttons_status[0] = false;
                buttons_status[1] = false;
                buttons_status[4] = false;
            }
            
        }
        else if(touchLocation.x >= gScreenRect.w - gScreenRect.w / 4 && touchLocation.x <= gScreenRect.w)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                if(ship.fire){
                    buttons_status[2] = true;
                }
                
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[3] = true;
            }
            else
            {
                buttons_status[2] = false;
                buttons_status[3] = false;
            }
        }
        
    }
    //Touch motion
    else if( e.type == SDL_FINGERMOTION )
    {
        touchLocation.x = e.tfinger.x * gScreenRect.w;
        touchLocation.y = e.tfinger.y * gScreenRect.h;
        if(touchLocation.x >= 0 && touchLocation.x <= gScreenRect.w / 4)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                buttons_status[0] = true;
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[1] = true;
            }
            else if(touchLocation.y >= 0
                    && touchLocation.y <= gScreenRect.h / 10)
            {
                buttons_status[4] = true;
            }
            else
            {
                buttons_status[0] = false;
                buttons_status[1] = false;
                buttons_status[4] = false;
            }
        }
        else if(touchLocation.x >= gScreenRect.w - gScreenRect.w / 4 && touchLocation.x <= gScreenRect.w)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                if(ship.fire){
                    buttons_status[2] = true;
                }
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[3] = true;
            }
            else
            {
                buttons_status[2] = false;
                buttons_status[3] = false;
            }
        }
        else
        {
            buttons_status[0] = false;
            buttons_status[1] = false;
            buttons_status[2] = false;
            buttons_status[3] = false;
            buttons_status[4] = false;
        }
    }
    //Touch release
    if( e.type == SDL_FINGERUP )
    {
        ship.fire = true;
        
        touchLocation.x = e.tfinger.x * gScreenRect.w;
        touchLocation.y = e.tfinger.y * gScreenRect.h;
        
        if(touchLocation.x >= 0 && touchLocation.x <= gScreenRect.w / 4)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                buttons_status[0] = false;
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[1] = false;
            }
            else if(touchLocation.y >= 0
                    && touchLocation.y <= gScreenRect.h / 10)
            {
                buttons_status[4] = false;
            }
        }
        else if(touchLocation.x >= gScreenRect.w - gScreenRect.w / 4 && touchLocation.x <= gScreenRect.w)
        {
            if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)*2.5
               && touchLocation.y <= gScreenRect.h - (gScreenRect.h/10)*2.5 + (gScreenRect.h/10))
            {
                buttons_status[2] = false;
            }
            else if(touchLocation.y >= gScreenRect.h - (gScreenRect.h/10)
                    && touchLocation.y <= gScreenRect.h)
            {
                buttons_status[3] = false;
            }
            
        }
        if(level == -3)
        {
            left_right = true; //limiting rapid fire on upgrades menu
        }
    }
    
}

void Game::initiate(LTexture* textures[][4])
{
    
    
    // SHORTCODE: INITIATE
    
    Mix_PlayMusic( gMusic, -1 );
    ship.mPosX = gScreenRect.w / 2 - ship.SHIP_WIDTH / 2;
    ship.mPosY = gScreenRect.h / 3 * 2;

    ship.set_texture_array(textures[0], &yellow_bullet, &blue_laser_bullet);
    ship.upgrade_level = 0;
    
    ship.clear_bullets();
    clear_rocks();
    enter_zone();
    

    
    
    rocks_1.push_back(new Rock(gScreenRect.w/3 - 100, gScreenRect.h/8 + 100, 45, 66));
    rocks_1[0]->set_texture(&rock_100, &rock_66, &rock_33, &rock_11);
    level++;
    level_num.str( "" );
    level_num << level;
    SDL_Color textColor = { 255, 255, 255 };
    gTextTexture.loadFromRenderedText( level_num.str().c_str(), textColor );
    
}


void Game::render_buttons(bool a, bool b, bool c, bool d, bool e)
{
    if(a)
    {
        if(buttons_status[0]) SDL_SetRenderDrawColor( gRenderer, 211, 211, 211, 80 );
        
        else if(ship.charge > 49) SDL_SetRenderDrawColor( gRenderer, 1, 36, 59, 80 );
        
        else SDL_SetRenderDrawColor( gRenderer, 112,128,144, 80 );
        
        button.x = 0;
        button.y = gScreenRect.h - (gScreenRect.h/10)*2.5;
        SDL_RenderFillRect(gRenderer, &button);
    }
    if(b)
    {
        if(buttons_status[1]) SDL_SetRenderDrawColor( gRenderer, 211, 211, 211, 80 );
        
        else SDL_SetRenderDrawColor( gRenderer, 112,128,144, 80 );
        
        button.x = 0;
        button.y = gScreenRect.h - (gScreenRect.h/10);
        SDL_RenderFillRect(gRenderer, &button);
    }
    if(c)
    {
        if(buttons_status[2]) SDL_SetRenderDrawColor( gRenderer, 211, 211, 211, 80 );
        
        else SDL_SetRenderDrawColor( gRenderer, 112,128,144, 80 );
        
        button.x = (gScreenRect.w / 4) * 3;
        button.y = gScreenRect.h - (gScreenRect.h/10)*2.5;
        SDL_RenderFillRect(gRenderer, &button);
    }
    if(d)
    {
        if(buttons_status[3]) SDL_SetRenderDrawColor( gRenderer, 211, 211, 211, 80 );
        
        else SDL_SetRenderDrawColor( gRenderer, 112,128,144, 80 );
        
        button.x = (gScreenRect.w / 4) * 3;
        button.y = gScreenRect.h - gScreenRect.h/10;
        SDL_RenderFillRect(gRenderer, &button);
    }
    if(e)
    {
        if(buttons_status[4]) SDL_SetRenderDrawColor( gRenderer, 211, 211, 211, 80 );
        
        else SDL_SetRenderDrawColor( gRenderer, 112,128,144, 80 );
        
        button.x = 0;
        button.y = 0;
        SDL_RenderFillRect(gRenderer, &button);
    }
    
}

void Game::fly_away_animation()
{
    // SHORTCODE: FLY AWAY

    ship.clear_bullets();
    
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    while(ship.degrees != 270)
    {
        if(ship.degrees >= 270)
        {
            ship.degrees = 270;
        }
        else
        {
            ship.degrees += 8;
        }
        SDL_RenderClear( gRenderer );
        
        
        space_700.render(0, 0);
        ship.render();
        
        SDL_RenderPresent( gRenderer );
        

    }
    while(ship.mPosY + ship.SHIP_HEIGHT * 2 > 0)
    {
        ship.mPosY -= ship.SHIP_PROPULSION;
        ship.SHIP_PROPULSION += 0.05;
        SDL_RenderClear( gRenderer );
        
        
        space_700.render(0, 0);
        ship.render();
        
        SDL_RenderPresent( gRenderer );
    }
    ship.degrees = 270;
    ship.SHIP_PROPULSION = 0;
    ship.mPosY = (gScreenRect.h - ship.SHIP_HEIGHT) - (gScreenRect.h / 4);
    ship.mPosX = (gScreenRect.w - ship.SHIP_WIDTH) / 2;
    SDL_Delay( 1000 );
}

void Game::approach_planet(int planet)
{
    // SHORTCODE: APPROACH PLANET

    
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    ship.degrees = 270;
    ship.SHIP_PROPULSION = 7;
    ship.mPosY = gScreenRect.h + ship.SHIP_HEIGHT;
    ship.mPosX = (gScreenRect.w - ship.SHIP_WIDTH) / 2;
    
    int ship_text_w = ship.textures[0]->mWidth;
    int ship_text_h = ship.textures[0]->mHeight;
    
    int rotation = 0;
    bool once = true;
    while(ship.mPosY > gScreenRect.h / 2 + ship_text_h)
    {
        if(ship.SHIP_PROPULSION < 0.25)
        {
            ship.SHIP_PROPULSION = 0.25;
        }
        ship.mPosY -= 2*ship.SHIP_PROPULSION;
        ship.SHIP_PROPULSION -= 0.055;
        
        if(ship.mPosY < gScreenRect.h / 4 * 3)
        {
            if(rotation == 0)
            {
                
                ship.textures[0]->mWidth*=0.9;
                ship.textures[0]->mHeight*=0.9;
            
                ship.textures[1]->mWidth*=0.9;
                ship.textures[1]->mHeight*=0.9;
            
                ship.textures[2]->mWidth*=0.9;
                ship.textures[2]->mHeight*=0.9;
            
                ship.textures[3]->mWidth*=0.9;
                ship.textures[3]->mHeight*=0.9;
                rotation = 8;
            }
            rotation--;
        }
        
        SDL_RenderClear( gRenderer );
        
        
        space_700.render(0, 0);
        if(planet == 1) brown_planet.render(gScreenRect.w / 3, (gScreenRect.h - brown_planet.mHeight)/ 2);
        else if(planet == 2) blue_planet.render(gScreenRect.w / 3, (gScreenRect.h - blue_planet.mHeight)/ 2);
        else if(planet == 3) green_planet.render(gScreenRect.w / 3, (gScreenRect.h - green_planet.mHeight)/ 2);
        ship.render();
        
        SDL_RenderPresent( gRenderer );
        if(once)
        {
            SDL_Delay(1000);
            once = false;
        }
    }
    
    ship.textures[0]->mWidth = ship_text_w;
    ship.textures[0]->mHeight = ship_text_h;
    
    ship.textures[1]->mWidth = ship_text_w;
    ship.textures[1]->mHeight = ship_text_h;
    
    ship.textures[2]->mWidth = ship_text_w;
    ship.textures[2]->mHeight = ship_text_h;
    
    ship.textures[3]->mWidth = ship_text_w;
    ship.textures[3]->mHeight = ship_text_h;
    
    ship.degrees = 270;
    
    ship.SHIP_PROPULSION = 0;
    
    
    

    SDL_Color textColor = { 255, 255, 255 };
    
    if(planet == 1) message_red.loadFromRenderedText( "collected a red crystal", textColor );
    if(planet == 2) message_red.loadFromRenderedText( "retrieved a purple dark matter converter", textColor );
    if(planet == 3) message_red.loadFromRenderedText( "happened upon a blue time diffuser", textColor );
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );
    
    
    
    SDL_RenderClear( gRenderer );
    
    


    message_red.mWidth /= 3;
    message_red.mHeight /= 3;
    
    message_box.x = ( gScreenRect.w - message_red.getWidth() ) / 2  - (message_red.getWidth()*0.25);
    message_box.y = ( gScreenRect.h - message_red.getHeight() ) / 2 - message_red.getHeight()*1.5;
    message_box.w = message_red.mWidth * 1.5;
    message_box.h = message_red.mHeight * 5;
    
    space_700.render(0, 0);
    if(planet == 1) brown_planet.render(gScreenRect.w / 3, (gScreenRect.h - brown_planet.mHeight)/ 2);
    else if(planet == 2) blue_planet.render(gScreenRect.w / 3, (gScreenRect.h - blue_planet.mHeight)/ 2);
    else if(planet == 3) green_planet.render(gScreenRect.w / 3, (gScreenRect.h - green_planet.mHeight)/ 2);
    
    SDL_RenderFillRect(gRenderer, &message_box);
    
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 100 );

    SDL_RenderDrawRect(gRenderer, &message_box);
    
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );

    message_red.render( ( gScreenRect.w - message_red.getWidth() ) / 2, ( gScreenRect.h - message_red.getHeight() ) / 2 );
    
    SDL_RenderPresent( gRenderer );

    SDL_Delay( 2000 );
}

void Game::enter_zone()
{
    SDL_RenderClear( gRenderer );
    space_700.render(0, 0);
    SDL_RenderPresent( gRenderer );

    ship.degrees = 270;
    ship.mPosX = gScreenRect.w / 2 - ship.SHIP_WIDTH / 2;
    ship.mPosY = gScreenRect.h + 5;
    ship.SHIP_PROPULSION = 3;
    while(ship.mPosY > gScreenRect.h/3*2)
    {
        
        ship.mPosY -= ship.SHIP_PROPULSION;
        
        ship.SHIP_PROPULSION -= 0.00001;
        
        SDL_RenderClear( gRenderer );
        space_700.render(0, 0);
        ship.render();
        SDL_RenderPresent( gRenderer );
    }
    ship.SHIP_PROPULSION = 0;
}
void Game::enter_hole(Ship& ship, Black_Hole* hole)
{
    
    // SHORTCODE: ENTER HOLE

    
    SDL_RenderClear( gRenderer );
    space_700.render(0, 0);
    hole->render();
    SDL_RenderPresent( gRenderer );
    
    
    ship.SHIP_PROPULSION = 0.3;
    
    int ship_text_w = ship.textures[2]->mWidth;
    int ship_text_h = ship.textures[2]->mHeight;
    
    int rotation = 0;
    bool not_done = true;
    while(ship.mPosY + ship.textures[2]->mHeight/2 != hole->mPosY + hole->hole_texture->mHeight && ship.mPosX + ship.textures[2]->mWidth/2 != hole->mPosX + hole->hole_texture->mWidth && not_done)
    {
        SDL_RenderClear( gRenderer );
        space_700.render(0, 0);
        hole->render();
        hole->move(ship);
        ship.render();
        SDL_RenderPresent( gRenderer );
        
        
        ship.degrees-=2;
        if(ship.mPosY + ship.textures[2]->mHeight/2 < hole->mPosY + hole->hole_texture->mHeight/2) // ship N of hole
        {
            ship.mPosY++;
            if(ship.mPosX + ship.textures[2]->mWidth/2 < hole->mPosX + hole->hole_texture->mWidth/2)// ship NW of hole
            {
                ship.mPosX++;
            }
            else if(ship.mPosX + ship.textures[2]->mWidth/2 > hole->mPosX + hole->hole_texture->mWidth/2)// ship NE of hole
            {
                ship.mPosX--;
            }
            else // ship on correct x
            {
                
            }
        }
        else if(ship.mPosY + ship.textures[2]->mHeight/2 > hole->mPosY + hole->hole_texture->mHeight/2)
        {
            ship.mPosY--;
            if(ship.mPosX + ship.textures[2]->mWidth/2 < hole->mPosX + hole->hole_texture->mWidth/2)
            {
                ship.mPosX++;
            }
            else if(ship.mPosX + ship.textures[2]->mWidth/2 > hole->mPosX + hole->hole_texture->mWidth/2)
            {
                ship.mPosX--;
            }
            else
            {
                
            }
        }
        else //ship on correct y
        {
            if(ship.mPosX + ship.textures[2]->mWidth/2 < hole->mPosX + hole->hole_texture->mWidth/2)
            {
                ship.mPosX++;
            }
            else if(ship.mPosX + ship.textures[2]->mWidth/2 > hole->mPosX + hole->hole_texture->mWidth/2)
            {
                ship.mPosX--;
            }
            else
            {
                //SHIP SHOULD DISAPPEAR AND GAME OVER
            }
        }
        if(rotation == 3)
        {
            ship.textures[0]->mWidth*=0.99999999999;
            ship.textures[0]->mHeight*=0.85;
        
            ship.textures[1]->mWidth*=0.99999999999;
            ship.textures[1]->mHeight*=0.85;
        
            ship.textures[2]->mWidth*=0.99999999999;
            ship.textures[2]->mHeight*=0.85;
        
            ship.textures[3]->mWidth*=0.99999999999;
            ship.textures[3]->mHeight*=0.85;
            rotation = 0;
        }
        rotation++;
        
        if(ship.textures[2]->mWidth < ship_text_w * 0.1)
        {
            restart_game();
            not_done = false;
        }
    }
    
    ship.SHIP_PROPULSION = 0;
    
    ship.textures[0]->mWidth = ship_text_w;
    ship.textures[0]->mHeight = ship_text_h;
    
    ship.textures[1]->mWidth = ship_text_w;
    ship.textures[1]->mHeight = ship_text_h;
    
    ship.textures[2]->mWidth = ship_text_w;
    ship.textures[2]->mHeight = ship_text_h;
    
    ship.textures[3]->mWidth = ship_text_w;
    ship.textures[3]->mHeight = ship_text_h;
    
    
}
void Game::upgrades_menu(LTexture* textures[][4])
{
    
    // SHORTCODE: UPGRADES MENU

    render_buttons(true, true, true, true, false );
    
    SDL_Color textColor = { 255, 255, 255 };
    
    
    
    
    //print play on button 0
    gTextTexture.loadFromRenderedText( "play", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w / 8 - gTextTexture.mWidth/2, (gScreenRect.h - (gScreenRect.h/10)*2.5)+gScreenRect.h/20 - gTextTexture.mHeight/2    );
    
    
    
    
    //print left on button 1
    gTextTexture.loadFromRenderedText( "left", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w / 8 - gTextTexture.mWidth/2, (gScreenRect.h - gScreenRect.h/20) - gTextTexture.mHeight/2);


    
    //print select on button 2
    gTextTexture.loadFromRenderedText( "select", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w - gScreenRect.w/8 - gTextTexture.mWidth/2, (gScreenRect.h - (gScreenRect.h/10)*2.5)+gScreenRect.h/20 - gTextTexture.mHeight/2 );
    

    
    //print right on button 3
    gTextTexture.loadFromRenderedText( "right", textColor );
    
    gTextTexture.mWidth /= 3;
    gTextTexture.mHeight /= 3;
    
    gTextTexture.render( gScreenRect.w - gScreenRect.w/8 - gTextTexture.mWidth/2, (gScreenRect.h - gScreenRect.h/20) - gTextTexture.mHeight/2);
    

    
    //print upgrades as screen title
    gTextTexture.loadFromRenderedText( "upgrades", textColor );
    
    gTextTexture.mWidth /= 2;
    gTextTexture.mHeight /= 2;
    
    
    gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 6 );
    
    //print menu pointer number
    std::stringstream ss;
    ss << menu_pointer;
    gTextTexture.loadFromRenderedText( ss.str().c_str(), textColor );
    
    gTextTexture.mWidth /= 2;
    gTextTexture.mHeight /= 2;
    
    gTextTexture.render( ( gScreenRect.w - gTextTexture.getWidth() ) / 2, ( gScreenRect.h - gTextTexture.getHeight() ) / 3 * 2 + gTextTexture.getHeight() * 2 );
    
    
    SDL_Rect upgrade_preview;
    
    upgrade_preview.w = gScreenRect.w / 2;
    upgrade_preview.h = gScreenRect.h / 3;
    
    upgrade_preview.x = ( gScreenRect.w - upgrade_preview.w ) / 2;
    upgrade_preview.y = ( gScreenRect.h - upgrade_preview.h ) / 2;
    
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );
    
    SDL_RenderFillRect(gRenderer, &upgrade_preview);
    
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 100 );
    
    SDL_RenderDrawRect(gRenderer, &upgrade_preview);
    
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );

    if(unlocks[menu_pointer])
    {
        //render image of this upgrade level ship
        textures[menu_pointer][3]->mWidth *= 1.5;
        textures[menu_pointer][3]->mHeight *= 1.5;
        
        textures[menu_pointer][3]->render( gScreenRect.w/2 - textures[menu_pointer][3]->mWidth /2, gScreenRect.h/2 - textures[menu_pointer][3]->mHeight /2 - upgrade_preview.h / 4, NULL, 270, NULL, SDL_FLIP_NONE );
        
        textures[menu_pointer][3]->mWidth = textures[menu_pointer][2]->mWidth;
        textures[menu_pointer][3]->mHeight = textures[menu_pointer][2]->mHeight;
        
        if(menu_pointer == 0)
        {
            gTextTexture.loadFromRenderedText( "cyan ship", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2);
            
            int h = gTextTexture.mHeight*3;
            
            gTextTexture.loadFromRenderedText( "standard shot", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
            
            gTextTexture.loadFromRenderedText( "no charge shot", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
        }
        if(menu_pointer == 1)
        {
            gTextTexture.loadFromRenderedText( "red ship", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2);
            
            int h = gTextTexture.mHeight*3;
            
            gTextTexture.loadFromRenderedText( "spread shot", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
            
            gTextTexture.loadFromRenderedText( "rapid fire", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
        }
        if(menu_pointer == 2)
        {
            gTextTexture.loadFromRenderedText( "purple ship", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2);
            
            int h = gTextTexture.mHeight*3;
            
            gTextTexture.loadFromRenderedText( "laser beam", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
            
            gTextTexture.loadFromRenderedText( "explosive nova", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
        }
        if(menu_pointer == 3)
        {
            gTextTexture.loadFromRenderedText( "blue ship", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2);
            
            int h = gTextTexture.mHeight*3;
            
            gTextTexture.loadFromRenderedText( "swarm shot", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
            
            gTextTexture.loadFromRenderedText( "to be determined", textColor );
            
            gTextTexture.mWidth /= 3;
            gTextTexture.mHeight /= 3;
            
            
            
            gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2 + upgrade_preview.h/4 + h);
            
            h += gTextTexture.mHeight*1.5;
        }
        
    }
    else
    {
        //render big '?' with upgrade #
        //print upgrades as screen title
        gTextTexture.loadFromRenderedText( "keep exploring", textColor );
        
        gTextTexture.mWidth /= 3;
        gTextTexture.mHeight /= 3;
        
        
        gTextTexture.render( gScreenRect.w/2 - gTextTexture.mWidth /2, gScreenRect.h/2 - gTextTexture.mHeight /2);
        
    }
    
    
    
    
    if(buttons_status[0])
    {
        //go back to playing
        level = progress;
    }
    else if(buttons_status[1])
    {
        //move selecter left
        if(menu_pointer == 0)
        {
            
        }
        else
        {
            if(left_right)
            {
                menu_pointer--;
                left_right = false;
            }
        }
    }
    else if(buttons_status[2])
    {
        if(unlocks[menu_pointer])
        {
            ship.upgrade_level = menu_pointer;
            if(menu_pointer == 3)
            {
                ship.set_texture_array(textures[menu_pointer], &purple_bullet, &blue_bullet);
            }
            else ship.set_texture_array(textures[menu_pointer], &yellow_bullet, &blue_laser_bullet);
            
        }
    }
    else if(buttons_status[3])
    {
        //move selecter right
        if(menu_pointer == 5)
        {
            
        }
        else
        {
            if(left_right)
            {
                menu_pointer++;
                left_right = false;
            }
        }

    }
    
}

void Game::restart_game()
{

    // SHORTCODE: RESTART GAME

    
    SDL_Color textColor = { 255, 255, 255 };
    
    message_red.loadFromRenderedText( "fell to the deep space", textColor );

    
    
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );
    
    
    
    SDL_RenderClear( gRenderer );
    
    
    
    
    message_red.mWidth /= 3;
    message_red.mHeight /= 3;
    
    message_box.x = ( gScreenRect.w - message_red.getWidth() ) / 2  - (message_red.getWidth()*0.25);
    message_box.y = ( gScreenRect.h - message_red.getHeight() ) / 2 - message_red.getHeight()*1.5;
    message_box.w = message_red.mWidth * 1.5;
    message_box.h = message_red.mHeight * 5;
    
    space_700.render(0, 0);
    
    SDL_RenderFillRect(gRenderer, &message_box);
    
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 100 );
    
    SDL_RenderDrawRect(gRenderer, &message_box);
    
    SDL_SetRenderDrawColor( gRenderer, 1, 1, 1, 100 );
    
    message_red.render( ( gScreenRect.w - message_red.getWidth() ) / 2, ( gScreenRect.h - message_red.getHeight() ) / 2 );
    
    SDL_RenderPresent( gRenderer );
    
    SDL_Delay( 1500 );

    level = -1;
    
    level_num.str( "" );
    level_num << "1";

    level_num_texture.loadFromRenderedText( level_num.str().c_str(), textColor );
    
}
// SHORTCODE: CLEARING VECTORS

void Game::clear_rocks()
{
    for(int i = (int)rocks_1.size() - 1; i >= 0; i--)
    {
        delete rocks_1[i];
        rocks_1.erase(rocks_1.begin() + i);
    }
}
void Game::clear_holes()
{
    for(int i = (int)holes.size() - 1; i >= 0; i--)
    {
        delete holes[i];
        holes.erase(holes.begin() + i);
    }
}
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/





#endif