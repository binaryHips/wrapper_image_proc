#include "image_ppm.h" 



color fragment(int U, int V, OCTET* ImgIn, int nW, int nH){
	color COLOR = color{0, 0, 0};
{
    COLOR = from_HSV(
                to_HSV(get_pixel_safe(ImgIn, nW, nH, U,V)));
    if (V > 120){
        for (int i = 0; i < 300; ++i){

            COLOR = from_HSV(
                    to_HSV(COLOR));

        }
    }
    
    
}
  	return COLOR;
}



int main(int argc, char* argv[]){
   int nH, nW, nTaille, nR, nG, nB, S;
   OCTET *ImgIn, *ImgOut;
   lire_nb_lignes_colonnes_image_ppm("./images/artemis.ppm", &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm("./images/artemis.ppm", ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
   for (int U = 0; U < nW; ++U){
      for (int V = 0; V < nH; ++V){
         put_pixel_c(ImgOut, nW, U, V, fragment(U,V, ImgIn, nW, nH));
      }
   }   ecrire_image_ppm("./output/test_conv_hsv_progressif.ppm", ImgOut,  nH, nW);
}