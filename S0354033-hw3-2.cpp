// A C++ program to find convex hull of a set of points. Refer
// http://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
// this for collinear!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;
int num;
 
struct Point
{
    double x, y;
    int no;
};
 
// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;
 
// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}
 
// A utility function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
 
// A utility function to return square of distance
// between p1 and p2
double distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}
 
// Prints convex hull of a set of n points.
void convexHull(Point points[], int *no, int n, int l, int r)
{
   // Find the bottommost point
   double xmin = points[0].x;
   int min = 0;
   for (int i = 1; i < n; i++)
   {
     double x = points[i].x;
 
     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((x < xmin) || (xmin == x &&
         points[i].y < points[min].y))
        xmin = points[i].x, min = i;
   }
 
   // Place the bottom-most point at first position
   swap(points[0], points[min]);
 
   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);
 
   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       
 
 
       points[m] = points[i];       
       m++;  // Update size of modified array
   }
 
   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (m < 3) return;
 
   // Create an empty stack and push first three points
   // to it.
   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
 
   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (orientation(nextToTop(S), S.top(), points[i]) == 1 )
         S.pop();
      S.push(points[i]);
   }
 
   // Now stack has the output points, print contents of stack
   int ok=0;
   if(l == 0 && r == num-1){
     ok=1;
     printf("最後的convex hull:\n");
   }
   else if(l == 0&&r == (num-1)/2){
     ok=1;
     printf("最後一次合併前left convex hull:\n");
   }
   else if(l == ((num-1)/2+1)&&r == num-1){
     ok=1;
     printf("最後一次合併前right convex hull:\n");
   }
   double strr[2000][3];
   int cc=0;
   while (!S.empty() && ok==1 )
   {
       Point p = S.top();
       strr[cc][0] = p.no;
       strr[cc][1] = p.x;
       strr[cc][2] = p.y;       
       S.pop();
       cc++;
   }
   if(ok==1){
   
   cout << "頂點數:" << cc << endl; 
   for(int e=cc-1;e>=0;e--){
     cout << "NO." << strr[e][0] << "(" << strr[e][1] << ", " << strr[e][2] <<")" << endl;
   }
   int ccc=0;
   double temp[100][3];
   for(int e=0;e<n;e++){
   	 if(points[e].x == points[0].x){
   	   temp[ccc][0] = points[e].no;
   	   temp[ccc][1] = points[e].x;
   	   temp[ccc][2] = points[e].y;
       ccc++;
     }
   }
   for(int e=1;e<ccc-1;e++){
   	 cout << "NO." << temp[e][0] << "(" << temp[e][1] << ", " << temp[e][2] <<")" << endl;     
   }
   }
   ok=0;
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
	void quickSort(double *a,double *b,int *no,int left,int right)  
   {  
      double pivod;
	  int i,j;
      
      if(left>right)
        return;
      pivod=a[left];   
      
      i=left+1;
      j=right;
      
      while(1)
        {  
          while(i<=right)           
            { if(a[i]>pivod)                                                    
              { break; }                          
              i++;                                      
            }      
          while(j>left)    
            {  if(a[j]<pivod)                  
               { break; }                    
               j--;                             
            }      
         if(i>j)
         { break; }     
         swap(&a[i],&a[j],&b[i],&b[j],&no[i],&no[j]); 
         
       }
       swap(&a[left],&a[j],&b[left],&b[j],&no[left],&no[j]);
       quickSort(a,b,no,left,j-1);  
       quickSort(a,b,no,j+1,right);
     }

void DC(double *a,double *b,int *no,int l, int r){
    if(l >= r)    return ;
    // System.out.println("l+r/2 = " + (l+r)/2);
    int m = (l+r)/2;
    DC(a,b,no,l, m);
    DC(a,b,no,m+1, r);
    int n = r-l+1;
    Point points[n];
    for(int i=0;i<n;i++){
      points[i].x = a[l+i];
      points[i].y = b[l+i];
      points[i].no = no[l+i];
    }
    convexHull(points,no,n,l,r);
}

// Driver program to test above functions
int main()
{
    FILE *datain;
	  double data_x[2000];
	  double data_y[2000];	  
	  int no[2000];
	  float avg; 
	  int sum = 0; 
	  int count = 0;	  
	  int t;
	  int k=0;
	  datain = fopen("test1.txt","r");
	  if(!datain){ 
	  	printf("檔案開啟失敗");
	  	exit(1);
	  } 
	  while(fscanf(datain,"%lf %lf",&data_x[k],&data_y[k])!=EOF)//算有幾筆資料 
	  {        
	  	count++;
	  	no[k] = k+1;
	  	k++;
	  }
	  fclose(datain);
	  //printf("%d\n",count);
	  num = count;
/*	  for(int i=0;i<count;i++)
        printf("%lf %lf\n",data_x[i],data_y[i]);*/
    quickSort(data_x,data_y,no,0,count-1);//quick sort
  /*  for(int i=0;i<count;i++)
      printf("%lf %lf\n",data_x[i],data_y[i]);*/
      
    DC(data_x,data_y,no,0,count-1);
    
    /*Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);*/
    system("pause");
    return 0;
}
