#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <windows.h>
#define N 1000//���ݿ��������
#define S 10//Ӣ��������󳤶�
struct user//������һ���û����Ͻṹ��
{
    char name[S];  //����
    int account[2];//�ʻ���Ϣ
    int methods[1];//�Ʒѷ���
}U[N];//������һ���ṹ�����U
typedef struct user user;
struct clocks//������һ��ʱ��ṹ��
{
    int year[2];
    int month[1];
    int day[1];
    int hour[1]; 
    int minute[1];
    int sec[1];
};//������һ���ṹ�����T
typedef struct clocks clocks;//�ṹ��Ƕ�� 
struct times//������һ������ʱ��ṹ��
{
    int account[2];  //�˻�
    clocks time_start[1];//��ʼʱ��
    clocks time_end[1];//����ʱ��
}T[N];//������һ���ṹ�����T

typedef struct times times;
struct expend//������һ���������
{   
    int account;//�ʻ���Ϣ
    char name[S];  //����
    int methods;//�Ʒѷ���;  //�û����� 
    int min;//������ʱ 
    float expend;//��� 
}E[N];//������һ���ṹ�����T
typedef struct expend expend;
#define sizeusers sizeof(user)
#define sizetime sizeof(times)
#define sizeexpend sizeof(expend)
int p=0;//ͳ���û�����
FILE*fp;

int Usernumber(user U[]);
int Timenumber(times T[]);
void readFile(user U[]);
void saveFile(user U[],int n);
void saveFileTIME(times T[],int n);
void readFileTIME(times T[]);
void readFileEXPEND(times T[]);
void saveFileEXPEND(expend E[],int n);
void adduserdata();
void addnetdata();
void deluserdata();
void deltimedata();
float cal00(int min);
float cal01(int min);
float cal02(int min);
float cal03(int min);
float cal04();
int dayofmonth(int a,char b[]);
void calexpense(times T[],user U[]);
int  titoei(int min,user U[],times T[],expend E[],int i);
void randaddnetdata();
int main()
{
   
    fp = fopen("D:\\�Ʒ�ϵͳ\\�û�����.txt","a+");
    readFile(U);
    p=Usernumber(U);
    int n;
    char i,o;
    begin:printf("\n");
    printf("\t******************************************************\n");
    printf("\t**     1���û�����¼��      2��������¼¼��          **\n");
    printf("\t**     3���û�����ɾ��      4��������¼ɾ��          **\n");
    printf("\t**     5�����Ѽ���          6��������¼����          **\n");
    printf("\t**                  7���˳�ϵͳ                      **\n");
    printf("\t******************************************************\n");
    printf("        ��ѡ������Ҫ�Ĳ������<1-10>,���س�����:");
    while(1)
    {
        scanf("%d%c",&n,&o);
        switch(n)//ͨ��swtich������Ҫ����Ĺ���
        {
            case 1:adduserdata();break;
            case 2:addnetdata();break;
			case 3:deluserdata();break;
			
	        case 4:deltimedata();break;
			case 5:calexpense(T,U);break;
			case 6:randaddnetdata();break;
            case 7:{
                printf("���Ҫ�˳���  ������Y��N\n");
                scanf("%c",&i);
                if(i=='Y')
                {
                    exit(0);
                }
                else
                {
                    goto begin;
                }
            }//�˳�ϵͳ
            default:printf("�������˴���Ĺ��ܴ��룬�޷�ִ�У�����������");
                goto begin;//�������г���
        }goto begin;
    }
    return 0;
}

void adduserdata()
{
    char i,o;
    p=Usernumber(U);
    do{
        printf("����¼���%d���û�\n",p+1);
        printf("�������û�����:\n");
        scanf("%[^\n]",U[p].name);

        printf("�������û��˺�:\n");
        scanf("%s",U[p].account);

        printf("������Ʒѷ�ʽ:\n");
        scanf("%s",U[p].methods);
        p++;
        printf("¼��ɹ����Ƿ����¼��?������Y��N\n");
        scanf("%s%c",&i,&o);
		saveFile(U,p);
    }while(i=='Y');
    printf("���ڹ���%d���û�",p);
    
}
void addnetdata()
{
    char i,o;
    p=Timenumber(T);
    do{
        printf("����¼���%d������\n",p+1);
        printf("�������û��ʺ�:\n");
        scanf("%[^\n]",T[p].account);

        printf("�����뿪ʼʱ��:\n");
        scanf("%4s%2s%2s%2s%2s%2s",T[p].time_start[0].year,T[p].time_start[0].month,T[p].time_start[0].day,T[p].time_start[0].hour,T[p].time_start[0].minute,T[p].time_start[0].sec);
        printf("���������ʱ��:\n");
        scanf("%4s%2s%2s%2s%2s%2s",T[p].time_end[0].year,T[p].time_end[0].month,T[p].time_end[0].day,T[p].time_end[0].hour,T[p].time_end[0].minute,T[p].time_end[0].sec);
        p++; 
        printf("¼��ɹ����Ƿ����¼��?������Y��N\n");
        scanf("%s%c",&i,&o);
		
    }while(i=='Y');
    printf("���ڹ���%d������",p);
    saveFileTIME(T,p);
}
    void calexpense(times T[],user U[]){//�����û�ÿ������ʱ�� 
	char year[4],month[2];
	int daysum;
	int min=0;
	int i=0,j,r;
	int n;
	char years[4];
	
	p=Timenumber(T);
	printf("���������:\n");
    scanf("%s",&year);
    //printf("%d",atoi(T[i].time_start[0].month));
    printf("�������·�:\n");
    scanf("%s",&month);

    daysum=dayofmonth(atoi(year),month);////////////////////////////////////////////////////////////////////////////////////////////////////////////////////��취ʵ�����µļ��� 
    /*	printf("%d\n",atoi(T[i].time_start[0].year)<=atoi(year)&&atoi(year)<=atoi(T[i].time_end[0].year));
    	printf("%d\n",atoi(T[i].time_start[0].month)<=atoi(month)&&atoi(month)<=atoi(T[i].time_end[0].month));
    	printf("%d\n",atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month));
    	printf("%d\n",atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month));
    	printf("%d\n",atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)==atoi(T[i].time_end[0].month));
    	printf("%d\n",atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month));
    */
    	
    	
    for(i=0;i<p;i++)
    {
    	if(atoi(T[i].time_start[0].year)<=atoi(year)&&atoi(year)<=atoi(T[i].time_end[0].year))
		{
		
            if(atoi(T[i].time_start[0].year)!=atoi(year)&&atoi(year)!=atoi(T[i].time_end[0].year))
	        {
	   	    min=daysum*1440;
	   	     r=titoei(min,U,T,E,i);
	        }
	        if(atoi(T[i].time_start[0].year)==atoi(year)&&atoi(year)!=atoi(T[i].time_end[0].year))
	        {
	   	        if(atoi(T[i].time_start[0].month)<=atoi(month))
	   	        {
	   	        	if(atoi(T[i].time_start[0].month)==atoi(month))
					   {
	   	        		min=daysum*1440-((atoi(T[i].time_start[0].day)-1)*1440+atoi(T[i].time_start[0].hour)*60+atoi(T[i].time_start[0].minute));
					    r=titoei(min,U,T,E,i);
						}
					if(atoi(T[i].time_start[0].month)!=atoi(month))
					   {
						min=daysum*1440;
						 r=titoei(min,U,T,E,i);
					   }   
				}
	   
	        }
	        if(atoi(T[i].time_start[0].year)!=atoi(year)&&atoi(year)==atoi(T[i].time_end[0].year))
	        {
	        	if(atoi(T[i].time_end[0].month)>=atoi(month))
				{
				
	        	if(atoi(month)==atoi(T[i].time_end[0].month))
				{
	        	    min=(atoi(T[i].time_end[0].day)-1)*1440+atoi(T[i].time_end[0].hour)*60+atoi(T[i].time_end[0].minute);	
	        	     r=titoei(min,U,T,E,i);
				}
				if(atoi(month)!=atoi(T[i].time_end[0].month))
				{
					min=daysum*1440;
					 r=titoei(min,U,T,E,i);
				}
			    }
			}
	   
            if(atoi(T[i].time_start[0].year)==atoi(year)&&atoi(year)==atoi(T[i].time_end[0].year))//������λ����ʼ��ͽ�����֮�� 
            {
        	if(atoi(T[i].time_start[0].month)<=atoi(month)&&atoi(month)<=atoi(T[i].time_end[0].month))//������λ����ʼ�ºͽ�����֮�� 
			{
		    		
					if(atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month))//����������ʼ���Ҳ��ǽ����� 
					{
						min=daysum*1440-((atoi(T[i].time_start[0].day)-1)*1440+atoi(T[i].time_start[0].hour)*60+atoi(T[i].time_start[0].minute));
				     r=titoei(min,U,T,E,i);
				    }
					if(atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)==atoi(T[i].time_end[0].month))//�������ǽ������Ҳ�����ʼ�� 
					{
				    	min=(atoi(T[i].time_end[0].day)-1)*1440+atoi(T[i].time_end[0].hour)*60+atoi(T[i].time_end[0].minute);
		            r=titoei(min,U,T,E,i);
					}
					if(atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)==atoi(T[i].time_end[0].month))//����������ʼ�����ǽ����� 
					{
				        min=(atoi(T[i].time_end[0].day)-1)*1440+atoi(T[i].time_end[0].hour)*60+atoi(T[i].time_end[0].minute)-((atoi(T[i].time_start[0].day)-1)*1440+atoi(T[i].time_start[0].hour)*60+atoi(T[i].time_start[0].minute));
				    r=titoei(min,U,T,E,i);
		            }
					if(atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month))//�����¼�����ʼ�����ǽ����� 
					{
						min=daysum*1440;
					r=titoei(min,U,T,E,i);
					}
			 
			 
            }
            }
            
			 
	   }
	  
    } 
	//Ҫ��U��I��account ��ϵ������ȷ��U��methods 
	
    saveFileEXPEND(E,r);
    
}

int Usernumber(user U[])

{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\�û�����.txt","rb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        return 0;
    }
    fread(&U[i],sizeusers,1,fp);
    while(!feof(fp))
    {
        i++;
        fread(&U[i],sizeusers,1,fp);
    }
    fclose(fp);
    return i;
}
int Timenumber(times T[])

{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\������¼�ļ�.txt","rb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        return 0;
    }
    fread(&T[i],sizetime,1,fp);
    while(!feof(fp))
    {
        i++;
        fread(&T[i],sizetime,1,fp);
    }
    fclose(fp);
    return i;
}

void readFile(user U[])
{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\�û�����.txt","rb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }
    fread(&U[i],sizeusers,1,fp);
    while(!feof(fp))
    {
        i++;
        fread(&U[i],sizeusers,1,fp);
    }
    fclose(fp);
}
void readFileTIME(times T[])
{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\������¼�ļ�.txt","rb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }
    fread(&T[i],sizetime,1,fp);
    while(!feof(fp))
    {
        i++;
        fread(&T[i],sizetime,1,fp);
    }
    fclose(fp);
}
void readFileEXPEND(times T[])
{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\�����Ʒ�.txt","rb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }
    fread(&E[i],sizeexpend,1,fp);
    while(!feof(fp))
    {
        i++;
        fread(&E[i],sizeexpend,1,fp);
    }
    fclose(fp);
}
void saveFile(user U[],int n)
{
    FILE*fp;
	
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\�û�����.txt","wb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }
    //fprintf(fp,"%s%s%s",U[n].name,U[n].account,U[n].methods);

    fwrite(U,sizeusers,n,fp);
    
    fputc("\n",fp);
    fclose(fp);
    

}
void saveFileTIME(times T[],int n)
{
    FILE*fp;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\������¼�ļ�.txt","wb"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }

    fwrite(T,sizetime,n,fp);
    fclose(fp);

}
void saveFileEXPEND(expend E[],int n)
{
    FILE*fp;
    if((fp=fopen("D:\\�Ʒ�ϵͳ\\��������.txt","w+"))==NULL)
    {
        printf("file dose not exist,creat it first:\n");
        exit(0);
    }

    fwrite(E,sizeexpend,n,fp);
    fclose(fp);

}
void  deluserdata()
{
    int i=0,j;
    char s[20];
    p=Usernumber(U);
    printf("��������Ҫɾ�����û���:");
    scanf("%[^\n]",s);
    for(i=0;i<p;i++)
    {

        if((strcmp(s,U[i].name))==0)
        {
            for(j=i;j<p;j++)
            {
                U[j]=U[j+1];
                p--;
            }
            printf("ɾ���ɹ���\n");
        }
        else if(i==p-1)
        {printf("δ�ҵ���Ҫɾ�����û�!\n");

        }
    }
}
void deltimedata()
{
    int i=0,j;
    char s[20];
    p=Timenumber(T);
    printf("��������Ҫɾ�����˺�:");
    scanf("%[^\n]",s);
    for(i=0;i<p;i++)
    {

        if((strcmp(s,T[i].account))==0)
        {
            for(j=i;j<p;j++)
            {
                T[j]=T[j+1];
                p--;
            }
            printf("ɾ���ɹ���\n");
        }
        else if(i==p-1)
        {printf("δ�ҵ���Ҫɾ�����ʺ�!\n");

        }
    }
    saveFileTIME(T,p);

}
float cal00(int min){
	return min*0.03;
} 

float cal01(int min){
	if(min<=1800){
		return 50;
	}else
	{
		return 50+(min-1800)*0.03;
	}
} 
float cal02(int min){
	if(min<=3600){
		return 95;
	}else
	{
		return 95+(min-3600)*0.03;
	}
} 
float cal03(int min){
	if(min<=9000){
		return 200;
	}else
	{
		return 200+(min-9000)*0.03;
	}
} 
float cal04(){
    return 300;
}  
int dayofmonth(int a,char b[])

{

    if(strcmp(b,"02")==0)
    {
        if((a%4==0 && (a%100)!=0) || (a%400==0))
            return 29;
        else
            return 28;
    }
    if(strcmp(b,"01")==0 || strcmp(b,"03")==0 || strcmp(b,"05")==0 || strcmp(b,"07")==0 || strcmp(b,"09")==0 || strcmp(b,"10")==0 || strcmp(b,"12")==0)
       return 31; 
    if(strcmp(b,"04")==0 || strcmp(b,"06")==0 || strcmp(b,"09")==0 || strcmp(b,"11")==0)
       return 30;
}

int titoei(int min,user U[],times T[],expend E[],int i)//���T[]��E[]��ת������������ 
{
    int j=0,q,r=0;
	float expend;
    char s[20];
    p=Timenumber(T);
    q=Usernumber(U);
    

        for(j=0;j<q;j++)
		{
		 
        if((strcmp(T[i].account,U[j].account))==0)
        {
        	
            E[r].account=U[j].account;
            strcpy(E[r].name,U[j].name);
            E[r].methods=U[j].methods;
            E[r].min=min;		
			switch(atoi(E[r].methods))//ͨ��swtich������Ҫ����Ĺ���
        {
            case 0:expend=cal00(min);break;
            case 1:expend=cal01(min);break;
			case 2:expend=cal02(min);break;
			case 3:expend=cal03(min);break;
            case 4:expend=cal04();break;   
        }
            E[r].expend=expend;
            printf("\n%s ",E[r].account);
            printf("%s ",E[r].name);
            printf("%s ",E[r].methods);
            printf("%d���� ",min);
            printf("%fԪ ",expend);
	
        r++;
        }
		} 
      
    

    return r;
}

/*void randaddnetdata(times T[])//д��һ������˵ĺ��� 
{
    int j;
    char str[4] ;
    char str2[2]; 
    p=Timenumber(T);
    srand(time(NULL)); //��ʼ��ʱ������
   
    for(j=p;j<150+p;j++)
    {   
	    itoa(rand()%15+1,str,10);
    	strcpy(T[p].account,str);
    	itoa(rand()%51+2000,str,10);
        strcpy(T[p].time_start[0].year,str,10); //����   
		if(month=rand()%12+1<10){
			itoa(month,str2,10);
			strcat ("0","str2");
			strcpy(T[p].time_start[0].month,str2,10);
		}else{
		
		itoa(month,str2,10);
		strcpy(T[p].time_start[0].month,str2,10);
	    }
	    if(day=rand()%28+1<10){
			itoa(day,str2,10);
			strcat ("0","str2");
			strcpy(T[p].time_start[0].day,str2,10);
		}else{
		
		itoa(day,str2,10);
		strcpy(T[p].time_start[0].day,str2,10);
	    }
		if(hour=rand()%12+1<10){
			itoa(hour,str2,10);
			strcat ("0","str2");
			strcpy(T[p].time_start[0].hour,str2,10);
		}else{
		
		itoa(hour,str2,10);
		strcpy(T[p].time_start[0].hour,str2,10);
	    }
        
        T[p].time_start[0].minute=rand()%60+1;
        T[p].time_start[0].sec=rand()%60+1;
        T[p].time_end[0].year=rand()%51+2000; //����   
        T[p].time_end[0].month=rand()%12+1;
        T[p].time_end[0].day=rand()%28+1;
        T[p].time_end[0].hour =rand()%12+1;
        T[p].time_end[0].minute=rand()%60+1;
        T[p].time_end[0].sec=rand()%60+1;
        if(T[p].time_start[0].year>=T[p].time_end[0].year){
        	T[p].time_end[0].year=T[p].time_start[0].year;
		}
    }
    printf("���ڹ���%d������",p);
    saveFileTIME(T,p);
}
*/        
        void randaddnetdata(){
        	 srand((unsigned)(time(NULL))+rand());//���������
        	int syear,smonth,sday,shour,sminute,ssec;
            int eyear,emonth,eday,ehour,eminute,esec;
            int account;
            int a;
            int j=0;
    for(j=0;j<100;j++)
    {   
        account=rand()%15+1;
		syear=rand()%51+2000; //����   
        smonth=rand()%12+1;
        sday=rand()%28+1;
        shour =rand()%12+1;
        sminute=rand()%60+1;
        ssec=rand()%59+1;
        
        eyear=rand()%51+2000; //����   
        emonth=rand()%12+1;
        eday=rand()%28+1;
        ehour =rand()%12+1;
        eminute=rand()%60+1;
        esec=rand()%59+1;
        if(syear>eyear){
        	a=eyear;
        	eyear=syear;
        	syear=a;
		}
		if(syear==eyear){
			if(smonth>emonth){
				a=emonth;
        	    emonth=smonth;
        	    smonth=a;
			}
			if(smonth==emonth){
				if(sday>eday){
					a=eday;
        	        eday=sday;
        	        sday=a;
				}
				if(sday==eday){
                    if(shour>ehour){
                    	a=ehour;
        	            ehour=shour;
        	            shour=a;
					}
					if(shour==ehour){
						if(sminute>eminute){
							a=eminute;
        	                eminute=sminute;
        	                sminute=a;
						}
					}
				}
			}
		}
			printf("%4d %4d %2d %2d %2d %2d %2d   %4d %2d %2d %2d %2d %2d\n",account,syear,smonth,sday,shour,sminute,ssec,eyear,emonth,eday,ehour,eminute,esec) ;
	        	
	}

} 


