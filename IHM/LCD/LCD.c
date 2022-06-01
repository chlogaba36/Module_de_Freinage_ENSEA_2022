/**
 *\file LCD.c
 *\brief Librairie faites sur mesure pour controler l'écran LCD
 *\author Colin PERRET et Chloé GABARREN
 *\version 1.1
 *\date 31/05/2022
 *
 * Ensemble des fonctions qui seront utilisé pour écrire sur l'afficheur.
 * Cette librairie est plus digest et plus détaillé que celles disponibles
 * sur internet et celle mise à disposition par le fabricant.
 *
 */

#include <LCD.h>

I2C_HandleTypeDef hi2c1;

/**
 * \fn void LCD_transmit_cmd (char cmd)
 * \brief Fonction de transfert d'une commande à l'écran.
 *        Le microcontroleur faisant interface entre l'I2C et
 *        l'écran fonctionne sur 10 bits. Le MSB est obtenue
 *        par transfert d'une première information qui est soit
 *        0x40 pour afficher un caractère ou 0x80 pour une
 *        commande permettant par exemple d'allumer l'écran,
 *        déplacer le curseur ou l'écran, etc (voir datasheet
 *        HD44780U page 24). Le bit suivant est un bit lié au
 *        protocol I2C dont on n'a pas à se soucier et il reste
 *        l'octet de donnée (le caractère en ASCII ou une commande).
 * \param un caractère car c'est une information codé sur un
 *        octet.
 * \return void.
 */

void LCD_transmit_cmd(char cmd){
   char data[2] = {0x80,cmd};
   HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS<<1, data, sizeof(data), HAL_MAX_DELAY);
}

/**
 * \fn void LCD_Init (void)
 * \brief Fonction pour initialiser l'écran.
 *        Reproduit les étapes de la datasheet HD44780U page 45.
 * \param void.
 * \return void.
 */
void LCD_Init(void){
   //init begin
   HAL_Delay(50);
   LCD_transmit_cmd(LCD_SET);
   HAL_Delay(5);
   LCD_transmit_cmd(LCD_SET);
   HAL_Delay(1);
   LCD_transmit_cmd(LCD_SET);
   HAL_Delay(1);
   //trois set
   LCD_transmit_cmd(LCD_SET3C);
   HAL_Delay(5);
   LCD_transmit_cmd(LCD_DISPOFF);
   HAL_Delay(5);
   LCD_transmit_cmd(LCD_DISPCLEAR);
   HAL_Delay(5);
   LCD_transmit_cmd(LCD_MODESET);
   HAL_Delay(5);
   //init finished

   LCD_Home();
   LCD_transmit_cmd(LCD_DISPONF);
   HAL_Delay(5);
   LCD_transmit_cmd(LCD_MODESET);
   HAL_Delay(2000);
}

/**
 * \fn void LCD_set_Cursor(int ligne, int colonne)
 * \brief Fonction pour placer le cursor à la ligne et la
 *        colonne placé en argument (les indices commencent à 0).
 * \param Les entiers ligne et colonne dont les indices commencent à 0.
 * \return void.
 */
void LCD_set_Cursor(int ligne, int colonne){
   char pos;
   if (colonne==1){
      pos = 0x40 | ( (char) ligne);
   }
   else{
      pos = (char) ligne;
   }
   LCD_transmit_cmd(pos);
   HAL_Delay(1);
}

/**
 * \fn void LCD_PrintChar(char c)
 * \brief Fonction permettant d'afficher un caractère.
 *        Comme mentionné dans la fonction "LCD_Transmit_cmd",
 *        Il faut d'abord envoyé l'information au microcontrolleur
 *        de l'écran que l'on veut écrire un caractère avant de l'envoyer.
 * \param Le caractère que l'on veut écrire.
 * \return void.
 */
void LCD_PrintChar(char c){
   char data[2] = {0x40,c};
   HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS<<1, data, sizeof(data), HAL_MAX_DELAY);
   HAL_Delay(5);
}

/**
 * \fn void LCD_PrintChar(char* str, int len)
 * \brief Fonction permettant d'afficher une chaine de caractères en connaissant sa taille.
 *        On réalise une boucle for pour envoyer caractère par caractère avec l'information
 *        que l'on va écrire un caractère sur l'écran comme mentionné dans "LCD_PrintChar".
 *
 *        Remarque: on peut envoyer directement "@X...X", le @ correspond à 0x40 suivi de la
 *                  chaine de caractères.
 * \param La chaine de caractères que l'on veut écrire ainsi que sa taille.
 * \return void.
 */
void LCD_PrintStr(char* str, int len){
   int i=0;
   for (i=0;i<len;i++){
      char data[2] = {0x40,str[i]};
      HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS<<1, data, sizeof(data), HAL_MAX_DELAY);
      HAL_Delay(5);
   }
}

/**
 * \fn void LCD_Home(void)
 * \brief Fonction permettant de replacer l'écran et le cursor en haut à gauche.
 * \param void.
 * \return void.
 */
void LCD_Home(void){
   LCD_transmit_cmd(LCD_HOME);
   HAL_Delay(5);
}

/**
 * \fn void LCD_Clear(void)
 * \brief Fonction permettant d'effacer tous ce qui est écrit sur l'écran.
 * \param void.
 * \return void.
 */
void LCD_Clear(void){
   LCD_transmit_cmd(LCD_DISPCLEAR);
   HAL_Delay(5);
}

/**
 * \fn void LCD_YNCursorBlink(int i)
 * \brief Fonction permettant de faire clignoter le curseur.
 * \param Un entier (1 ou 0) pour faire clignoter le curseur ou pas.
 * \return void.
 */
void LCD_YNCursorBlink(int i){
   if (i==1){
      LCD_transmit_cmd(0x0f);
      HAL_Delay(5);
   }
   else {
      LCD_transmit_cmd(0x0e);
      HAL_Delay(5);
   }
}

/**
 * \fn void LCD_Manuel(void)
 * \brief Fonction permettant d'afficher le passage en mode manuel.
 *        Piste d'amélioration: on affiche également la tension mesuré.
 * \param void.
 * \return void.
 */
void LCD_Manuel(void){
   LCD_Clear();
   LCD_Home();
   char str[14]="Mode manuel ON";
   LCD_PrintStr(str,14);
}

/**
 * \fn void LCD_PrintInt(int i)
 * \brief Fonction permettant d'afficher le nombre des dixaines et de
 *        l'unité d'un entier sur l'écran.
 * \param L'entier à afficher.
 * \return void.
 */
void LCD_PrintInt(int i){
   char str[3] = "00V";
   int decim = (int) i/10;
   int unit = (int) i%10;
   str[0] = 0x30 | (decim+'0');
   str[1] = 0x30 | (unit+'0');
   LCD_PrintStr(str,3);
}

/**
 * \fn void LCD_Menu(float vmin, float vmax, int cursor)
 * \brief Fonction permettant d'afficher le menu.
 *        Les valeurs de Vmin et Vmax sont affcichées avec le mode auto.
 *        Pour sélectionner une valeur, le curseur clignote sur le point associé
 *        à la sélection en cours.
 * \param Les valeurs de vmin, vmax et la position du curseur (0, 1 ou 2).
 * \return void.
 */
void LCD_Menu(int vmin, int vmax, int cursor){
   LCD_Clear();
   LCD_Home();
   char vmi[5]= "Vmin=";
   char vma[5]= "Vmax=";
   LCD_PrintChar(CHAR_POINT);
   LCD_PrintStr(vmi,5);
   LCD_PrintInt(vmin);
   LCD_transmit_cmd(CURSOR_RETURNLIGNE);
   LCD_PrintChar(CHAR_POINT);
   LCD_PrintStr(vma,5);
   LCD_PrintInt(vmax);
   LCD_PrintChar(' ');
   LCD_PrintChar(CHAR_POINT);
   LCD_PrintStr("Aut", 3);
   LCD_set_Cursor(0, 0);
}

/**
 * \fn void LCD_vmin_menu(float vmin)
 * \brief Fonction permettant d'afficher le menu de sélection de vmin.
 * \param La valeur de vmin.
 * \return void.
 */
void LCD_vmin_menu(int vmin){
   LCD_Clear();
   LCD_Home();
   char ligne1[11] = "Selec Vmin:";
   LCD_PrintStr(ligne1, 11);
   LCD_transmit_cmd(CURSOR_RETURNLIGNE);
   LCD_PrintInt(vmin);
}

/**
 * \fn void LCD_vmin_actualisation(float vmin)
 * \brief Fonction permettant de modifier la valeur afficher de vmin
 *        sans réécrire tout le texte de "LCD_vmin_menu".
 * \param La valeur de vmin.
 * \return void.
 */
void LCD_vmin_actualisation(int vmin){
   LCD_set_Cursor(0,1);
   LCD_PrintInt(vmin);
}

/**
 * \fn void LCD_vmax_menu(float vmax)
 * \brief Fonction permettant d'afficher le menu de sélection de vmax.
 * \param La valeur de vmax.
 * \return void.
 */
void LCD_vmax_menu(int vmax){
   LCD_Clear();
   LCD_Home();
   char ligne1[11] = "Selec Vmax:";
   LCD_PrintStr(ligne1,11);
   LCD_transmit_cmd(CURSOR_RETURNLIGNE);
   LCD_PrintInt(vmax);
}

/**
 * \fn void LCD_vmax_actualisation(float vmax)
 * \brief Fonction permettant de modifier la valeur afficher de vmax
 *        sans réécrire tout le texte de "LCD_vmax_menu".
 * \param La valeur de vmax.
 * \return void.
 */
void LCD_vmax_actualisation(int vmax){
   LCD_set_Cursor(0,1);
   LCD_PrintInt(vmax);
}
