
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

   int **creer_matrice(int dimension)
   {
		    int **matrice = (int **)malloc(dimension * sizeof(int *));
		    for (int i = 0; i < dimension; i++) 
		    {
			matrice[i] = (int *)malloc(dimension * sizeof(int));
			for (int j = 0; j < dimension; j++) 
			{
			    matrice[i][j] = rand() % 10;  
			}
		    }
		    return matrice;
    }

    void afficher_matrice_texte(int **matrice, int dimension) 
    {
	    for (int i = 0; i < dimension; i++) 
	    {
		for (int j = 0; j < dimension; j++) 
		{
		    printf("%d ", matrice[i][j]);
		}
		printf("\n");
	    }
    }


   void afficher_matrice_binaire(int **matrice, int dimension) 
   {
	    for (int i = 0; i < dimension; i++) 
	    {
		for (int j = 0; j < dimension; j++)
	        {
		    printf("%08b ", matrice[i][j]);
		}
		printf("\n");
	    }
   }


   void sauvegarder_matrice(int **matrice, int dimension, const char *nom_fichier, int format_binaire) 
   {
   
	    FILE *fichier = fopen(nom_fichier, format_binaire ? "wb" : "w"); 
	    if (fichier == NULL) 
	    {
		perror("Erreur lors de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	    }

	    if (format_binaire) 
	    {
		fwrite(&dimension, sizeof(int), 1, fichier);  
		for (int i = 0; i < dimension; i++) 
		{
		    fwrite(matrice[i], sizeof(int), dimension, fichier); 
		}
	    } 
	    else 
	    {
		fprintf(fichier, "%d\n", dimension);  
		for (int i = 0; i < dimension; i++) 
		{
		    for (int j = 0; j < dimension; j++) 
		    {
		        fprintf(fichier, "%d ", matrice[i][j]);
		    }
		    fprintf(fichier, "\n");
		}
	    }

	    fclose(fichier);
    }


    int **charger_matrice(const char *nom_fichier, int *dimension, int format_binaire) 
    {
	    FILE *fichier = fopen(nom_fichier, format_binaire ? "rb" : "r");
	    if (fichier == NULL) 
	    {
		perror("Erreur lors de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	    }

	    if (format_binaire) 
	    {
		fread(dimension, sizeof(int), 1, fichier);  
		int **matrice = (int **)malloc(*dimension * sizeof(int *));
		for (int i = 0; i < *dimension; i++) 
		{
		    matrice[i] = (int *)malloc(*dimension * sizeof(int));
		    fread(matrice[i], sizeof(int), *dimension, fichier);  
		}
		fclose(fichier);
		return matrice;
	    } 
	    else 
	    {
		fscanf(fichier, "%d", dimension); 
		int **matrice = (int **)malloc(*dimension * sizeof(int *));
		for (int i = 0; i < *dimension; i++) {
		    matrice[i] = (int *)malloc(*dimension * sizeof(int));
		    for (int j = 0; j < *dimension; j++) {
		        fscanf(fichier, "%d", &matrice[i][j]);
		    }
		}
		fclose(fichier);
		return matrice;
	    }
   }


   int main(int argc, char *argv[]) 
   {
	    srand(time(NULL));

	    int dimension = 0;
	    int format_binaire = 1;  
	    int afficher = 0;         
	    int creation = 0;         
	    char *nom_fichier = NULL; 

	    for (int i = 1; i < argc; i++) 
	    {
		if (strcmp(argv[i], "-c") == 0) 
		{
		    creation = 1;
		} 
		else if (strcmp(argv[i], "-a") == 0) 
		{
		    afficher = 1;
		}
		 else if (strcmp(argv[i], "-b") == 0) 
		{
		    format_binaire = 1;
		} 
		else if (strcmp(argv[i], "-t") == 0) 
		{
		    format_binaire = 0;
		} else if (strcmp(argv[i], "-d") == 0) 
		{
		    if (i + 1 < argc) 
		    {
		        dimension = atoi(argv[++i]);
		    }
		}
		 else if (strcmp(argv[i], "-f") == 0) 
		 {
		    if (i + 1 < argc) 
		    {
		        nom_fichier = argv[++i];
		    }
		}
	    }

	    if (dimension <= 0 || nom_fichier == NULL) 
	    {
		fprintf(stderr, "Erreur: La dimension ou le nom du fichier sont manquants.\n");
		return 1;
	    }

	    int **matrice = NULL;

	   
	    if (creation) 
	    {
		matrice = creer_matrice(dimension);
		sauvegarder_matrice(matrice, dimension, nom_fichier, format_binaire);
	    }

	  
	    if (afficher) 
	    {
		matrice = charger_matrice(nom_fichier, &dimension, format_binaire);
		printf("Matrice lue depuis le fichier %s:\n", nom_fichier);
		if (format_binaire) 
		{
		    afficher_matrice_binaire(matrice, dimension);
		} 
		else 
		{
		    afficher_matrice_texte(matrice, dimension);
		}
	    }

	  
	    for (int i = 0; i < dimension; i++) 
	    {
		free(matrice[i]);
	    }
	    free(matrice);

	    return 0;
	}

