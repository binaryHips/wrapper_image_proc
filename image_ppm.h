// ----------------------------------------------------------------------------
// Filename        : image_ppm.c
// Description     :
// Created On      : Tue Mar 31 13:26:36 2005
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define allocation_tableau(nom, type, nombre) \
if( (nom = (type*) calloc (nombre, sizeof(type) ) ) == NULL ) \
{\
 printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");\
 exit(1);\
}

typedef unsigned char OCTET;

/*===========================================================================*/
void ignorer_commentaires(FILE * f)
{
  unsigned char c;
  while((c=fgetc(f)) == '#')
    while((c=fgetc(f)) != '\n');
  fseek(f, -sizeof(unsigned char), SEEK_CUR);
}
/*===========================================================================*/


/*===========================================================================*/
void ecrire_image_ppm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
   FILE *f_image;
   int taille_image = 3*nb_colonnes * nb_lignes;

   if( (f_image = fopen(nom_image, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fprintf(f_image,"P6\r") ;                               /*ecriture entete*/
	 fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

	 if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     != (size_t)(taille_image))
	    {
	       printf("\nErreur d'ecriture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/

/*===========================================================================*/		
void lire_nb_lignes_colonnes_image_ppm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
   FILE *f_image;
   int max_grey_val;

   /* cf : l'entete d'une image .ppm : P6                   */
   /*				       nb_colonnes nb_lignes */
   /*    			       max_grey_val          */


   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fscanf(f_image, "P6 ");
	 ignorer_commentaires(f_image);
	 fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
	 fclose(f_image);
      }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_ppm(char  nom_image[], OCTET *pt_image, int taille_image)
{
   FILE *f_image;
   int  nb_colonnes, nb_lignes, max_grey_val;
   taille_image=3*taille_image;

   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	fscanf(f_image, "P6 ");
	ignorer_commentaires(f_image);
	fscanf(f_image, "%d %d %d%*c",
	       &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

	 if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     !=  (size_t)(taille_image))
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}

/*===========================================================================*/
/*===========================================================================*/

void planR(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i];
      }
   }
   
/*===========================================================================*/
/*===========================================================================*/

void planV(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i+1];
      }
   }   

/*===========================================================================*/
/*===========================================================================*/

void planB(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i+2];
      }
   }
   
/*===========================================================================*/   
/*===========================================================================*/

void ecrire_image_pgm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
   FILE *f_image;
   int taille_image = nb_colonnes * nb_lignes;

   if( (f_image = fopen(nom_image, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fprintf(f_image,"P5\r") ;                               /*ecriture entete*/
	 fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

	 if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     != (size_t) taille_image)
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
   FILE *f_image;
   int max_grey_val;

   /* cf : l'entete d'une image .pgm : P5                    */
   /*				       nb_colonnes nb_lignes */
   /*    			       max_grey_val          */


   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fscanf(f_image, "P5 ");
	 ignorer_commentaires(f_image);
	 fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
	 fclose(f_image);
      }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_pgm(char  nom_image[], OCTET *pt_image, int taille_image)
{
   FILE *f_image;
   int  nb_colonnes, nb_lignes, max_grey_val;

   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	fscanf(f_image, "P5 ");
	ignorer_commentaires(f_image);
	fscanf(f_image, "%d %d %d%*c",
	       &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

	 if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     !=  (size_t) taille_image)
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/


//#define FRAGMENT(T, size, size_row, n_color) int n_color = n_color, size = size, size_row = size_row; int for (int u = 0, v = 0; i <= size; u = u + n_color)
//#define loop(x,n) for(int x = 0; x < n; ++x)

struct color{

   int r;
   int g;
   int b;
};

struct hsv{

   float h;
   float s;
   float v;
};

int get_pixel_bw(OCTET* pt_image, int size_x,  int u, int v){

   return  pt_image[v * size_x + u];

}

color get_pixel_c(OCTET* pt_image, int size_x, int u, int v){

   return  color{
      pt_image[(u * size_x + v)*3],
      pt_image[(u * size_x + v )*3+1],
      pt_image[(u * size_x + v)*3+2]
      
      };
}


color get_pixel_safe(OCTET* pt_image, int size_x, int size_y, int u, int v){

   int realU, realV;

   u = u % (size_x * 2);
   v = v % (size_y * 2);

   if (u<0) u += size_x;
   if (v<0) v += size_y;

   if (u >= size_x-1) u = 2*size_x - u;
   if (v >= size_y-1) v = 2*size_y - v;

   return  color{
      pt_image[(u * size_x + v)*3],
      pt_image[(u * size_x + v )*3+1],
      pt_image[(u * size_x + v)*3+2]
      
      };

}
void put_pixel_bw(OCTET* pt_image, int size_x, int u, int v, int val ){


   pt_image[v * size_x + u] = val;

}


void put_pixel_c(OCTET* pt_image, int size_x, int u, int v, color c){


   pt_image[(u * size_x + v)*3] = c.r;
   pt_image[(u * size_x + v)*3+1] = c.g;
   pt_image[(u * size_x + v)*3+2] = c.b;

}

void get_neighbours_4_bw(OCTET* pt_image, int size_x, OCTET* res, int u, int v){
   //securing 
   res[0] = u-1 >= 0? get_pixel_bw(pt_image, size_x, u-1, v): -1;
   res[2] = u+1 >= 0? get_pixel_bw(pt_image, size_x, u+1, v): -1;
   res[1] = v-1 >= 0? get_pixel_bw(pt_image, size_x, u, v-1): -1;
   res[3] = v+1 >= 0? get_pixel_bw(pt_image, size_x, u, v+1): -1;

   //TODO make the 8 neighbours version
}

void get_neighbours_4_c(OCTET* pt_image, int size_x, int size_y, color* res, int u, int v){
   //securing 
   res[0] = u-1 >= 0? get_pixel_c(pt_image, size_x, u-1, v): color{-1, -1, -1};
   res[2] = u+1 >= 0? get_pixel_c(pt_image, size_x, u+1, v): color{-1, -1, -1};
   res[1] = v-1 >= 0? get_pixel_c(pt_image, size_x, u, v-1): color{-1, -1, -1};
   res[3] = v+1 >= 0? get_pixel_c(pt_image, size_x, u, v+1): color{-1, -1, -1};

   //TODO make the 8 neighbours version
}


int lum(color C){
   return 0.299*C.r + 0.587*C.g + 0.114*C.b;
}

color c(int r, int g, int b){

   return {r, g, b};
}

color add(color a , color b){

   return {
      a.r + b.r,
      a.g + b.g,
      a.b + b.b};
}

color sub(color a , color b){

   return {
      a.r - b.r,
      a.g - b.g,
      a.b - b.b};
}

color scale(color a , float b){

   return {
      (int)(a.r * b),
      (int)(a.g * b),
      (int)(a.b * b)};
}

//Stored in a color: be careful!
color to_YCrCb(color source){
   int y = lum(source);
   return {
      lum(source),
      (int)(0.5 * source.r - 0.4187 * source.g - 0.0813 * source.b) + 128,
      (int)(-0.1687 * source.r - 0.3313 * source.g + 0.5 * source.b) + 128
   };


}

color from_YCrCb(color source){
   return {
      (int)(source.r + 1.402 * (source.g - 128)),
      (int)(source.r - 0.34414*(source.b-128) - 0.714414*(source.g - 128)),
      (int)(source.r + 1.772 *(source.b - 128))
   };


}

//from https://mattlockyer.github.io/iat455/documents/rgb-hsv.pdf
hsv to_HSV(color source){
   
   float r = source.r/255.0;
   float g = source.g/255.0;
   float b = source.b/255.0;

   float h, s, v;

   float max = r > b ? (r > g ? r : g) : (b > g ? b : g);
   float min = r < b ? (r < g ? r : g) : (b < g ? b : g);
   float delta = max-min;

   //hue
   if (delta == 0){

      h = 0.0;
   } else if (max == r){
      h = (g-b)/ delta;

   } else if (max == g){
      h = (b-r) / delta + 2;

   } else if (max == b){
      h = (r-g)/ delta + 4;

   }

   //value
   v = max;

   //saturation
   v == 0 ? s = 0 : s = delta / v;

   return {h, s, v};

};
color from_HSV(hsv source){

   float h = fmod(source.h, 6.0);
   float s = source.s;
   float v = source.v;

   if (h < 0) h = h+6.0;

   float a, b, c; //channels


   a = v * (1.0-s);

   b = v * (1- (h - floor(h)) * s);

   c = v * (1- (1- (h-floor(h)))*s);

   hsv res; //not a real hsv

   if (h < 1.0){

      res = {v, c, a};

   } else if (h < 2.0){

      res = {b, v, a};

   } else if (h < 3.0){

      res = {a, v, c};

   } else if (h < 4.0){

      res = {a, b, v};

   } else if (h < 5.0){

      res = {c, a, v};

   } else if (h <= 6.0){

      res = {v, a, b};

   }

   return {

      (int)(res.h*255),
      (int)(res.s*255),
      (int)(res.v*255)
   };

}

