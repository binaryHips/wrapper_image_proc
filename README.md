
# C++ wrapper for quicker writing of PPM images processing algorithms
### This is an experiment! It may not work well.

This is a little project I made to learn flex and bison, aswell as being able to easily toy with image processing on the CPU.

### How to use

- On linux:
	Download the whole version folder in ./packaged. It contains all the files needed, aswell as a readme with explanations (only in french as of now).
	There's also a bunch of script examples, and their image results.



- If you're not on linux, this should work (?):

	First, download the whole folder in ./packaged.
	Then, build the content of ./src, and replace the file named "wrapper" in the folder by it.
	Finally, launch a bash interpreter and you should be good to go

I may end up adding a windows version.


### How it works

You can find the source code in /src. Here's an explanation of how it works.


The user write a script like this.

It's akin to shader code. The instructions inside FRAGMENT are c++.

Documentation is in ./packaged/xx/README.txt (in french)

```cpp
IN ./images/artemis.ppm
OUT ./output/artemis_grey.ppm

FRAGMENT{
    int l = lum(IN(U,V));
    COLOR = c(l, l, l);
}
```

Then, after calling ./process <script> , a parser, written in flex + bison, wraps the code in a C++ body.
(arguably, it's simple enough to be done with flex alone, but it was a learning project)

The IN and OUT arguments are gathered and placed into the load and save functions.
The FRAGMENT code is put into a fragment function, and the IN() calls are swapped for the get_pixel_safe function (which handles overshoots when accessing pixels of the image)
While c++ is allowed in the fragment function, the generated program is pretty much C-compatible.

The result looks like this.
(image_ppm.h courtesy of William Puech)

```cpp

#include "image_ppm.h" 

color fragment(int U, int V, OCTET* ImgIn, int nW, int nH){
	color COLOR = color{0, 0, 0};
  {
  int l = lum(get_pixel_safe(ImgIn, nW, nH, U,V));
  COLOR = c(l, l, l);
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
   }   ecrire_image_ppm("./output/artemis_grey.ppm", ImgOut,  nH, nW);
}

```
Then this file is compiled, ran, and deleted (except if using the -s option).
The resulting image should be generated.


