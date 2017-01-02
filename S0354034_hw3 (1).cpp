#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#define clockwise 1
#define counterclockwise 2
#define coliner 3
#define PI 3.14159625
	int sort_angle;
	using namespace std;
	struct POINT
	{
		double x,y,angle;
		int no;
	};
	POINT nextTOP(stack<POINT> &Stack)
	{
	    POINT p = Stack.top();
	    Stack.pop();
	    POINT res = Stack.top();
	    Stack.push(p);
	    return res;
	}
	void swap(double *a, double *b,double *c,double *d,int*e,int*f)
    {                                            
        double temp;                                     
        int temp_no ;                            
	     temp=*a;   	                                
	     *a=*b;                                   
	     *b=temp;     
		 
		 temp=*c;
		 *c=*d;
		 *d=temp; 
		 
		 temp_no=*e;
		 *e=*f;
		 *f=temp_no;  
		                                 
    } 
    void swapangle(double *a, double *b,double *c,double *d,int*e,int*f,double*g,double*h)
    {                                            
        double temp;                                     
        int temp_no ;                            
	     temp=*a;   	                                
	     *a=*b;                                   
	     *b=temp;     
		 
		 temp=*c;
		 *c=*d;
		 *d=temp; 
		 
		 temp_no=*e;
		 *e=*f;
		 *f=temp_no;
		 
		 temp =*g;
		 *g=*h;
		 *h=temp;  
		                                 
    } 
	void sort(POINT point[],int left,int right)  
   {  
      double pivod;
	  int i,j;
      
      if(left>right)
        return;
	  pivod=point[left].x;   
      i=left+1;
      j=right;
      
        while(1)
        {  
      	  while(i<=right)           
          { 
		  	if(point[i].x>pivod)                                                    
        		{ break; }                          
          	i++;                                      
          }   
		  while(j>left)    
          {  
		  	if(point[j].x<pivod)                  
               { break; }                    
            j--;                             
          } 
           
         if(i>j)
         { break; }     
         swap(&point[i].x,&point[j].x,&point[i].y,&point[j].y,&point[i].no,&point[j].no); 
         
       }
       swap(&point[left].x,&point[j].x,&point[left].y,&point[j].y,&point[left].no,&point[j].no);
       sort(point,left,j-1);  
       sort(point,j+1,right);
     }
    void sortangle(POINT point[],int left,int right)  
   {  
      double pivod;
	  int i,j;
      
      if(left>right)
        return;
	  pivod=point[left].angle;   
      i=left+1;
      j=right;
      
        while(1)
        {  
      	  while(i<=right)           
          { 
		  	if(point[i].angle>pivod)                                                    
        		{ break; }                          
          	i++;                                      
          }   
		  while(j>left)    
          {  
		  	if(point[j].angle<pivod)                  
               { break; }                    
            j--;                             
          } 
           
         if(i>j)
         { break; }     
         swapangle(&point[i].x,&point[j].x,&point[i].y,&point[j].y,&point[i].no,&point[j].no,&point[i].angle,&point[j].angle); 
         
       }
       swapangle(&point[left].x,&point[j].x,&point[left].y,&point[j].y,&point[left].no,&point[j].no,&point[left].angle,&point[j].angle);
       sortangle(point,left,j-1);
       sortangle(point,j+1,right);
     }
	int orientation(POINT p, POINT q, POINT r)
    {
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
   }
	void Convexhull(int left,int right,POINT point[],int count)
	{
		int test;
		//printf("%d %d\n",left,right);
		if(left == 0&&right == count/2)
		{	
			test = 1;
			printf("最後一次合併前的左邊凸多邊型:\n");
		}
		else if(left == (count/2+1)&&right == count)
		{
			test = 1;
			printf("最後一次合併前的右邊凸多邊型:\n");
		}
		else if(left == 0 && right == count)
		{
			test = 1;
			printf("最後的凸多邊型:\n");
		}
			
		for(int k=left+1;k<=right;k++)//最左邊x相同 找y最小 O(n)
		{
			if(point[k].x == point[left].x&&point[k].y < point[left].y)
			{
				POINT temp;
				temp = point[k];
				point[k] = point[left];
				point[left] = temp;
			}	
		}
		for(int k=left+1;k<=right;k++)//找出每個點跟第一個點的夾角 O(n)
		{
			double tan = (point[k].y - point[left].y)/(point[k].x - point[left].x);
			point[k].angle = atan(tan)*180/PI;
		}
	
		 sortangle(point,left+1,right);//排角度 O(nlogn)
		 POINT p[count];
		 int t = 0;
		 for(int k=left+1;k<=right;k++)
			 	if(point[k].x == point[left].x)
			 		p[t++] = point[k];
		/* if(test == 1)
		 	for(int k=left;k<=right;k++)
		 		printf("(%lf,%lf)\n",point[k].x,point[k].y);*/
		 stack<POINT> Stack;//利用stack實現granham scan 
		 if(right-left+1 < 3&&test == 1)//不到三個點直接輸出 
		 {	
		 	printf("總共頂點數: %d\n",right-left+1);
		 	for(int k=left;k<=right;k++)
		 		printf("編號 %d:(%lf,%lf)\n",point[k].no,point[k].x,point[k].y); 
		 }
		 else//超過三個點 做granham scan 
		 {
		 	 Stack.push(point[left]);//把一開始的三個點加入stack 
	   		 Stack.push(point[left+1]);
	         Stack.push(point[left+2]);
	         for (int k = left+3; k <= right; k++)//O(n)
			 {  
			      while (orientation(nextTOP(Stack), Stack.top(), point[k]) == 1)//檢查是否有順時針 
			         Stack.pop();//如果有就pop掉 
			      Stack.push(point[k]);//如果沒有就push下一個點 
			 }
			/**************印點****************/ 
	   		 int point_num=0;
	   		 int index = 0;
	   		 POINT temp[count]; 
			 while (!Stack.empty() && test==1)//最後stack一一pop出來 
			 {
			       temp[index] = Stack.top();      
			       Stack.pop();
			       index++;
			       point_num++;  
			 }
			// printf("%d\n",point_num);
			 if(test == 1)
			 {	
			 	printf("總共頂點數: %d\n",point_num);
			 	for(int k=index-1;k>=0;k--)
			 		printf("編號 %d:(%lf,%lf)\n",temp[k].no,temp[k].x,temp[k].y);
				
			 }
			 
			 test = 0;
		 }
		// for(int k=0;k<t;k++)
		//	printf("編號 %d:(%lf,%lf)\n",p[k].no,p[k].x,p[k].y);
	//	t=0; 
		/*********************************************/
	}
	void median_line(int left,int right,POINT point[],int count)
	{	
		int midline;
		if(right - left < 1)
			return;
		midline = (right+left)/2;
		median_line(left,midline,point,count);//繼續切左邊 
		median_line(midline+1,right,point,count);//繼續切右邊 
		Convexhull(left,right,point,count);//找凸邊形 
	}
	int main(){
	  FILE *datain;
	  char space;
	  char str[50];
	  int no[2000];
	  int count = 0;
	  int t; 
	  
	  datain = fopen("test1.txt","r");
	  if(!datain){ 
	  	printf("檔案開啟失敗");
	  	exit(1);
	  } 
	  while(fgets(str,50,datain))//算有幾筆資料 
	  {
	  	count++;
	  }
	  fclose(datain);
	  POINT point[count];
	  datain = fopen("test1.txt","r");//讀資料進來 
	  for(int k=0;k<count;k++)
	  {
	  	fscanf(datain,"%lf",&point[k].x);
		fscanf(datain,"%*c",&space);
		fscanf(datain,"%lf",&point[k].y);
		point[k].no = k+1;
	  }
	  fclose(datain);
	  sort_angle = 0;
	  sort(point,0,count-1);//quick sort
	  //for(int k=0;k<count;k++)//印排序後資料 
	  //	printf("%d (%lf,%lf)\n",point[k].no,point[k].x,point[k].y);
	  median_line(0,count-1,point,count-1);//找中位數 
	  
	  system("pause");
	  return 0;
	}
