#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <string>
#include <ctime>
#include <iomanip>
#include <windows.h>
using namespace std;
//********************全局变量****************************
int N;                        		//背包总个数 
int WMAX;                      		//最大容量 
int cw=0,cp=0;                 		//当前重量和价值
int max_value=0;    	       		//结果：最大价值 
double totaltime=0;            		//计算函数时间 
int vw[200];            	   		//单位重量比 
int w_v[200][2];    	       		//价值重量数组
int T[1500][1500];  	       		//动态规划表格 
int decrease[200];  	       		//保存递减序列的下标 
int vector_quantity[200];  	   		//解向量
int best_results[200];        	 	//解向量副本 
int left_value;                		//剩余总价值：回溯剪枝 
string s;                      		//文件名字符串 
ofstream ofs;                  		//创建输出流对象
ifstream ifs;                       //创建输入流对象

_LARGE_INTEGER time_start;     		/*开始时间*/
_LARGE_INTEGER time_over;      		/*结束时间*/
double dqFreq;                      /*计时器频率*/
LARGE_INTEGER f;                    /*计时器频率*/

//*******************算法函数******************************
int DP();                           //动态规划解决KP问题 
int output();                  		//输出测试数据
int Greedy();                  		//贪心算法解决KP问题
int KnapSack();                		//构建动态规划表 
void get_data();       	            //读文件，取得测试数据
int sort(int choice);          		//按单位重量价值排序
int input(int choice);         		//选择输入数据文件0-9 
void output_result();               //将结果输出并写入文件
void scatter_diagram();             //绘制散点图 
void Backtracking(int i);      		//回溯法解决KP问题 
//******************主函数********************************* 
int main()
{
	int choice; 
	printf(" *******0/1背包问题********\n\n");
	printf("        1.动态规划法       \n");
	printf("        2.贪心算法         \n");
	printf("        3.回溯算法         \n");
	printf("        4.非递增排序       \n");
	printf("        5.绘制散点图       \n");
	printf("        6.正确读入数据     \n");
	printf("        7.结束测试         \n\n"); 
	printf(" **************************\n");
	cout<<"请选择算法(或结束测试)："; 
	cin>>choice;
	while(choice!=7)
	{
		switch (choice)
		{
			case 1:
				//选择数据0-9 
			    input(choice);
				break;
			case 2:
			    input(choice);
				break;
			case 3:
			    input(choice);
				break;
			case 4:
			    input(choice);
				break;
			case 5:
			 	input(choice);
				break;
			case 6:
			 	input(choice);
				break;
			default:
			    printf("输错了！请重新输入！\n");
				break;	
	    }
	    printf(" *******0/1背包问题********\n\n");
		printf("        1.动态规划法       \n");
		printf("        2.贪心算法         \n");
		printf("        3.回溯算法         \n");
		printf("        4.非递增排序       \n");
		printf("        5.绘制散点图       \n");
		printf("        6.正确读入数据     \n");
		printf("        7.结束测试         \n\n"); 
		printf(" **************************\n");
	    cout<<"请选择算法(或结束测试)："; 
	    cin>>choice;
	}
	return 0;
} 
//0.选择输入数据文件0-9 
int input(int choice)
{
	vector<int> v;
	int choice2;

	printf("---------选择测试数据0-9----------\n\n");
	printf("          0. 测试数据0            \n");
	printf("          1. 测试数据1            \n");
	printf("          2. 测试数据2            \n");
	printf("          3. 测试数据3            \n");
	printf("          4. 测试数据4            \n");
	printf("          5. 测试数据5            \n");
	printf("          6. 测试数据6            \n");
	printf("          7. 测试数据7            \n");
	printf("          8. 测试数据8            \n");
	printf("          9. 测试数据9            \n");
	printf("          10.返回上级列表         \n\n");
	printf("----------------------------------\n");
	cout<<"请选择测试数据(或返回上级)：";
	cin>>choice2; 
	while(choice2!=10)
	{
		//每次都清空二维数组，以避免影响下次数据的测试 
    	memset(&w_v[0][0],0,sizeof(w_v));
    	//文件第一行数据为重量限制以及背包数，需单独拿出，用count来区分 
		switch (choice2)
		{
			//打开文件 //执行算法 
			case 0: ifs.open("beibao0.in",ios::in); s="beibao0.in"; get_data(); break;
			case 1: ifs.open("beibao1.in",ios::in); s="beibao1.in"; get_data(); break;
			case 2: ifs.open("beibao2.in",ios::in); s="beibao2.in"; get_data(); break;
			case 3: ifs.open("beibao3.in",ios::in); s="beibao3.in"; get_data(); break;
			case 4: ifs.open("beibao4.in",ios::in); s="beibao4.in"; get_data(); break;
			case 5: ifs.open("beibao5.in",ios::in); s="beibao5.in"; get_data(); break;
			case 6: ifs.open("beibao6.in",ios::in); s="beibao6.in"; get_data(); break;
			case 7: ifs.open("beibao7.in",ios::in); s="beibao7.in"; get_data(); break;
			case 8: ifs.open("beibao8.in",ios::in); s="beibao8.in"; get_data(); break;
			case 9: ifs.open("beibao9.in",ios::in); s="beibao9.in"; get_data(); break;
			default: cout<<"输入错误，请重新输入！"<<endl; break;	
	    }
		QueryPerformanceFrequency(&f);
    	dqFreq=(double)f.QuadPart;
    	QueryPerformanceCounter(&time_start);
    	if(choice==1)
    		DP();
		else if(choice==2)
			Greedy();
		else if(choice==3)
		{
			cw=0,cp=0;
			max_value=0; 
			for(int i=0;i<N;i++)
			{
				left_value+=w_v[i][1];	
			} 
			Backtracking(0);
			for(int i=0;i<N;i++)
			{
				vector_quantity[i]=best_results[i];
			}
			ofs.open("Backtracking.txt",ios::out|ios::app); 
    		output_result();
		}else if(choice==4)
			sort(choice);
		else if(choice==6)
	        break;
		else if(choice==5){
			scatter_diagram(); 	
		}		    
		QueryPerformanceCounter(&time_over);
		cout<<"运行时间:"<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)<<"s\n";
		if(choice==1)
			cout<<"结果已写入DP.txt文件中！\n";    
		else if(choice==2)
			cout<<"结果已写入Greedy.txt文件中！\n"; 
		else if(choice==3)
		 	cout<<"结果已写入backtracking.txt文件中！\n";	
		ofs<<"Time:"<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)<<"s\n";
		ofs.close();
		system("pause");
		cout<<"\n请选择测试数据（或返回上级）：";
		cin>>choice2; 
	}
	cout<<endl;
	return 0;
} 
//已知WMAX、N、w_v[N][2]，要的结果是最大能装的重量！ 
//1.动态规划解决KP问题 
int DP()
{ 
	max_value=KnapSack();
	ofs.open("DP.txt",ios::out|ios::app); 
	output_result();
	return 0;
}
//2.构建动态规划表 
int KnapSack()
{
	int i=0,j=0;
	int a=0,b=0;
	for(i=0;i<=N;i++)
	{
		T[i][0]=0;
	}
	for(j=0;j<=WMAX;j++)
	{
		T[0][j]=0;
	}
	for(i=1;i<=N;i++)
	{   //计算第i行，进行第i次迭代 
		for(j=1;j<=WMAX;j++)
		{
			//绘制表 
			T[i][j]=T[i-1][j];
			if(j>=w_v[i-1][0] && T[i][j]<w_v[i-1][1]+T[i-1][j-w_v[i-1][0]]) 
		        T[i][j]=w_v[i-1][1]+T[i-1][j-w_v[i-1][0]];
		} 
	}
	for(j=WMAX,i=N;i>=1;i--)
	{   //求装入背包的物品 
		if(T[i][j]>T[i-1][j])
		{
			vector_quantity[i]=1;  //若当前价值大于上一行价值，说明当前物品被装入背包中 
			j=j-w_v[i][0];
		}
	}
	//得到背包取得的最大价值 
	return T[N][WMAX];  
}
//3.贪心算法解决KP问题（得到的结果是近似解，并非最优解！！！） 
int Greedy()
{
	int choice3=0;
	//直接使用排好序的下标进行贪心选择
	//计算最大重量，以及解向量 
	int k=0,g=0;
	//重新归0，方便下次使用 
	max_value=0;
	sort(choice3);
	for(int i=0;i<N;i++)
	{
		g=decrease[k];
		if(w_v[g][0]<=WMAX && WMAX>0)
		{
			max_value+=w_v[g][1];  //价值增加 
			WMAX-=w_v[g][0];       //重量减少 
			vector_quantity[g]=1; 
		}
		k++;	
	}
	//将结果写入文件 
	ofs.open("Greedy.txt",ios::out|ios::app); 
	output_result();
	return 0;
}
//4.回溯法
void Backtracking(int i)
{
    if(i>=N) //递归结束的判定条件
    {   
	    if(cp>max_value)
		{
    	    max_value = cp;                                                 
    	    for(int i=0;i<N;i++)
			{
    	    	best_results[i]=vector_quantity[i];
			}
	    }
        return;
    }
    left_value-=w_v[i][1];
    //如若左子节点可行，则直接搜索左子树;
    //对于右子树，先计算上界函数，以判断是否将其减去
    if(cw+w_v[i][0]<=WMAX )//将物品i放入背包,搜索左子树
    {
        cw+=w_v[i][0];       //同步更新当前背包的重量
        cp+=w_v[i][1];       //同步更新当前背包的总价值
        vector_quantity[i]=1;
        Backtracking(i+1);   //深度搜索进入下一层
        cw-=w_v[i][0];       //回溯复原
        cp-=w_v[i][1];       //回溯复原
    }
    if(cp+left_value>max_value)//如若符合条件则搜索右子树
    	Backtracking(i+1);
    left_value+=w_v[i][1];
}
//5.按单位重量价值排序（递减排序） 
int sort(int choice)
{
    int index;                  //下标 
    int k=0,g=0; 
	for(int i=0;i<N;i++)
	{
		decrease[i]=i;
		vector_quantity[i]=0; 
	}
	//冒泡排序
	for(int i=0;i<N-1;i++)
	{
		for(int j=0;j<N-1-i;j++)
		{
			if(vw[j]<vw[j+1])
			{
				index=vw[j];
				vw[j]=vw[j+1];
				vw[j+1]=index;
				index=decrease[j];
				decrease[j]=decrease[j+1];  //存入下标，用来递减排序 
				decrease[j+1]=index;        //输出时循环输出，下标用的decrease中的 
			}	
		}
	}
	if(choice==4)
	{
		cout<<"下标排序"<<endl;
		for(int m=0;m<N;m++)
		{
			cout<<decrease[m]+1<<" ";
		}
		cout<<endl<<"按单位重量价值递减排序："<<endl;
		for(int i=0;i<N;i++)
		{
			g=decrease[k];
			cout<<"背包"<<g+1<<"  ";
			cout<<w_v[g][0]<<"  "<<w_v[g][1]<<"  ";
	    	printf("%.2f\n",w_v[g][1]/float(w_v[g][0]));	
			k++;	
		}
	} 
	return 0;	
} 
//6.读文件，取得测试数据 
void get_data()
{
	int count=0;
	int t1;
	int *p=&w_v[0][0];
	if(!ifs.is_open())
	{
		cout<<"文件打开失败！"<<endl;
		return;
	}
	//存入数组
	while(ifs>>t1)
	{   //遇到空白符结束 
		count++;
		if(count==1)
		{
		    WMAX=t1;  //最大限重 
			cout<<"重量限制："<<WMAX<<"--->"; 
		}else if(count==2)
		{
			N=t1;     //背包总数
			cout<<"背包总数："<<N<<endl;  
		}else
		{
			*p=t1;
			p++;	
		}		
	}
	ifs.close();
	output();
}
//7.输出测试数据
int output(){
	for(int i=0;i<N;i++)
	{
		vw[i]=0;
	}
	cout<<"---------------------------"<<endl;
	cout<<"      重量"<<" "<<"价值"<<" "<<"价值/重量"<<endl; 
	for(int i=0;i<N;i++)
	{
		cout<<"背包"<<i+1<<" "; 
		for(int j=0;j<2;j++)
		{
			cout<<" "<<w_v[i][j]<<"  ";
		}
		printf("%.2f",w_v[i][1]/float(w_v[i][0]));
		vw[i]=w_v[i][1]/float(w_v[i][0]); 
		cout<<endl;
	}
	cout<<"---------------------------"<<endl;
	return 0;
}
//8.将结果输出并写入文件
void output_result()
{
	ofs<<s<<"      ";
	ofs<<"Max_value:"<<max_value<<"      ";
	cout<<"\n该算法计算得的最大价值为："<<max_value<<endl;
	ofs<<"solution_vector:{";
	cout<<"解向量为：{";
	for(int i=0;i<N;i++)
	{
		if(i==N-1)
		{
			ofs<<vector_quantity[i];
		    cout<<vector_quantity[i];
		}else
		{
			ofs<<vector_quantity[i]<<",";
		    cout<<vector_quantity[i]<<",";
		}
	}
	cout<<"}"<<endl;
	ofs<<"}"<<"      ";
} 
//9.绘制散点图 
void scatter_diagram()
{
	cout<<"本项目由于C++不方便使用，便单独用python实现了散点图功能\n";
	cout<<"结果在同路径下的picture文件夹里！(此部分功能仍需拓展)\n";
} 
 





 
