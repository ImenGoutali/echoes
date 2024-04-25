#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "imen.h"

int main(int argc, char **argv)
{
    int tentative = 3;
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    // Set the font for the primitives drawing routines
    gfxPrimitivesSetFont(NULL, 0, 0);
    // Zoom the image by a factor of 2
    SDL_Surface *zoomed = NULL;
    // Création de la surface de l'écran
    SDL_Surface *ecran = SDL_SetVideoMode(300, 300, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Erreur lors de la création de la surface de l'écran : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de la structure tic
    tic t;
    initialiserTic(&t);

    // Variable pour la boucle principale
    int continuer = 1;
    int x, y, coup;
    int i = 1;
    //-----audio
    Mix_HaltMusic();
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000);
    t.music = Mix_LoadMUS("click.mp3"); // emplcament musique 1

    //----------------

    // Boucle principale du jeu
    while (continuer)
    {
        // Affichage des images sur l'écran
 printf("t.tabsuivi table: num tour = %d,tentaive=%d\n",t.num_tour,tentative);
    for (int i = 0; i < 9; i++) {
        printf("%d ", t.tabsuivi[i]);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
     
        // Si conditions selon votre algorithme
        if (t.num_tour < 9 && atilgagner(t.tabsuivi) == 0&&tentative>0)
        {
            afficherTic(t, ecran);

            if (t.num_tour % 2 == 1)
            { // Tour du PC
                calcul_coup(t.tabsuivi);
                t.num_tour++;
            }
            else
            {
                SDL_Event event;
                SDL_WaitEvent(&event);
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    Mix_PlayMusic(t.music, 1); // -1 to loop indefinitely

                    x = event.button.x / 95;
                    y = event.button.y / 95;
                    coup = 3 * y + x;
                    t.tabsuivi[coup] = -1;

                    t.num_tour++;
                }
                else if (event.type == SDL_QUIT)
                {
                    continuer = 0;
                }
                else if (event.type == SDL_KEYDOWN)
                {                              // Keyboard button pressed
                    Mix_PlayMusic(t.music, 1); // -1 to loop indefinitely
                    t.num_tour++;
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_KP1: // Numpad 1
                        if (t.tabsuivi[6] == 0)
                        {
                            t.tabsuivi[6] = -1;
                        }
                        break;
                    case SDLK_KP2: // Numpad 2
                        if (t.tabsuivi[7] == 0)
                        {
                            t.tabsuivi[7] = -1;
                        }
                        break;
                    case SDLK_KP3: // Numpad 3
                        if (t.tabsuivi[8] == 0)
                        {
                            t.tabsuivi[8] = -1;
                        }
                        break;
                    case SDLK_KP4: // Numpad 4
                        if (t.tabsuivi[3] == 0)
                        {
                            t.tabsuivi[3] = -1;
                        }
                        break;
                    case SDLK_KP5: // Numpad 5
                        if (t.tabsuivi[4] == 0)
                        {
                            t.tabsuivi[4] = -1;
                        }
                        break;
                    case SDLK_KP6: // Numpad 6
                        if (t.tabsuivi[5] == 0)
                        {
                            t.tabsuivi[5] = -1;
                        }
                        break;
                    case SDLK_KP7: // Numpad 7
                        if (t.tabsuivi[0] == 0)
                        {
                            t.tabsuivi[0] = -1;
                        }
                        break;
                    case SDLK_KP8: // Numpad 8
                        if (t.tabsuivi[1] == 0)
                        {
                            t.tabsuivi[1] = -1;
                        }
                        break;
                    case SDLK_KP9: // Numpad 9
                        if (t.tabsuivi[2] == 0)
                        {
                            t.tabsuivi[2] = -1;
                        }
                        break;
                    }
                }
            }
        }
        else
        {

            if (i == 1)
            {
    int resultat = atilgagner(t.tabsuivi);
            
                Resultat(t.tabsuivi, ecran);
                SDL_Delay(3000);
                 if (resultat == -1) {tentative=0;}else {
           tentative--;
            if(tentative>0){
                 
               for (int k=0 ;k<9;k++)
{t.tabsuivi[k]=0 ;}}
t.num_tour=0;
  t.joueur=1; 
}
         
            }
            
           
            //---------------------------
           if(tentative<=0){ 
          i = 0;
             int resultat = atilgagner(t.tabsuivi);
              printf("d5aler =%d\n",resultat);
            if (resultat == -1) // keno jeweb s 7i7e
            { 
                 static float zoom_factor = 1.0;                                          // nzoomi melowel b 1.0
                zoom_factor += 0.01;                                                     // zoome yemchi w yekber 0 0.01
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));     // n aficher background bidhe
                zoomed = zoomSurface(t.won.img, zoom_factor, zoom_factor, SMOOTHING_ON); // nesna3 surface jdida eli b zoom jdidee
                int x = (ecran->w / 2) - (zoomed->w / 2);                                // ne7seb l x eli fel woset
                int y = (ecran->h / 2) - (zoomed->h / 2);                                // ne7seb l y eli fel wose
                SDL_Rect dest = {x, y, zoomed->w, zoomed->h};                            // nrake7 destination ween bech naffiche fi screen
                SDL_BlitSurface(zoomed, NULL, ecran, &dest);      
                              
                               if(zoom_factor>2) {return 0;}
                                    SDL_Flip(ecran);
             }
            else if (resultat == 1 || resultat == -5) // keno jeweb bel 8alet
            {
                 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));                      // n aficher background bidhe
                static double angle = 0.0;                                                                // angel de routage melowel 0.0
                SDL_Surface *rotated_img = rotozoomSurface(t.lost.img, angle, 1.0, 0);                    // nrotate l image
                SDL_Rect rect = {(ecran->w - rotated_img->w) / 2, (ecran->h - rotated_img->h) / 2, 0, 0}; // destination cordinate
                SDL_BlitSurface(rotated_img, NULL, ecran, &rect);                                         // naffiche l image jdida b rotate
                SDL_FreeSurface(rotated_img);
                angle += 0.1; // nzeed fel angle de routage 
                    if(angle>20) {return 0;}
                         SDL_Flip(ecran);
            } }
            //----------------------------
            // Check for SDL_QUIT after displaying result
            SDL_Event event;
            SDL_WaitEvent(&event);
            if (event.type == SDL_QUIT)
            {
                continuer = 0;
            }
        }
        SDL_Flip(ecran);
    }

    // Libération des ressources et fin du programme
    liberer(t);
    SDL_Quit();
    TTF_Quit();
    return EXIT_SUCCESS;
}
