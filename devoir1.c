#include <stdlib.h>
#include <stdio.h>
#include <string.h>


  int main (int argc , char * argv[])
  {
    int resultat;
    int n;
  
      if (argc > 1)
      {
         
          if(strcmp(argv[1],"-f")==0 || strcmp(argv[1],"-g")==0)
          {
            int i=0;n=0;
            while(argv[2][i]!='\0')
            {
               
               if (argv[2][i]>='0' && argv[2][i]<='9')
               { 
                 n=n*10;
                 n=n+(argv[2][i] - '0');
                 i++;
               }
               else {break;}
            
            }
           
            if( argv[2][i]=='\0')
            {
               
               i=0;
                if( strcmp(argv[1],"-f")==0 )
                {
                   resultat=1;
                  while(i<n)
                  {
                     resultat=resultat*2;
                     i++;
                  }
                    printf("f(%d)=%d\n", n,resultat);
                    if(argc > 3)
                  {
                  
                          if(strcmp(argv[3],"-f")==0 || strcmp(argv[3],"-g")==0)
			  {
			  
			    
				if( strcmp(argv[3],"-f")==0 )
				{
				    i=0;n=resultat;resultat=1;
				  while(i<n)
				  {
				     resultat=resultat*2;
				     i++;
				  
				  }
				    printf("fof(%d)=%d\n",n,resultat);
				}
				else
				{
				
				  resultat= 2* resultat;
				 printf("gof(%d)=%d\n",n, resultat);
				} 
                    
                          }//ici si la quatrieme argument  n est pas valable le programme l ignore c est dire il 
                          
                           // ne fait rien 
                 }
                }
                else
                {
                
                  resultat= 2* n;
                 printf("g(%d)=%d\n", n,resultat);
                 if(argc > 3)
                  {
                  
                          if(strcmp(argv[3],"-f")==0 || strcmp(argv[3],"-g")==0)
			  {
			  
			    
				if( strcmp(argv[3],"-f")==0 )
				{
				    i=0;n=resultat;resultat=1;
				  while(i<n)
				  {
				     resultat=resultat*2;
				     i++;
				  
				  }
				    printf("fof(%d)=%d\n",n,resultat);
				}
				else
				{
				
				  resultat= 2* resultat;
				 printf("gof(%d)=%d\n",n, resultat);
				} 
                    
                          }//ici si la quatrieme argument  n est pas valable le programme l ignore c est dire il 
                          
                           // ne fait rien 
                 }
                }
                
                
          
          
              }
              else
              {
              
                 printf("argv[2] n est pas un entier");
                 exit(-1);
              }
      
          }
          else
          {
            
            printf("argument non valide ");
            exit(1);
          
          }
  
    }
    else 
    {
    
          printf("pas d argument ");
          exit(0);
         
    }
    return 0;
  
  
  
  
  }
