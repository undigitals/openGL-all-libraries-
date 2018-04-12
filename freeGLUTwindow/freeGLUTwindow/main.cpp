#include <stdio.h>

int main(){
    int n, count=0,sum=0;
    
    scanf("%i",&n);
    for(int i=1;i<=n;i++){
        while(i/10){
            sum=i%10;
            if(sum==3){
                count++;
            }
            
            i/=10;
            
            
        }
        if(i==3){
            count++;
        }else{
            break;
        }
    }
    printf("%i",count);
    
    return 0;
}
