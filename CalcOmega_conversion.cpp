#include "../include/micromegas.h"
#include"../include/micromegas_aux.h"
#include "lib/pmodel.h"
#include <string>

using namespace std;

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* MAIN PROGRAM for two dark-matter candidates (by F.Staub, last change 04.05.2015)			     		    */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int main(int argc, char** argv)
{  
		int err, i;
	   	char lspname[10], nlspname[10];
		double Omega=-1, Xf=-1;
		double w,kk1,kk2,kk3,kk4,kk5,kk6,Tefo;
		double cut = 0.01;		// cut-off for channel output								
		int fast = 1;			/* 0 = best accuracy, 1 = "fast option" accuracy ~1% 	     */
 		double Beps = 1.E-5;  		/* Criteqrium for including co-annihilations (1 = no coann.) */
 		VZdecay=0; VWdecay=0; cleanDecayTable();
		ForceUG=1; 
			err = sortOddParticles(lspname);	
			printMasses(stdout,1);	
			
			//ExcludedForNDM="1122";  /*Excluded the process 11<->22*/
			ExcludedForNDM=NULL; /*To rset and include all channeles*/
	 		
	 		Omega = darkOmega2(fast,Beps,0);
                        printf("Omega_1h^2=%.2E\n", Omega*fracCDM[1]);
                        printf("Omega_2h^2=%.2E\n", Omega*fracCDM[2]);			
			printf("\n");

            //printf("M1=%.2E M2=%.2e\n",McdmN[1],McdmN[2]);
            printf("Tstart=%.4E Tend=%.4E vs=%.4E\n\n",Tstart,Tend, vs1122F(Tstart)); 
            
            Tefo = McdmN[1]/25.; //my Tfrezeout estimative
            
            if(Tefo < Tstart)
            {
            kk1 = vs2200F(Tefo); printf("Sigmav2200=%.4E\n",kk1);
			kk2 = vs2210F(Tefo); printf("Sigmav2210=%.4E\n",kk2);
			kk3 = vs2211F(Tefo); printf("Sigmav2211=%.4E\n",kk3);
		    kk4 = vs1100F(Tefo); printf("Sigmav1100=%.4E\n",kk4);
     		kk5 = vs1122F(Tefo); printf("Sigmav1122=%.4E\n",kk5);
			}
			else
            {    
			kk1 = vs2200F(Tstart); printf("Sigmav2200=%.3E\n",kk1);
			kk2 = vs2210F(Tstart); printf("Sigmav2210=%.3E\n",kk2);
			kk3 = vs2211F(Tstart); printf("Sigmav2211=%.3E\n",kk3);
            kk4 = vs1100F(Tstart); printf("Sigmav1100=%.3E\n",kk4);
		    kk5 = vs1122F(Tstart); printf("Sigmav1122=%.4E\n",kk5);
			}
			
 			printChannels(Xf, cut,Beps,1,stdout);
			FILE *omega = fopen("omg.out","w");
			fprintf(omega,"%i %6.6lf # total relic density \n",1,Omega);
			fprintf(omega,"%i %6.6lf # relic density for CDM1\n", 2,Omega*fracCDM[1]);
			fprintf(omega,"%i %6.6lf # relic density for CDM2\n", 3,Omega*fracCDM[2]);			
// 			w = 1.;
// 			i = 0;
// 			while (w>cut) 
// 			{
// 			    fprintf(omega,"%i %6.6lf # %s %s -> %s %s\n",100+i,omegaCh[i].weight,omegaCh[i].prtcl[0],omegaCh[i].prtcl[1],omegaCh[i].prtcl[2],omegaCh[i].prtcl[3]);
// 			    i++;
// 			    w = omegaCh[i].weight;
// 			}
// 			FILE *channels = fopen("channels.out","w");
// 			w = 1.;
// 			i = 0;
// 			while (w>cut) 
// 			{
// 			fprintf(channels,"%li %li %li %li %6.6lf # %s %s -> %s %s\n",pNum(omegaCh[i].prtcl[0]),pNum(omegaCh[i].prtcl[1]),pNum(omegaCh[i].prtcl[2]),pNum(omegaCh[i].prtcl[3]),omegaCh[i].weight,omegaCh[i].prtcl[0],omegaCh[i].prtcl[1],omegaCh[i].prtcl[2],omegaCh[i].prtcl[3]);
// 			    i++;
// 			    w = omegaCh[i].weight;
// 			}
			fclose(omega);
// 			fclose(channels);

                  

  	return 0;
}

