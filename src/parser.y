
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "lexer.h"
 void yyerror(const char *msg);


FILE* source_out;

char* img_path_in;
char* img_path_out;


void setup_main(){

   // fprintf(source_out, "\n\nint main(int argc, char* argv[]){\n");

   // fprintf(source_out, "   int nH, nW, nTaille, nR, nG, nB, S;\n   OCTET *ImgIn, *ImgOut;\n");

   // fprintf(source_out, "   lire_nb_lignes_colonnes_image_ppm(\"%s\", &nH, &nW);\n", img_path_in);
   // fprintf(source_out, "   nTaille = nH * nW;\n");

   // fprintf(source_out, "   int nTaille3 = nTaille * 3;\n   allocation_tableau(ImgIn, OCTET, nTaille3);\n");
   // fprintf(source_out, "   lire_image_ppm(\"%s\", ImgIn, nH * nW);\n", img_path_in);
   // fprintf(source_out, "   allocation_tableau(ImgOut, OCTET, nTaille3);\n");

   

   // //loop
   // fprintf(source_out, "   for (int U = 0; U < nW; ++U){\n");

   // fprintf(source_out, "      for (int V = 0; V < nH; ++V){\n");

   // fprintf(source_out, "         put_pixel_c(ImgOut, nW, U, V, fragment(U,V, ImgIn, nW, nH));\n");

   // fprintf(source_out, "      }\n   }");
   
   // ///

   // fprintf(source_out, "   ecrire_image_ppm(\"%s\", ImgOut,  nH, nW);\n}", img_path_out);

   
   const char* template = ("int main(int argc, char* argv[]){\n\
   int nH, nW, nTaille, nR, nG, nB, S;\n   OCTET *ImgIn, *ImgOut;\n\
   lire_nb_lignes_colonnes_image_ppm(\"%s\", &nH, &nW);\n\
   nTaille = nH * nW;\n\
   int nTaille3 = nTaille * 3;\n\
   allocation_tableau(ImgIn, OCTET, nTaille3);\n\
   lire_image_ppm(\"%s\", ImgIn, nH * nW);\n\
   allocation_tableau(ImgOut, OCTET, nTaille3);\n\n\
   for (int U = 0; U < nW; ++U){\n\
      for (int V = 0; V < nH; ++V){\n\
         put_pixel_c(ImgOut, nW, U, V, fragment(U,V, ImgIn, nW, nH));\n\
      }\n\
   }\n\
   ecrire_image_ppm(\"%s\", ImgOut,  nH, nW);\n\
}\n\
");

   fprintf(source_out, template, img_path_in, img_path_in, img_path_out);




   
}

%}



%union{
  char* fragment_code;
  char* input;
  char* output;
}

%define parse.error verbose
%locations

%start input
%token FRAG_END FRAGMENT BR_CLOSE
%token <input> INPUT IN_ACCESS CHAR ARG NEWLINE
%token <output> OUTPUT
%token  END COMM COLOR UNKNOWN


%left TIMES SLASH
%nonassoc UMINUS


%% 
input:	{  //import the header file
            fprintf(source_out, "%s", "#include \"image_ppm.h\" \n");
            }
			| input line
			;


line:		  NEWLINE {fprintf(source_out, "%s", $1);}
         | FRAGMENT{
            fprintf(source_out, "color fragment(int U, int V, OCTET* ImgIn, int nW, int nH){\n");
            fprintf(source_out, "\tcolor COLOR = color{0, 0, 0};\n{");
            }
         

         | FRAG_END{
            fprintf(source_out, "}\n  \treturn COLOR;\n}\n\n");
         }
         | IN_ACCESS{
            fprintf(source_out, "get_pixel_safe(ImgIn, nW, nH, ");
         }
         | ARG {fprintf(source_out, "%s", $1);}

         | CHAR {fprintf(source_out, "%s", $1);}

         | INPUT line{img_path_in = $1;}
         | OUTPUT line{img_path_out = $1;}
         | END   {
            setup_main();
            YYACCEPT;}
         | COMM 
		;



%%

int main(int argc, char **argv) {
   if (argc > 1) {
      yyin = fopen(argv[1], "r");

      if (argc == 3){ // if output filename given

         source_out = fopen(argv[2], "w");
      }
      else{ //if no filename given

         source_out = fopen(strcat(argv[1], "_generated.cpp"), "w");
      }


      if (yyin == NULL){
         printf("syntax: %s filename\n", argv[0]);
      }//end if
   }//end if
   yyparse(); // Calls yylex() for tokens.
   return 0;
}


void yyerror(const char *msg) {
   printf("** Line %d: %s\n", yylloc.first_line, msg);
}