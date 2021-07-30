#include<stdio.h>
void fcfs(int page[],int framesz[],int n,int frame)
{
	int i,j,pageft=0,s;
	for(i = 0; i< n; i++)
	{
		s=0;
		for(j = 0; j< frame; j++)
		{
			if(page[i]==framesz[j])
			{
				s++;
				pageft--;
			}
		}
		pageft++;
		if((pageft <= frame) && (s == 0))
        {
            framesz[i] = page[i];
        }   
        else if(s == 0)
        {
            framesz[(pageft - 1) % frame] = page[i];
        }
	}
	printf("\nTotal no of page faults(FCFS ALGORITHM):%d",pageft);
}
int findLRU(int time[], int n)
{
	int i, minimum = time[0], pos = 0;
	for(i = 1; i < n; ++i)
	{
		if(time[i] < minimum)
		{
			minimum = time[i];
			pos = i;
		}
	}
	return pos;
}
void lru(int page[],int framesz[],int n,int frame)
{
	int counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
	for(i = 0; i < frame; ++i)
	{
    	framesz[i] = -1;
    }
    for(i = 0; i < n; ++i)
	{
    	flag1 = flag2 = 0;
    	for(j = 0; j < frame; ++j)
		{
    		if(framesz[j] == page[i])
			{
			    counter++;
			    time[j] = counter;
			    flag1 = flag2 = 1;
			    break;
   			}
     	}
    	if(flag1 == 0)
		{
			for(j = 0; j < frame; ++j)
			{
     			if(framesz[j] == -1)
				{
				    counter++;
				    faults++;
				    framesz[j] = page[i];
				    time[j] = counter;
				    flag2 = 1;
			        break;
    			}
     		}
     	}
    	if(flag2 == 0)
		{
		    pos = findLRU(time, frame);
		    counter++;
		    faults++;
		    framesz[pos] = page[i];
		    time[pos] = counter;
     	}
	}
	printf("\n\nTotal Page Faults(LRU) = %d", faults);
}
void optimal(int page[],int framesz[],int n,int frame)
{
	int i,j,pageft=0,s,flag1,flag2,flag3,temp[frame],k, pos, max, miss = 0;
	for(i = 0; i < frame; ++i)
	{
       	framesz[i] = -1;
	}
    for(i = 0; i < n; ++i)
	{
        flag1 = flag2 = 0;
        for(j = 0; j < frame; ++j)
		{
            if(framesz[j] == page[i])
			{
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0)
		{
            for(j = 0; j < frame; ++j)
			{
                if(framesz[j] == -1)
				{
                    pageft++;
                    framesz[j] = page[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        if(flag2 == 0)
		{
        	flag3 =0;
            for(j = 0; j < frame; ++j)
			{
           		temp[j] = -1;
            	for(k = i + 1; k < n; ++k)
				{
		            if(framesz[j] == page[k])
					{
			            temp[j] = k;
			            break;
            		}
             	}
            }
            for(j = 0; j < frame; ++j)
			{
            	if(temp[j] == -1)
				{
		            pos = j;
		            flag3 = 1;
		            break;
             	}
            }
            if(flag3 ==0)
			{
           		max = temp[0];
            	pos = 0;
            	for(j = 1; j < frame; ++j)
				{
            		if(temp[j] > max)
					{
	             		max = temp[j];
	            		pos = j;
             		}
             	}            
            }
			framesz[pos] = page[i];
			pageft++;
    	}
    }
    printf("\n\nTotal Page Faults(OPTIMAL) = %d", pageft);
    
}
void main()
{
	int n,frame,i;
	printf("Enter the total no of pages:");
	scanf("%d",&n);
	printf("Enter the no of frames:");
	scanf("%d",&frame);
	int page[n],framesz[frame];
	for(i = 0; i< n; i++)
    {
        printf("Reference String value [%d]:", i + 1);
	    scanf("%d", &page[i]);
    }
    fcfs(page,framesz,n,frame);
    optimal(page,framesz,n,frame);
 	lru(page,framesz,n,frame);   
}

