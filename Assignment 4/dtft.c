/* -----------------------------------------------------------------------------
  The Discrete-time Fourier transform (DTFT) 
-------------------------------------------------------------------------------*/

#include<stdio.h> 
#include<math.h> 

float re[100],im[100],ma[150],ph[150]; 
float pi=3.14; 
int main(){ 
int n,i,j; 
printf("Enter the range of the function:"); 
scanf("%d",&n); 

for(i=0;i<100;i++){ 

 	if(i<n){ 
 	 	printf("real part of x[%d]:",i); 
                     scanf("%f",&re[i]);  	 	
                     printf("img part of x[%d]",i); 
 	 	scanf("%f",&im[i]); 
 	 	} 
	else{  	 	
                 re[i]=0; 
  	 	im[i]=0; 
 	 	} 
 	} 
	
for(i=0;i<150;i++){ 
 	float p=0,q=0; 
          for(j=0;j<n;j++){
  	 	p=p+re[j]*cos(0.1*i*j)+im[j]*sin(0.1*i*j); 
                    q=q+im[j]*cos(0.1*i*j)-re[j]*sin(0.1*i*j); 
 	 	} 
 	ma[i]=sqrt(pow(p,2)+pow(q,2));
  	printf("magnitude:%f\n",ma[i]);
  	ph[i]=atan(-q/p); 
 	printf("phase:%f\n",ph[i]); 
 	}
return 0; 
} 