#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int localidad; //1 a 300
    int provincia; //1 a 24
    int zonageo; //1 a 8
}destinos;

typedef struct {
    int local; //1 a 300 ordenado por localidad
    float peso;
    char tipo; //n normal, f fragil , v vencimiento
}envios;

int cargaarchivo(destinos[]);
int buscar(int ,destinos [],int );
void mostrar(float[] ,int[] ,int[] ,int[] ,float );

int main()
{
    int zona=0,contcod,cantenvios,i,antlocalidad,x,masde4k=0,contgral=0,contv=0,maxenvios,pos=0,cant,primero=0,codmax,cantmax;
    int vzonN[8]={0},vzonV[8]={0},vzonF[8]={0};
    float porcenv,vzonPeso[8]={0};
    destinos des[300];
    envios env;

    cant=cargaarchivo(des);
    cargaarchivo(des);
    FILE*fenv;
    fenv=fopen("envios.dat","rb");
    if(fenv==NULL)
    {
    printf("\nError en envios.dat\n");
    system("pause");
    exit(0);
    }

    fread(&env, sizeof(envios),1,fenv);
    while(!feof(fenv))
        {
        antlocalidad=env.local;
        pos=0;
        contcod=0;

        while(antlocalidad==env.local&&!feof(fenv))
            {
            contgral++;
            contcod++;

            if(env.peso>4)
                masde4k++;

            pos=buscar(antlocalidad,des,cant);
            zona=des[pos].zonageo;

            vzonPeso[zona-1]+=env.peso;
            if(env.tipo=='V'||env.tipo=='v')
            {
                contv++;
                vzonV[zona-1]++;
            }
            else if(env.tipo=='N'||env.tipo=='n')
                vzonN[zona-1]++;
            else if(env.tipo=='F'||env.tipo=='f')
                vzonF[zona-1]++;

            fread(&env, sizeof(envios),1,fenv);

            }
            if(primero==0)
            {
                codmax=antlocalidad;
                cantmax=contcod;
                primero++;
            }
            else if(cantmax<contcod)
            {
                codmax=antlocalidad;
                cantmax=contcod;
            }
            printf("\nLa Localidad %d, tuvo %d encomiendas que pesaron mas de 4 kilos",antlocalidad,masde4k); //pto B
            for(i=0;i<=cant;i++)
            {
                if(des[i].localidad!=0)
                    printf("La localidad con codigo %d no realizo pedido",des[i].localidad);//pto C
            }
        }
        printf("El codigo de la localidad que mas envuios realizo es: %d",codmax);//pto A

        porcenv=(contv*contgral)/100; //pto E
        mostrar(vzonPeso,vzonN,vzonF,vzonV,porcenv);//pto D

    fclose(fenv);

    return 0;
}
int buscar(int env,destinos des[],int n)
{
    int x=0,pos=-1;

    while(x<n&&pos==-1)
    {
        if(env==des[x].localidad)
            pos=x;
        else
            x++;
    }

    return pos;
};
int cargaarchivo (destinos des[300])
{
    int can;
    FILE*fdes;
        fdes=fopen("destinos.dat","rb");
        if(fdes==NULL)
            {
            printf("\nError en destinos.dat\n");
            system("pause");
            exit(1);
            }

    fread(&des[can], sizeof(destinos),1,fdes);

    while(!feof(fdes))
        {
            can++;
        fread(&des[can], sizeof(destinos),1,fdes);
        }
    fclose(fdes);

    return can;
};

void mostrar(float z[],int n[],int f[],int v[],float porcen)
{
    int i;

    printf("\nZONA          TOTAL KILOS         TOTAL tipo N            TOTAL tipo F            TOTAL tipo V");
    for(i=0;i<8;i++)
        printf("%d          %.2f          %d          %d          %d",i+1,z[i],n[i],f[i],v[i]);
    printf("\nEl porcentaje de encomiendas de tipo V es: %.2f",porcen);
};
