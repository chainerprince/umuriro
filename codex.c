#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*
_GrouP_
Biziyaremye Henriette
Itetero Ariane
Niyigena Yves
Impano Alliance
Mutegetsi Prince
*/
typedef struct registered_users{
	char names[40];
	char category[40];
	char cashpowerNumber[100];
	char prev[100];
} Users ;
float residential(Users *user,int);
float nonresidential(Users *user,int);
int generateToken();
int main(){
	int units;
	int success = 0;
	int  cash;
	char cpn[20];
FILE *reg_tarrif = fopen("abaguzi_bumuriro.csv" , "r");
FILE *tempFile= fopen("temp.csv","w+");
	if(reg_tarrif == NULL){
		printf("the file is unable to open");
	}
	else{	
    Users users[100];
    Users *us;
    us = users;
	char buff[1000];
	int row_count;
	int  field_count;
	
	int i=0;
		printf("\t\t\t\t\t\t\t\tHello Dear Welcome to System codex ********* \n");
	printf("Enter your cash power number --- ");
		scanf("%s",cpn);
	while(fgets(buff, 1000 , reg_tarrif) != NULL)
	{
		field_count = 0;
		char *field = strtok(buff , ",");
		
		while(field){
			if (field_count == 0){
				strcpy(us->names , field);	
			}
			else if (field_count == 1){
				strcpy(us->category , field);	
			}
			else if (field_count == 2){
				strcpy(us->cashpowerNumber , field);
			}
			else {
				strcpy(us->prev , field);	

			}
			field = strtok(NULL , ",");
			field_count++;
		}
		
		

		// printf("%s",cpn);
		// printf("%s\n",us->cashpowerNumber);
     
		if(strcmp(us->cashpowerNumber,cpn)==0){

	printf("Enter The amount of money you have  ---  ");
		scanf("%d",&cash);
		if(strcmp(us->category,"residential")==0){ 

			units = residential(us,cash);
			
			printf("%s you are given %.2f KWH", us->names, units);
			strcpy(us->prev,(char*) units);
			success = 1;
			// break;

	}else if(!strcmp(us->category,"non-residential")){
		
			units = nonresidential(us,cash);
			printf("%s you have bought %d KWH",us->names,units);
			strcpy(us->prev,(char*) units);
		}else if(strcmp(us->category,"Telecom Tower") == 0){
			units=cash/201;
			printf("You are given %d KWH",units);
		}else if(strcmp(us->category,"Water treatment")==0){
			units=cash/126;
			printf("You are given %d KWH",units);
		}
		else if(strcmp(us->category,"hotel")==0){
			units=cash/157;
			printf("You are given %d KWH",units);
			success = 1;
			// break;
		}
		else if(strcmp(us->category,"Health facilities")==0){
			units=cash/186;
			printf("You are given %d KWH",units);
		}
		else if(strcmp(us->category,"Broadcasters")==0){
			units=cash/192;
			printf("You are given %d KWH",units);
		}
		else if(strcmp(us->category,"Commercial data centers")==0){
			units=cash/179;
			printf("You are given %d KWH",units);
    	}else{
			printf("Invalid");
		}
	}

	char userbuffer[1024];
	
		 sprintf(userbuffer, "%s,%s,%s,%s\n",us->names,us->category,us->prev,us->cashpowerNumber);
             fputs(userbuffer, tempFile);	

		
		

	}
	
	
// fclose(reg_tarrif);
	
	if(success){
		int token = generateToken();
		printf("\tThe token is %d",token);
          fclose(reg_tarrif);
          fclose(tempFile);
		remove("abaguzi_bumuriro.csv");
		rename ("temp.csv","abaguzi_bumuriro.csv");	
	}else{
		printf("You must first get registered");
	}
		
	
}
return 0;

}		


float residential(Users *user , int cash){
    float units;
    float previous = atof(user->prev);
    int amount;
    if(previous <= 15){
		
        float possibleUnits = 15 - previous;
		
        
        units = cash/89;
		
		
        if(units>possibleUnits){     
             
             units = possibleUnits;            
            cash-=units*89;
            
            previous+=units;
            
            if(cash>0){
                int possibleUnits = 50 - previous;
                units += cash/212;
                if(units>possibleUnits){
                    units += possibleUnits;
                    cash-=units*212;
                    previous += units;
                }else{
                    return units;
                }
                
                
                if(cash>0){
                  
                    units += cash/249;
                }
            }
            // return units;
                
            } else{
				
                return units;
            }
            
        }
        else if(previous > 15 && previous <=50){            
             int possibleUnits = 50 - previous;
             units = cash/212;
               if(units>possibleUnits){
             
             units = possibleUnits;
            cash -= units*212;
       
            
            previous+=units;
                
            } else{
                previous += units;
				
                return units;
            }
             
        }else{
            units = cash/249;
			 
            return units;
        }
       
     
}


float nonresidential(Users *user,int cash){
	int units = 0,possibleUnits,bUnits,amount;
	int prev = atof(user->prev);
	char category[30] = "non residential";
		// printf("Starting");
		if(prev<100){
			possibleUnits = 100 - prev;
			bUnits = cash/227;
			if(bUnits<possibleUnits){
				amount = bUnits*227;
				cash -= amount;
				units += bUnits;
				prev += bUnits;				
			}else{
				bUnits = possibleUnits;
				amount = bUnits*227;
				cash -= amount;
				units += bUnits;
				prev += bUnits;	
			//	printf("In the first category the remaining money is %d",prev);
			}			
		}
		if(cash>255&&prev>=100){
				bUnits = cash/255;
				units += bUnits;
				prev += bUnits;
				amount = bUnits * 255;
				cash -= amount;
			}
		
}


int generateToken(){
   srand(time(NULL));
   int low = 7110009;
   int high =711000900;
   int token = (rand() % (high-low+ 1))+low;
   return token;
}