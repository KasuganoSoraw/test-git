#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <windows.h>
#define N 1000//数据库最大容量
#define S 10//英文中文最大长度
struct user//定义了一个用户资料结构体
{
    char name[S];  //姓名
    int account[2];//帐户信息
    int methods[1];//计费方法
}U[N];//定义了一个结构体变量U
typedef struct user user;
struct clocks//定义了一个时间结构体
{
    int year[2];
    int month[1];
    int day[1];
    int hour[1]; 
    int minute[1];
    int sec[1];
};//定义了一个结构体变量T
typedef struct clocks clocks;//结构体嵌套 
struct times//定义了一个上网时间结构体
{
    int account[2];  //账户
    clocks time_start[1];//开始时间
    clocks time_end[1];//结束时间
}T[N];//定义了一个结构体变量T

typedef struct times times;
struct expend//定义了一个上网金额
{   
    int account;//帐户信息
    char name[S];  //姓名
    int methods;//计费方法;  //用户资料 
    int min;//上网用时 
    float expend;//金额 
}E[N];//定义了一个结构体变量T
typedef struct expend expend;
#define sizeusers sizeof(user)
#define sizetime sizeof(times)
#define sizeexpend sizeof(expend)
int p=0;//统计用户总数
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
   
    fp = fopen("D:\\计费系统\\用户资料.txt","a+");
    readFile(U);
    p=Usernumber(U);
    int n;
    char i,o;
    begin:printf("\n");
    printf("\t******************************************************\n");
    printf("\t**     1、用户资料录入      2、上网记录录入          **\n");
    printf("\t**     3、用户资料删除      4、上网记录删除          **\n");
    printf("\t**     5、网费计算          6、上网记录生成          **\n");
    printf("\t**                  7、退出系统                      **\n");
    printf("\t******************************************************\n");
    printf("        请选择您需要的操作序号<1-10>,按回车结束:");
    while(1)
    {
        scanf("%d%c",&n,&o);
        switch(n)//通过swtich语句决定要进入的功能
        {
            case 1:adduserdata();break;
            case 2:addnetdata();break;
			case 3:deluserdata();break;
			
	        case 4:deltimedata();break;
			case 5:calexpense(T,U);break;
			case 6:randaddnetdata();break;
            case 7:{
                printf("真的要退出吗？  请输入Y或N\n");
                scanf("%c",&i);
                if(i=='Y')
                {
                    exit(0);
                }
                else
                {
                    goto begin;
                }
            }//退出系统
            default:printf("你输入了错误的功能代码，无法执行！请重新输入");
                goto begin;//重新运行程序
        }goto begin;
    }
    return 0;
}

void adduserdata()
{
    char i,o;
    p=Usernumber(U);
    do{
        printf("正在录入第%d个用户\n",p+1);
        printf("请输入用户姓名:\n");
        scanf("%[^\n]",U[p].name);

        printf("请输入用户账号:\n");
        scanf("%s",U[p].account);

        printf("请输入计费方式:\n");
        scanf("%s",U[p].methods);
        p++;
        printf("录入成功，是否继续录入?请输入Y或N\n");
        scanf("%s%c",&i,&o);
		saveFile(U,p);
    }while(i=='Y');
    printf("现在共有%d个用户",p);
    
}
void addnetdata()
{
    char i,o;
    p=Timenumber(T);
    do{
        printf("正在录入第%d条数据\n",p+1);
        printf("请输入用户帐号:\n");
        scanf("%[^\n]",T[p].account);

        printf("请输入开始时间:\n");
        scanf("%4s%2s%2s%2s%2s%2s",T[p].time_start[0].year,T[p].time_start[0].month,T[p].time_start[0].day,T[p].time_start[0].hour,T[p].time_start[0].minute,T[p].time_start[0].sec);
        printf("请输入结束时间:\n");
        scanf("%4s%2s%2s%2s%2s%2s",T[p].time_end[0].year,T[p].time_end[0].month,T[p].time_end[0].day,T[p].time_end[0].hour,T[p].time_end[0].minute,T[p].time_end[0].sec);
        p++; 
        printf("录入成功，是否继续录入?请输入Y或N\n");
        scanf("%s%c",&i,&o);
		
    }while(i=='Y');
    printf("现在共有%d条数据",p);
    saveFileTIME(T,p);
}
    void calexpense(times T[],user U[]){//计算用户每月上网时间 
	char year[4],month[2];
	int daysum;
	int min=0;
	int i=0,j,r;
	int n;
	char years[4];
	
	p=Timenumber(T);
	printf("请输入年份:\n");
    scanf("%s",&year);
    //printf("%d",atoi(T[i].time_start[0].month));
    printf("请输入月份:\n");
    scanf("%s",&month);

    daysum=dayofmonth(atoi(year),month);////////////////////////////////////////////////////////////////////////////////////////////////////////////////////想办法实现闰月的计算 
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
	   
            if(atoi(T[i].time_start[0].year)==atoi(year)&&atoi(year)==atoi(T[i].time_end[0].year))//输入年位于起始年和结束年之间 
            {
        	if(atoi(T[i].time_start[0].month)<=atoi(month)&&atoi(month)<=atoi(T[i].time_end[0].month))//输入月位于起始月和结束月之间 
			{
		    		
					if(atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month))//输入月是起始月且不是结束月 
					{
						min=daysum*1440-((atoi(T[i].time_start[0].day)-1)*1440+atoi(T[i].time_start[0].hour)*60+atoi(T[i].time_start[0].minute));
				     r=titoei(min,U,T,E,i);
				    }
					if(atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)==atoi(T[i].time_end[0].month))//输入月是结束月且不是起始月 
					{
				    	min=(atoi(T[i].time_end[0].day)-1)*1440+atoi(T[i].time_end[0].hour)*60+atoi(T[i].time_end[0].minute);
		            r=titoei(min,U,T,E,i);
					}
					if(atoi(T[i].time_start[0].month)==atoi(month)&&atoi(month)==atoi(T[i].time_end[0].month))//输入月是起始月且是结束月 
					{
				        min=(atoi(T[i].time_end[0].day)-1)*1440+atoi(T[i].time_end[0].hour)*60+atoi(T[i].time_end[0].minute)-((atoi(T[i].time_start[0].day)-1)*1440+atoi(T[i].time_start[0].hour)*60+atoi(T[i].time_start[0].minute));
				    r=titoei(min,U,T,E,i);
		            }
					if(atoi(T[i].time_start[0].month)!=atoi(month)&&atoi(month)!=atoi(T[i].time_end[0].month))//输入月既是起始月又是结束月 
					{
						min=daysum*1440;
					r=titoei(min,U,T,E,i);
					}
			 
			 
            }
            }
            
			 
	   }
	  
    } 
	//要把U和I的account 联系起来，确定U的methods 
	
    saveFileEXPEND(E,r);
    
}

int Usernumber(user U[])

{
    FILE*fp;
    int i=0;
    if((fp=fopen("D:\\计费系统\\用户资料.txt","rb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\上网记录文件.txt","rb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\用户资料.txt","rb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\上网记录文件.txt","rb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\上网计费.txt","rb"))==NULL)
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
	
    if((fp=fopen("D:\\计费系统\\用户资料.txt","wb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\上网记录文件.txt","wb"))==NULL)
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
    if((fp=fopen("D:\\计费系统\\上网费用.txt","w+"))==NULL)
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
    printf("输入你想要删除的用户名:");
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
            printf("删除成功！\n");
        }
        else if(i==p-1)
        {printf("未找到你要删除的用户!\n");

        }
    }
}
void deltimedata()
{
    int i=0,j;
    char s[20];
    p=Timenumber(T);
    printf("输入你想要删除的账号:");
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
            printf("删除成功！\n");
        }
        else if(i==p-1)
        {printf("未找到你要删除的帐号!\n");

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

int titoei(int min,user U[],times T[],expend E[],int i)//完成T[]到E[]的转换，并计算金额 
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
			switch(atoi(E[r].methods))//通过swtich语句决定要进入的功能
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
            printf("%d分钟 ",min);
            printf("%f元 ",expend);
	
        r++;
        }
		} 
      
    

    return r;
}

/*void randaddnetdata(times T[])//写到一半放弃了的函数 
{
    int j;
    char str[4] ;
    char str2[2]; 
    p=Timenumber(T);
    srand(time(NULL)); //初始化时间种子
   
    for(j=p;j<150+p;j++)
    {   
	    itoa(rand()%15+1,str,10);
    	strcpy(T[p].account,str);
    	itoa(rand()%51+2000,str,10);
        strcpy(T[p].time_start[0].year,str,10); //区间   
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
        T[p].time_end[0].year=rand()%51+2000; //区间   
        T[p].time_end[0].month=rand()%12+1;
        T[p].time_end[0].day=rand()%28+1;
        T[p].time_end[0].hour =rand()%12+1;
        T[p].time_end[0].minute=rand()%60+1;
        T[p].time_end[0].sec=rand()%60+1;
        if(T[p].time_start[0].year>=T[p].time_end[0].year){
        	T[p].time_end[0].year=T[p].time_start[0].year;
		}
    }
    printf("现在共有%d条数据",p);
    saveFileTIME(T,p);
}
*/        
        void randaddnetdata(){
        	 srand((unsigned)(time(NULL))+rand());//随机数生成
        	int syear,smonth,sday,shour,sminute,ssec;
            int eyear,emonth,eday,ehour,eminute,esec;
            int account;
            int a;
            int j=0;
    for(j=0;j<100;j++)
    {   
        account=rand()%15+1;
		syear=rand()%51+2000; //区间   
        smonth=rand()%12+1;
        sday=rand()%28+1;
        shour =rand()%12+1;
        sminute=rand()%60+1;
        ssec=rand()%59+1;
        
        eyear=rand()%51+2000; //区间   
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


