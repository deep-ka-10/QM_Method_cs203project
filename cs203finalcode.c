/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(i,a,n) for(int i=a;i<n;i++)
#define d(i,a,n) for(int i=a;i>=n;i--)

int i,j,temp,nvariable,nallminterm,nDontCare,nnowMT,nnowPI;
int nPI=0,nEPI=0,PotEPINo=0,MinimumNo=0,Grouping=1,npossibleEPI=1;
int  **Minterm_Binary,*DontCareDecimal, *MintermIndicesDecimal,****Column;
int **EPI_Index,**PI_Index,**ReducedPIChart_Y,*ReducedPIChart_X,*nCounter;
int **Potential_EPI,**ReducedPIChart,*For, *nPIForEPI;

int checkdontcare(int MT)
{
    
    f(i,0,nDontCare)
    {
        if(MT==DontCareDecimal[i]) return 1;
    }
    return 0;
}

void convertBinary()
{
    int i,j,p;
    f(i,0,nallminterm)
    {
        p=MintermIndicesDecimal[i];
        d(j,nvariable-1,0)
        {
            Minterm_Binary[i][j]=p%2;
            p/=2;
            
        }
    }
}

int OneCounter(int *binary, int nDigit)
{
    int count=0;
    f(i,0,nDigit)
    {
        if(binary[i]==1) count++;
    }
    return count;
}

int Combination(int x, int nColumn, int y)
{
    int var=1,vari=1;
    d(i,x,x-y+1-nColumn) var*=i;
    d(i,y,1) vari*=i;
    return var/vari;
} 

int checkPowerOfTwo(int num)
{
    int i=floor(log(num)/log(2))==(log(num)/log(2));
    return (i);
}

void Result();

void Recursion_For_Loop(int v)
{
    int n=v;
    For[n]=0;
    while(For[n]<nnowPI)
    {
        if(ReducedPIChart[nnowMT-1-n][For[n]])
        {
            if(n==0)
            {
                f(i,0,nnowMT) Potential_EPI[PotEPINo][i]=For[nnowMT-1-i];
                PotEPINo++;
            }
            
            else if(n>0)
            {
                v=n;
                v=v-1;
                Recursion_For_Loop(v);
            }
        }
    For[n]++;
    }
}


int main()
{
    int l,k,LogicProbe,x,n,m,y,z;

    printf("Enter the number of variables : ");
    scanf("%d",&nvariable);

    do{
        printf("\nenter total minterms including Don't-Cares(less than 2^%d and greater than 1):",nvariable);
        scanf("%d",&nallminterm);
        
    }while(nallminterm>pow(2,nvariable) || nallminterm<=0);
    
    do{
        printf("\nenter total Don't-Cares(less than the %d nor greater than 0):",nallminterm);
        scanf("%d",&nDontCare);
    }while(nDontCare>=nallminterm || nDontCare<0);
    
    MintermIndicesDecimal=(int *)malloc(nallminterm*sizeof(int));
    
    f(i,0,nallminterm)
    {
        do{   
            printf("\nenter the decimal index of the %dth minterm in ascending order",i+1);
            printf("\nThe number should be smaller than %lf :",pow(2,nvariable));
            scanf("%d",&MintermIndicesDecimal[i]);
            
        }while(MintermIndicesDecimal[i]<=MintermIndicesDecimal[i-1]&&MintermIndicesDecimal[i]>=pow(2,nvariable));
    }
    
    if(nDontCare!=0)
    {
        printf("\nenter dontcare terms:");
        DontCareDecimal=(int *)malloc(nDontCare*sizeof(int));
        
        f(i,0,nDontCare)
        {
            do{   
                printf("\nenter the decimal index of the %dth Don'tCare in ascending order",i+1);
                printf("\nThe number should be smaller than %lf :",pow(2,nvariable));
                scanf("%d",&DontCareDecimal[i]);
                
            }while(DontCareDecimal[i]<=DontCareDecimal[i-1]&&DontCareDecimal[i]>=pow(2,nvariable));
        }
    }
    
    Minterm_Binary=(int **)malloc(nallminterm*sizeof(int*));
    
    f(i,0,nallminterm) Minterm_Binary[i]=(int *)malloc((nvariable+4)*sizeof(int));

    convertBinary();

    f(i,0,nallminterm)
    {
        Minterm_Binary[i][nvariable+1]=0;
        Minterm_Binary[i][nvariable]=OneCounter(Minterm_Binary[i],nvariable);
        Minterm_Binary[i][nvariable+2]=Minterm_Binary[i][nvariable+3]=MintermIndicesDecimal[i];
        
    }

    Column=(int ****)malloc((nvariable+1)*sizeof(int***));
    
    f(i,0,nvariable+1) Column[i]=(int ***)malloc((nvariable+1-i)*sizeof(int**));
    
    f(i,0,nvariable+1)
    {
        f(j,0,nvariable+1-i)
        {
         Column[i][j]=(int**)malloc(Combination(nvariable,i,j)*sizeof(int*)); 
         f(k,0,Combination(nvariable,i,j)) Column[i][j][k]=NULL;
            
        }
        
    }
    
    f(i,0,nvariable+1)
    {
        int k=0;
        f(j,0,nallminterm)
        {
            if(Minterm_Binary[j][nvariable]==i) Column[0][i][k++]=Minterm_Binary[j];
            
        }
        
    }
    
    f(i,0,nvariable+1)
    {
        if(Grouping)
        {
            Grouping=0;
            f(j,0,nvariable-i)
            {
                int position;
                int p,m=0;
                f(k,0,Combination(nvariable,i,j))
                if(Column[i][j][k]!=NULL)
                {
                    f(l,0,Combination(nvariable,i,j+1))
                    {
                        if(Column[i][j+1][l]!=NULL&& Column[i][j+1][l][nvariable+2+i]>Column[i][j][k][nvariable+2+i] &&checkPowerOfTwo(Column[i][j+1][l][nvariable+2+i]-Column[i][j][k][nvariable+2+i]))
                        {
                            LogicProbe=-1*(i);
                            f(n,1,i+1)
                            f(p,1,i+1)
                            if(Column[i][j+1][l][nvariable+1+n]==Column[i][j][k][nvariable+1+p])
                            {
                                LogicProbe=LogicProbe+1;
                                
                            }
                            if(LogicProbe==0) 
                            {
                                Grouping=1;
                                Column[i+1][j][m]=(int *)malloc((nvariable+4+i+pow(2,i+1))*sizeof(int));
                                Column[i][j][k][nvariable+1]=Column[i][j+1][l][nvariable+1]=1;
                                f(n,0,nvariable+2+i)
                                {
                                    Column[i+1][j][m][n]=Column[i][j][k][n];
                                }
                                Column[i+1][j][m][nvariable+3+i]=Column[i][j][k][nvariable+2+i];
                                
                                f(n,nvariable+4+i,nvariable+4+i+pow(2,i+1))
                                Column[i+1][j][m][n]=Column[i+1][j][m][nvariable+1]=0;
                                position=log((Column[i][j+1][l][nvariable+2+i]-Column[i][j][k][nvariable+2+i]))/log(2);
                                Column[i+1][j][m][nvariable-1-position]=2;
                                Column[i+1][j][m][nvariable+2+i]=position;
                                f(p,0,pow(2,i)){
                                Column[i+1][j][m][nvariable+4+i+p]=Column[i][j][k][nvariable+3+i+p];}
                                f(p,pow(2,i),pow(2,i+1)){
                                Column[i+1][j][m][nvariable+4+i+p]=Column[i][j+1][l][nvariable+3+i+p-(int)pow(2,i)];}
                                m=m+1;
                            }
                        } 
                    }
                }
            }
        }
    }
    nCounter=(int *)malloc(pow(2,nvariable)*sizeof(int));
    f(i,0,pow(2,nvariable)) nCounter[i]=0;
    PI_Index=(int **)malloc(nallminterm*sizeof(int*));
    f(i,0,nallminterm)
    {
        PI_Index[i]=(int *)malloc(3*sizeof(int));
        
    }
    f(i,0,nvariable+1)
    {
        f(j,0,nvariable+1-i)
        f(k,0,Combination(nvariable,i,j))
            {
                if(Column[i][j][k]!=NULL &&Column[i][j][k][nvariable+1]==0)
                {
                    LogicProbe=-1*pow(2,i); 
                    d(l,k-1,0)
                        if(LogicProbe!=0)
                        {
                            LogicProbe=-1*pow(2,i);
                            f(m,0,pow(2,i))
                            f(n,0,pow(2,i))
                                if(Column[i][j][l][nvariable+3+i+m]==Column[i][j][k][nvariable+3+i+n]) LogicProbe++;
                            
                        }
                        if(LogicProbe!=0)
                        {
                            
                            PI_Index[nPI][1]=j;
                            PI_Index[nPI][2]=k;
                            PI_Index[nPI][0]=i;
                            nPI=nPI+1;
                            f(l,0,pow(2,i))
                            nCounter[Column[i][j][k][nvariable+3+i+l]]=nCounter[Column[i][j][k][nvariable+3+i+l]]+1;
                        }
                }  
            }
    }
    
    f(i,0,nDontCare) nCounter[DontCareDecimal[i]]=0;
    
    EPI_Index=(int **)malloc(nallminterm*sizeof(int*));
    
    f(i,0,pow(2,nvariable))
    {
        if(nCounter[i]==1)
        f(j,0,nPI)
        {
            f(k,0,pow(2,PI_Index[j][0]))
            {
                if(Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][nvariable+3+PI_Index[j][0]+k]==i)
                {
                    EPI_Index[nEPI]=PI_Index[j];
                    f(l,0,pow(2,PI_Index[j][0]))
                    nCounter[Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][nvariable+3+PI_Index[j][0]+l]]=0;
                    nEPI=nEPI+1;
                    k=pow(2,PI_Index[j][0]);
                }
            }
        }
    }
    
    nnowMT=0;
    f(i,0,pow(2,nvariable))
    {
        if(nCounter[i]!=0)
        nnowMT++;
        
    }
    
    ReducedPIChart_X=(int *)malloc(nnowMT*sizeof(int));
    ReducedPIChart_Y=(int **)malloc(nPI*sizeof(int*));
    ReducedPIChart=(int **)malloc(nnowMT*sizeof(int*));
    
    f(i,0,nnowMT) ReducedPIChart_X[i]=-1;
    f(i,0,nPI) ReducedPIChart_Y[i]=NULL;
    
    i=0;
    f(j,0,pow(2,nvariable))
    {
        if(nCounter[j]!=0)
        {
            ReducedPIChart_X[i]=j;
            i++;
        }
    }
    
    nnowPI=0;
    f(i,0,nPI)
    {
        int p=pow(2,PI_Index[i][0]);
        f(j,0,p)
        {
            if(nCounter[Column[PI_Index[i][0]][PI_Index[i][1]][PI_Index[i][2]][nvariable+3+PI_Index[i][0]+j]]!=0)
            {
                j=p; 
                ReducedPIChart_Y[nnowPI]=PI_Index[i];
                nnowPI=nnowPI+1;
            }
        }
        
    }
    
    if(nnowPI!=0)
    {
        For=(int *)malloc(nnowMT*sizeof(int)); 
        f(i,0,nnowMT) ReducedPIChart[i]=(int *)malloc(nnowPI*sizeof(int));
        f(i,0,nnowMT)
        f(j,0,nnowPI) ReducedPIChart[i][j]=0;
        f(i,0,nnowPI)
        f(j,0,pow(2,ReducedPIChart_Y[i][0]))
        f(k,0,nnowMT)
        if(Column[ReducedPIChart_Y[i][0]][ReducedPIChart_Y[i][1]][ReducedPIChart_Y[i][2]][nvariable+3+ReducedPIChart_Y[i][0]+j]==ReducedPIChart_X[k])
        {
            ReducedPIChart[k][i]=1;
        }
        
        f(i,0,nnowMT)
        {
            For[i]=-1;
            
        }
        f(i,0,nnowMT)
        npossibleEPI=npossibleEPI*nCounter[ReducedPIChart_X[i]];
        Potential_EPI=(int **)malloc(npossibleEPI*sizeof(int*));
        f(i,0,npossibleEPI)
        {
            Potential_EPI[i]=(int *)malloc(nnowMT*sizeof(int));
            
        }
        
        Recursion_For_Loop(nnowMT-1);
        nPIForEPI=(int *)malloc(npossibleEPI*sizeof(int));
        f(i,0,npossibleEPI)
        nPIForEPI[i]=0;
        f(i,0,npossibleEPI)
        f(j,0,nnowMT)
        if(Potential_EPI[i][j]!=-1)
        { 
            nPIForEPI[i]++;
            f(k,j+1,nnowMT)
            if(Potential_EPI[i][k]==Potential_EPI[i][j])
            Potential_EPI[i][k]=-1;
        }
        
        f(i,1,npossibleEPI)
        if(nPIForEPI[i]<nPIForEPI[MinimumNo])
        MinimumNo=i;
        f(i,0,nnowMT)
        if(Potential_EPI[MinimumNo][i]!=-1)
        
        EPI_Index[nEPI++]=ReducedPIChart_Y[Potential_EPI[MinimumNo][i]];
        
        printf("\n\nThe minimised boolean expression is: ");
        f(x,0,nEPI)
        {
            f(y,0,nvariable)
            {
                z=Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y];
                if(z==1) printf("%c",65+y);
                else if(z==0) printf("%c'",65+y);
            }
            if(x<nEPI-1) printf("+");
        }
        return 0;
    }
    else
    {
        printf("\n\nThe minimised boolean expression is: ");
        f(x,0,nEPI)
        f(y,0,nvariable)
        if(z==1) printf("%c",65+y);
        else if(z==0) printf("%c'",65+y);
        if(x<nEPI-1) printf("+"); 
        return 0;
        
    }
    
}



