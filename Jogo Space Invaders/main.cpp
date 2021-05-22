#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> 
#include<allegro5/allegro_image.h>   
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>                        
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

 //variaveis-------------------------------------------------------------------------------
    double pos = 0,pos2 = 0;
    int cont= 0;
    int nivel = 1;
    int Largura_t = 960;
    int Altura_t = 720;   
    int pos_x = Altura_t/2;
    int pos_y =650;
    bool aniarma = false;
    int NUM_MORCEGO = 7,VEL_MORCEGO = 3,CM = 600; 
    int NUM_INIMIGOS_FASE = 20;
    const int NUM_BALAS = 5; 
    const int FPS = 60;
    int inc = 0;
    
       ALLEGRO_SAMPLE *trilha_sonora2 = NULL;
       ALLEGRO_SAMPLE *trilha_sonora = NULL;
       ALLEGRO_SAMPLE *trilha_sonora_menu = NULL;
       ALLEGRO_SAMPLE_INSTANCE *inst_trilha_sonora = NULL;
       ALLEGRO_SAMPLE_INSTANCE *inst_trilha_sonora2 = NULL;
       ALLEGRO_SAMPLE_INSTANCE *inst_trilha_sonora_menu = NULL;
       ALLEGRO_BITMAP *img = NULL;
       ALLEGRO_BITMAP *img1 = NULL;
       ALLEGRO_BITMAP *img2 = NULL;
       ALLEGRO_BITMAP *img3 = NULL;
       ALLEGRO_BITMAP *img4 = NULL; 

//-----------------------------------------------------------------------------------------
 enum IDS {JOGADOR,PROJETIL,INIMIGOS}; 
 enum TECLAS {DIREITA, ESQUERDA,SPACE};
//----------------OBJETOS------------------------------

int Menu(ALLEGRO_DISPLAY *display,ALLEGRO_FONT *font20){
   bool hover[3] = {false,false,false},click[3] = {false,false,false};
   bool tf = false,tc = false;
   float pos_x = 0.0,pos_y = 0.0;
   float img1_x = Largura_t/4,img1_y = (Altura_t * 0.2),img2_x = Largura_t/4,img2_y = Altura_t * 0.4,img3_x = Largura_t/4,img3_y =Altura_t * 0.6;
   int fim = 0,at_btn,lg_btn,at_btn2,lg_btn2,btn2 = 0;
   ALLEGRO_EVENT_QUEUE *fila_menu = NULL;
   ALLEGRO_EVENT_QUEUE *tela = NULL;   
     ALLEGRO_BITMAP *bg = NULL;
     ALLEGRO_BITMAP *btn = NULL;
     ALLEGRO_BITMAP *btn_hover = NULL;
     ALLEGRO_BITMAP *btn_click = NULL;
     ALLEGRO_BITMAP *btn_sobre = NULL;
     ALLEGRO_BITMAP *btn_sobre_hover = NULL;
     ALLEGRO_BITMAP *btn_sobre_click = NULL;
     ALLEGRO_BITMAP *btn_sair = NULL;
     ALLEGRO_BITMAP *btn_sair_hover = NULL;
     ALLEGRO_BITMAP *btn_sair_click = NULL;    
      al_install_keyboard();
 al_install_mouse();
 al_init_primitives_addon();
 al_init_font_addon();
 al_init_ttf_addon();
 al_init_image_addon(); 
//criaçao da fila de eventos
  fila_menu = al_create_event_queue();
 //registro do evento
 al_register_event_source(fila_menu,al_get_keyboard_event_source());
 al_register_event_source(fila_menu,al_get_mouse_event_source());
 
 //Carregamento das imagens e fonts
 
   

  btn = al_load_bitmap("comecar/btn.png");
  btn_hover = al_load_bitmap("comecar/btn_ver.png");
  btn_click = al_load_bitmap("comecar/btn_ver_click.png");
  btn_sobre = al_load_bitmap("comecar/btn_sobre.png");
  btn_sobre_hover = al_load_bitmap("comecar/btn_sobre_ver.png");
  btn_sobre_click = al_load_bitmap("comecar/btn_sobre_ver_click.png");
  btn_sair = al_load_bitmap("comecar/btn_sair.png");
  btn_sair_hover = al_load_bitmap("comecar/btn_sair_ver.png");
  btn_sair_click = al_load_bitmap("comecar/btn_sair_ver_click.png");
  bg = al_load_bitmap("casa_opaca.png");
  trilha_sonora_menu = al_load_sample("musica do menu.ogg");
  inst_trilha_sonora_menu = al_create_sample_instance(trilha_sonora_menu);
  al_attach_sample_instance_to_mixer(inst_trilha_sonora_menu, al_get_default_mixer());
  al_set_sample_instance_playmode(inst_trilha_sonora_menu, ALLEGRO_PLAYMODE_LOOP);
  al_set_sample_instance_gain(inst_trilha_sonora_menu, 2.8);
  
 //dimensões das imagens
  lg_btn2 = al_get_bitmap_width(btn);
  at_btn2 = al_get_bitmap_height(btn);
 //Criação do grafico inicial do Jogo/menu
  al_draw_scaled_bitmap(bg,0,0,640,480,0,0,Largura_t,Altura_t,0);
  al_draw_text(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t * 0.1,ALLEGRO_ALIGN_CENTRE,"MORCELANDIA UFG");
  al_draw_scaled_bitmap(btn,0,0,lg_btn2,at_btn2,img1_x,img1_y,Largura_t/2,Altura_t/8,0);
  al_draw_scaled_bitmap(btn_sobre,0,0,lg_btn2,at_btn2,img2_x,img2_y,Largura_t/2,Altura_t/8,0);
  al_draw_scaled_bitmap(btn_sair,0,0,lg_btn2,at_btn2,img3_x,img3_y,Largura_t/2,Altura_t/8,0);
 al_flip_display();  
 al_play_sample_instance(inst_trilha_sonora_menu);
 al_hide_mouse_cursor(display);
  while(fim != 1 && fim != 2){
 //--------------LOGICA DO JOGO------------------------ 
   ALLEGRO_EVENT e;
   al_wait_for_event(fila_menu,&e);

   if(e.type == ALLEGRO_EVENT_KEY_DOWN){
              if(e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                    fim = 2;
              }
              if(e.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                         fim = 2;
                         } 
     }
              
            
else if(e.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
   if((pos_x >= img1_x && pos_x <= img1_x+300)&& (pos_y >= img1_y && pos_y <= img1_y+75)){
     click[0] = true;         
 }     
  if(e.mouse.button & 1 && (pos_x >= img2_x && pos_x <= img2_x+300)&& (pos_y >= img2_y && pos_y <= img2_y+75)){
   btn2 = 1;
 }
 if(e.mouse.button & 1 && (pos_x >= img3_x && pos_x <= img3_x+300)&& (pos_y >= img3_y && pos_y <= img3_y+75)){
  click[2] = true;
                 
 }    
}

   
else if(e.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
 if((pos_x >= img1_x && pos_x <= img1_x+300)&& (pos_y >= img1_y && pos_y <= img1_y+75)){
     click[0] = false;
 }
 if((pos_x >= img2_x && pos_x <= img2_x+300)&& (pos_y >= img2_y && pos_y <= img2_y+75)){
     btn2 = 0;
 }
 if((pos_x >= img3_x && pos_x <= img3_x+300)&& (pos_y >= img3_y && pos_y <= img3_y+75)){
     click[2] = false;
 }         
 
}
else if(e.type == ALLEGRO_EVENT_MOUSE_AXES){
 pos_x = e.mouse.x;    
 pos_y = e.mouse.y;
 
 if((pos_x >= img1_x && pos_x <= img1_x+300)&& (pos_y >= img1_y && pos_y <= img1_y+75)){
   hover[0] = true;      
  }
  else{
       hover[0] = false;
       click[0] = false;
       }
  if((pos_x >= img2_x && pos_x <= img2_x+300)&& (pos_y >= img2_y && pos_y <= img2_y+75)){
   btn2 = 2;      
  }
  else{
       btn2 = 0;
       }
 if((pos_x >= img3_x && pos_x <= img3_x+300)&& (pos_y >= img3_y && pos_y <= img3_y+75)){
   hover[2] = true;      
  }
  else{
       hover[2] = false;
       click[2] = false;
       }  //printf("coordenadas: %d x %d\n",ev.mouse.x,ev.mouse.y);
}
//---------------GRAFICO DO JOGO----------------------------------
      al_draw_filled_rectangle(pos_x, pos_y, pos_x+20, pos_y+20, al_map_rgb(0,0,0));      
      if(tf == true){
            fim = 2;
           }
      if(tc == true){
            fim = 1;
            }
      al_flip_display();
     al_draw_scaled_bitmap(bg,0,0,640,480,0,0,Largura_t,Altura_t,0);
     
       
      al_draw_text(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t * 0.1,ALLEGRO_ALIGN_CENTRE,"MORCELANDIA UFG");
      
//-------------------------------------BOTÃO 1----------------------------------------------
      if(hover[0] || click[0]){
         if(click[0]){
                    al_draw_scaled_bitmap(btn_click,0,0,lg_btn2,at_btn2,img1_x+10,img1_y+10,Largura_t/2,Altura_t/8,0);
                    tc = true;
                   }
                   else{
              al_draw_scaled_bitmap(btn_hover,0,0,lg_btn2,at_btn2,img1_x,img1_y,Largura_t/2,Altura_t/8,0);
           }
      
      }
      else{
    al_draw_scaled_bitmap(btn,0,0,lg_btn2,at_btn2,img1_x,img1_y,Largura_t/2,Altura_t/8,0);
      }
      
//---------------------------------BOTÃO 2---------------------------------------------------
    switch(btn2){
     case 2:
       al_draw_scaled_bitmap(btn_sobre_hover,0,0,lg_btn2,at_btn2,img2_x,img2_y,Largura_t/2,Altura_t/8,0);
       break;
     case 1:
      al_draw_scaled_bitmap(btn_sobre_click,0,0,lg_btn2,at_btn2,img2_x+10,img2_y+10,Largura_t/2,Altura_t/8,0);
      tf = 2;
      break;
       default:
    al_draw_scaled_bitmap(btn_sobre,0,0,lg_btn2,at_btn2,img2_x,img2_y,Largura_t/2,Altura_t/8,0);
     break;
    }
    
//------------------------BOTÃO 3------------------------------
    if(hover[2] || click[2]){
         if(click[2]){
                    al_draw_scaled_bitmap(btn_sair_click,0,0,lg_btn2,at_btn2,img3_x+10,img3_y+10,Largura_t/2,Altura_t/8,0);
                    tf = true; 
                    
                   }
                   else{
              al_draw_scaled_bitmap(btn_sair_hover,0,0,lg_btn2,at_btn2,img3_x,img3_y,Largura_t/2,Altura_t/8,0);
           }
      
      }
      else{
    al_draw_scaled_bitmap(btn_sair,0,0,lg_btn2,at_btn2,img3_x,img3_y,Largura_t/2,Altura_t/8,0);
      }
    
    }
    
   if(fim == 1){
           al_destroy_sample_instance(inst_trilha_sonora_menu);
          return (1);
          al_destroy_bitmap(bg);
          al_destroy_bitmap(btn);
           al_destroy_event_queue(fila_menu);
           al_destroy_bitmap(btn_hover);
            al_destroy_bitmap(btn_click);
            al_destroy_bitmap(btn_sobre);
             al_destroy_bitmap(btn_sobre_hover);
              al_destroy_bitmap(btn_sobre_click);
             al_destroy_bitmap(btn_sair);
             al_destroy_bitmap(btn_sair_hover);
             al_destroy_bitmap(btn_sair_click);
             al_destroy_sample(trilha_sonora_menu);
            
   }
   else{
        al_destroy_sample_instance(inst_trilha_sonora_menu);
        return (0);
        }    

}


struct Morcego{
        int ID;
        int sp;
        int x;
        int y;
        int velocidade;
        int borda_x;
        int borda_y;
        bool ativo;
      
        };
 
 
 

struct Projeteis{
       
  int x,y;
  int velocidade;
  bool ativo;     
       
}typedef aux;
   





int main()
{
   
 

   
  //-------------------------------------------------------------------------------------------
   bool desenha = false,clear = false;
   
   int cont_inimigos = 0,cont_mortos = 0,cont_invadidos = 0,placar,mn=0;
   int fim = false;
   ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_EVENT_QUEUE *tela = NULL;
   ALLEGRO_BITMAP *bg = NULL;
   ALLEGRO_BITMAP *aponta_arma = NULL;
   ALLEGRO_BITMAP *aponta_arma2 = NULL;
   
   int teclas[] = {false, false, false};
  ///--------------------PROTOTIPOS------------------------------------------------------------------------------                                                                                               
  
  
  void InitBalas(aux bala[],int tamanho);
  void AtiraBalas(aux bala[], int tamanho, int pos_x,int pos_y);
  void AtualizaBalas(aux bala[], int tamanho);
  void DesenhaBalas(aux bala[], int tamanho); 
  
  void InitMorcegos(Morcego morcegos[], int tamanho);
  void LiberaMorcegos(Morcego morcegos[], int tammanho,int *cont_inimigos);
  void AtualizarMorcegos(Morcego morcegos[], int tammanho);
  void DesenhaMorcegos(Morcego morcegos[], int tammanho);
  void BalaColidida(aux bala[], int b_tamanho, Morcego morcegos[], int c_tamanho,int *cont_mortos);
  
  void MorcegoColidido(Morcego morcegos[],int c_tamanho, double pos2,int *cont_invadidos);
  
  
  //--------------------------------------------------------------------------------------------------------------
  
  
  //------------------------------------INICIALIZACAO DE OBJETOS---------------------------------------------------
  //Arminha Arma;
   aux bala[NUM_BALAS];
    struct Morcego morcegos[NUM_MORCEGO];
      
  
  //----------------------------------------------//----------------------------------------------------------------
  
  //inicialização
   ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "falha na inicializacao do allegro!\n");
      return -1;
   }
 
   display = al_create_display(Largura_t, Altura_t);
   if(!display) {
      fprintf(stderr, "falha na criancao do display!\n");
      return -1;
   }
  //INICIALIZAÇÃO DAS FUNÇÕES ALLEGRO 
   al_init_primitives_addon();
   al_init_image_addon();
   al_install_mouse();
   al_init_font_addon();
   al_init_ttf_addon();
 
   aponta_arma = al_load_bitmap("sprite_0.png"); 
   aponta_arma2 = al_load_bitmap("sprite_1.png");
   ALLEGRO_BITMAP *icon = NULL;
   icon = al_load_bitmap("morcego/m1.png");
   ALLEGRO_FONT *font20 = al_load_font("font.ttf",40,0);
      ALLEGRO_FONT *font_arial = al_load_font("arial.ttf",25,0);
      ALLEGRO_FONT *font_arial20 = al_load_font("arial.ttf",20,0);
      ALLEGRO_FONT *font_enter = al_load_font("font.ttf",20,0);
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(10); // quantidade de variaveis que armazenariam a trilha sonora; 
   al_set_display_icon(display, icon); 
    //------------------------------------------------------------------------------------------------------------
   
   //instalando teclado
     al_install_keyboard();
      mn = Menu(display,font20);
   //variavel do tipo evento, para criar qualquer interação do teclado com o jogo
     fila_eventos = al_create_event_queue();
     timer = al_create_timer(1.0 / FPS);
    
     trilha_sonora = al_load_sample("musica-do-joguinho.ogg"); 
     trilha_sonora2 = al_load_sample("death.ogg");
     
     
     
     
     
     
     inst_trilha_sonora = al_create_sample_instance(trilha_sonora);
     inst_trilha_sonora2 = al_create_sample_instance(trilha_sonora2);
     
     
     al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer()); // criacao do mixer padrao da biblioteca para reproduzir o som 
     al_attach_sample_instance_to_mixer(inst_trilha_sonora2, al_get_default_mixer());
 
     al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP); // funcao para que a trilha sonora fique em um loop , caso ela termine , volta ao inicio da trilha ate o jogo acabar
     
     
     
     al_set_sample_instance_gain(inst_trilha_sonora, 2.8); // funcao de modificacao do volume da trilha sonora
     al_set_sample_instance_gain(inst_trilha_sonora2, 0.5);

     //registrando esse evento;
     al_register_event_source(fila_eventos, al_get_keyboard_event_source());
     al_register_event_source(fila_eventos, al_get_display_event_source(display));
     al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); 
      al_register_event_source(fila_eventos,al_get_mouse_event_source());
     //------------------------------------------------------------------------------------------------------------
       ALLEGRO_BITMAP *im1 = NULL;
       ALLEGRO_BITMAP *im2 = NULL;
       bg = al_load_bitmap("bg.png");
        im1 = al_load_bitmap("imagem.png");
         im2 = al_load_bitmap("imagem1.png");
   
   
    srand(time(NULL));
    InitMorcegos(morcegos,NUM_MORCEGO);  
    InitBalas(bala,NUM_BALAS);
    al_start_timer(timer);
     if(mn == 1){
        al_play_sample_instance(inst_trilha_sonora);  
         
      //LAÇO PRINCIPAL DO JOGO
      while(!fim){
       ALLEGRO_EVENT ev;
      al_wait_for_event(fila_eventos, &ev);
      
       if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
           mn = Menu(display,font20);
           al_destroy_sample_instance(inst_trilha_sonora);
          if(mn == 1){
               al_play_sample_instance(inst_trilha_sonora); 
                }
          if(mn == 0){
          break;
          }
         
         }           
       
       //---------------------------------------------------------------------------------------------
      
        
         
       //MOVIMENTAÇÃO SEGURANDO AS TECLAS-------------------------------------------------------------
       if(nivel == 20){
                
                  al_draw_text(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t/3 ,ALLEGRO_ALIGN_CENTRE,"PARABENS VOCE TERMINOU O JOGO");
        
        }
          switch(ev.keyboard.keycode){
                                      
           case ALLEGRO_KEY_RIGHT:
              teclas[DIREITA] = true;               
              break;  
           case ALLEGRO_KEY_LEFT:
              teclas[ESQUERDA] = true; 
              break;
           case ALLEGRO_KEY_SPACE:
              teclas[SPACE] = true; 
              AtiraBalas(bala,NUM_BALAS,pos_x,pos_y);
              aniarma = true;       
              break;
            case ALLEGRO_KEY_ENTER:
                 if(placar == 1){                   
                     nivel += 1;
                     if(nivel % 5 == 0){
                      VEL_MORCEGO += 1; 
                     }
                     CM -= 10;
                     NUM_INIMIGOS_FASE += 5;
                  if(nivel == 20){
                           mn = 0;
                           }
                 }
                 
                 InitMorcegos(morcegos,NUM_MORCEGO);  
                 InitBalas(bala,NUM_BALAS);
                 cont_mortos = 0;
                 cont_invadidos = 0;
                 cont_inimigos = 0;
                 clear =false;
              
                  break;
           }
       }
       if(ev.type == ALLEGRO_EVENT_KEY_UP){
         switch(ev.keyboard.keycode){
       
           case ALLEGRO_KEY_RIGHT:
              teclas[DIREITA] = false;
              break;  
           case ALLEGRO_KEY_LEFT:
              teclas[ESQUERDA] = false;
              break;   
           }
         }
          else if(ev.type == ALLEGRO_EVENT_TIMER){
               cont++;
               if(cont >= 30)
          {
                  cont = 0;
                  inc++;
                  } 
                       if(inc >= 3){
           inc =0;       
          }
             desenha = true;
          if(!clear){
          LiberaMorcegos(morcegos,NUM_MORCEGO,&cont_inimigos);
          AtualizarMorcegos(morcegos,NUM_MORCEGO);
          
           if(teclas[SPACE]){
            AtualizaBalas(bala,NUM_BALAS);     
            BalaColidida(bala, NUM_BALAS,morcegos,NUM_MORCEGO,&cont_mortos); 
           
            }
            MorcegoColidido(morcegos, NUM_MORCEGO, pos2,&cont_invadidos);
            }  
     }
       else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
              fim = true;
           }
        pos_x -= teclas[ESQUERDA] * 8;
        pos_x += teclas[DIREITA] * 8;
       
         if(pos_x < 0){
                pos_x= 0;
              }
              if(pos_x >= Largura_t ){
                pos_x = Largura_t - 50;
              } 
         
     //-----------------------------------------------------------------------------------------------------------
  
     if((cont_mortos + cont_invadidos) == NUM_INIMIGOS_FASE){
     
            clear = true;
            if(cont_mortos > cont_invadidos){
             placar = 1;
            } 
            if(cont_mortos < cont_invadidos){
             placar = 0;
            }
            if(cont_mortos == cont_invadidos){
             placar = 2;
            }
                           
          }
          
     
     //DESENHO----------------------------------------------------------------------------------------------------- 
     if(desenha && al_is_event_queue_empty(fila_eventos)){
       al_draw_scaled_bitmap(im1,0,0,720,836,0,0,Largura_t,Altura_t,0);
       al_draw_scaled_bitmap(im2,0,0,720,836,0,Altura_t - (Altura_t * 0.25),Largura_t,(Altura_t * 0.25),0);

     al_draw_filled_rectangle((Largura_t * 70)/100,(Altura_t * 80) /100,(Largura_t * 95) / 100,(Altura_t * 95) /100, al_map_rgba(100,100,100,0.9));  
        al_draw_textf(font_arial,al_map_rgb(255,0,0),Largura_t - (Largura_t * 0.18),Altura_t - (Altura_t * 0.20),ALLEGRO_ALIGN_CENTRE,"Nivel: %d",nivel);                  
       al_draw_textf(font_arial,al_map_rgb(255,0,0),Largura_t - (Largura_t * 0.18),Altura_t - (Altura_t * 0.15),ALLEGRO_ALIGN_CENTRE,"Mortos: %d",cont_mortos);
        al_draw_textf(font_arial,al_map_rgb(255,0,0),Largura_t - (Largura_t * 0.18),Altura_t - (Altura_t * 0.1),ALLEGRO_ALIGN_CENTRE,"Invadidos: %d",cont_invadidos);   
         al_draw_textf(font_arial20,al_map_rgb(255,255,255),0,Altura_t - (Altura_t * 0.20),0,"ESC: MENU");   
    
             
              if(!clear){
               desenha = false;
                     DesenhaBalas(bala,NUM_BALAS);
                    DesenhaMorcegos(morcegos,NUM_MORCEGO);               
                                          
                 }
                 else{
                 al_draw_filled_rectangle((Largura_t * 80)/100,(Altura_t * 30)/100,(Largura_t * 20)/100,(Altura_t * 50)/100, al_map_rgba(100,100,100,0.5));
                 if(nivel < 20){
                       al_draw_text(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t/3 ,ALLEGRO_ALIGN_CENTRE,"O JOGO ACABOU");   
                       switch(placar){
                        case 1:
                        al_draw_textf(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t * 0.4,ALLEGRO_ALIGN_CENTRE,"Ganhou");                            
                        al_draw_text(font_enter,al_map_rgb(255,255,255),Largura_t/2,Altura_t * 0.5 ,ALLEGRO_ALIGN_CENTRE,"ENTER: PROXIMO NIVEL");
                        break;
                        case 0:
                         al_draw_textf(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t * 0.4,ALLEGRO_ALIGN_CENTRE,"Perdeu");
                         al_draw_text(font_enter,al_map_rgb(255,255,255),Largura_t/2,Altura_t * 0.5 ,ALLEGRO_ALIGN_CENTRE,"ENTER: REINICIAR NIVEL");
                        break;
                        case 2:
                         al_draw_textf(font20,al_map_rgb(255,0,0),Largura_t/2,Altura_t * 0.4 ,ALLEGRO_ALIGN_CENTRE,"Empate");                            
                         al_draw_text(font_enter,al_map_rgb(255,255,255),Largura_t/2,Altura_t * 0.5 ,ALLEGRO_ALIGN_CENTRE,"ENTER: REINICIAR NIVEL");
                        break;
                       }
                       }
                      }
      
      
      if(!aniarma){
      al_draw_bitmap(aponta_arma,pos_x ,pos_y - 60,0);    
       
      }
      else{
       al_draw_bitmap(aponta_arma2,pos_x ,pos_y - 60,0);
       }
      aniarma = false;
     pos2 = (Altura_t * 0.63);
      pos = (Altura_t * 0.25);
      al_draw_line(0,Altura_t - pos, Largura_t,Altura_t - pos, al_map_rgb(0,0,0),2);

     al_flip_display();
    
        
    
   //-------------------------------------------------------------------------------------------------------------  
}
}
}
   //finalizar o programa
   al_destroy_display(display);
   al_destroy_event_queue(fila_eventos);
   al_destroy_bitmap(aponta_arma); 
   al_destroy_sample(trilha_sonora);
   al_destroy_sample(trilha_sonora2);
   al_destroy_sample_instance(inst_trilha_sonora);
   al_destroy_sample_instance(inst_trilha_sonora2);
   al_destroy_font(font20);
  al_destroy_font(font_arial);
  al_destroy_font(font_arial20);
  al_destroy_font(font_enter);    
   
   return 0;
 }
 
 //--------------------PROJETEIS------------------------------------------------
    void InitBalas(aux bala[],int tamanho){
 
        for(int i = 0; i < tamanho; i++){
        
         bala[i].velocidade = 10;
         bala[i].ativo = false;
         }
        
}     
  void AtiraBalas(aux bala[], int tamanho, int pos_x,int pos_y){
       
       for(int i = 0; i < tamanho; i++){
               
         if(!bala[i].ativo){
             bala[i].x = pos_x + 54;
             bala[i].y = pos_y;
           
             bala[i].ativo = true;
             break;
             }
         } 
     }
  void AtualizaBalas(aux bala[], int tamanho){
       
       for(int i = 0; i < tamanho; i++){
       
        if(bala[i].ativo){
         bala[i].y -= bala[i].velocidade;
          
          if(bala[i].y < 0){
           bala[i].ativo = false; }
          }
       }
  }
  void DesenhaBalas(aux bala[], int tamanho){
   
    for(int i = 0; i < tamanho; i++){
      
      if(bala[i].ativo){
       al_draw_filled_circle(bala[i].x,bala[i].y, 4, al_map_rgb(0,255,127));
       }
      }
    }
    
    void InitMorcegos(Morcego morcegos[], int tamanho){
      int i;
       for(i=0;i<tamanho;i++){
               morcegos[i].ID = INIMIGOS; 
               morcegos[i].sp = 0;  
               morcegos[i].velocidade = VEL_MORCEGO;
               morcegos[i].borda_x = 18;
               morcegos[i].borda_y = 18;    
               morcegos[i].ativo = false;
               }
       }
  void LiberaMorcegos(Morcego morcegos[], int tamanho,int *cont_inimigos){
       int i;
       
       
       for(i=0;i<tamanho;i++){
               morcegos[i].ID = INIMIGOS;   
               morcegos[i].velocidade = 4;
               morcegos[i].borda_x = 70;
               morcegos[i].borda_y = 70;   
               if(!morcegos[i].ativo){ 
                 if(rand() % CM == 0){
                 morcegos[i].x = 80 + rand() % 6 * (Largura_t * 0.16);
                  morcegos[i].y = 0;
                   morcegos[i].ativo = true;
                   *cont_inimigos = *cont_inimigos +1;
                  // printf("%d",*cont_inimigos);
                  // printf("%d",morcegos[i].x);           
                   break;
                 }
               }
             }
         }
  void AtualizarMorcegos(Morcego morcegos[], int tamanho){
        
       int i;
       for(i = 0;i<tamanho;i++){
         if(morcegos[i].ativo){
          morcegos[i].y += morcegos[i].velocidade;                       
             if(morcegos[i].y >   Altura_t){
                morcegos[i].ativo = false;                 
                              
             }              
         }            
             
       }
  }
  void DesenhaMorcegos(Morcego morcegos[], int tamanho){
       int i;
    img1 = al_load_bitmap("morcego/m1.png");
    img2 = al_load_bitmap("morcego/m2.png");
    img3 = al_load_bitmap("morcego/m3.png");
    img4 = al_load_bitmap("morcego/m4.png");
   
                    
          if(inc == 0){
                 img = img1;
                 }
          if(inc == 1){
                 img = img2;
                 }
          if(inc == 2){
                 img = img3;
          }
          if(inc == 3){
                 img = img4;
          }
          
          int lg_m = al_get_bitmap_width(img);
          int alt_m = al_get_bitmap_height(img);    
               
        for(i = 0;i<tamanho;i++){
          if(morcegos[i].ativo){
                   al_draw_scaled_bitmap(img,0,0,lg_m,alt_m,morcegos[i].x,morcegos[i].y,70,70,0);           
         }      
         
              
               
        }
       
       
       }

    
    //COLISOES-----------------------------------------------------------------------------------
    void BalaColidida(aux bala[], int b_tamanho, Morcego morcegos[], int c_tamanho,int *cont_mortos){
                
     for(int i = 0; i < b_tamanho; i++){
     
      if(bala[i].ativo){
                        
       for(int j = 0; j < c_tamanho; j++){
               
        if(morcegos[j].ativo){         
          if(((bala[i].x >= (morcegos[j].x)) && (bala[i].x <= ((morcegos[j].x + morcegos[j].borda_x)))) && ((bala[i].y > (morcegos[j].y - morcegos[j].borda_y)) && (bala[i].y < (morcegos[j].y + morcegos[j].borda_y)))){
       
          bala[i].ativo = false;
          morcegos[j].ativo = false;
           al_play_sample_instance(inst_trilha_sonora2);
           *cont_mortos = *cont_mortos + 1;
          
           }
        }
      } 
    }
  }
}
 
 void MorcegoColidido(Morcego morcegos[],int c_tamanho, double pos2,int *cont_invadidos){
      
      for(int i = 0; i < c_tamanho; i++){

      if(morcegos[i].ativo){
                         
       if(morcegos[i].y - morcegos[i].borda_y > pos2){
                        
        morcegos[i].ativo = false;
        *cont_invadidos = *cont_invadidos + 1;
        
       }
      }
     }     
    }
