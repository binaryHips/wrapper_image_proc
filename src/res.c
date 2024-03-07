#include "image_ppm.h" 
color fragment(int U, int V){
	color COLOR = color{0, 0, 0};
{COLOR=get_pixel_c(u,v)*2;}
  	return COLOR;
}



int main(int argc, char* argv[]){
   int nH, nW, nTaille, nR, nG, nB, S;
   OCTET *ImgIn, *ImgOut;
   lire_nb_lignes_colonnes_image_ppm("./image_test.ppm", &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm("./image_test.ppm", ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
   for (int U = 0; U < nW; ++U){
      for (int V = 0; V < nH; ++V){
         put_pixel_c(ImgOut, nW, U, V, fragment(U,V));
      }
   }   ecrire_image_ppm("./image_res.ppm", ImgOut,  nH, nW);
}