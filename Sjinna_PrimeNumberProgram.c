#include <stdio.h>
int main(){    
int given_number,temp=0,flag=0;    
printf("Enter a Number : ");    
scanf("%d",&given_number);    
temp=given_number/2;    
for(int i=2;i<=temp;i++)    
    {    
        if(given_number%i==0)  
        {    
            printf("Number is not prime");    
            flag=1;    
            break;    
        }    
    }    
    if(flag==0)    
        printf("Number is prime");     
    return 0;  
    
}    