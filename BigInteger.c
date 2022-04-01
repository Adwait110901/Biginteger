// Name: Adwait Deshpande
// Enrolment No.: BT19CSE003
// CPL Assignment No 2
#include<stdio.h>
#include<string.h>
typedef struct bigint_tag
{
	char number[309];
	int sign;
}bigint;
bigint Add(bigint ,bigint );
bigint Sub(bigint ,bigint );
bigint Multiply(bigint ,bigint );
bigint Str_rev(bigint );
bigint Str_rev(bigint str)
{
    int i,j;
	char temp;
	i = 0;
   	j = strlen(str.number) - 1;
    	while (i < j) 
    	{
      		temp = str.number[i];
      		str.number[i] = str.number[j];
      		str.number[j] = temp;
      		i++;
			j--;
   		}
	str.number[strlen(str.number)]='\0';
	return str;
}
bigint Add(bigint a,bigint b) 
{
	bigint sum;
	if((a.sign==1 && b.sign==1) || (a.sign==0 && b.sign==0)) // both +ve or both -ve nos.
	{
		//Addition Logic
		sum.sign=a.sign;
		int len_a=strlen(a.number),len_b=strlen(b.number),carry=0,sum_loop,i;
		for(i=0;((i<len_a)&&(i<len_b));i++)
		{
			sum_loop=(a.number[len_a-i-1]-'0')+(b.number[len_b-i-1]-'0')+carry;
			carry=sum_loop/10;
			sum_loop=sum_loop%10;
			sum.number[i]='0'+sum_loop;
		}
		while(i<len_a)
		{
			if(carry==0)		
				sum.number[i]=a.number[len_a-i-1];
			else
			{
				sum_loop=(a.number[len_a-i-1]-'0')+carry;
				carry=sum_loop/10;
				sum_loop=sum_loop%10;
				sum.number[i]='0'+sum_loop;
			}
			i++;
		}
		while(i<len_b)
		{	
			if(carry==0)		
				sum.number[i]=b.number[len_b-i-1];
			else
			{
				sum_loop=(b.number[len_b-i-1]-'0')+carry;
				carry=sum_loop/10;
				sum_loop=sum_loop%10;
				sum.number[i]='0'+sum_loop;
			}
			i++;
		}
		if(carry!=0)
		{
			sum.number[i]='0'+carry;
			i++;
		}
		sum.number[i]='\0';
		sum=Str_rev(sum);
	}
	else // one +ve one -ve case
	{
		if(a.sign==1 && b.sign==0)
		{
			b.sign=1;
			sum=Sub(a,b);
		}
		else if(a.sign==0 && b.sign==1)
		{
			b.sign=0;
			sum=Sub(a,b);
		}
	}
	return sum;
}

bigint Sub(bigint num_1, bigint num_2)
{
	bigint diff;
	if((num_1.sign==1 && num_2.sign==1) || (num_1.sign==0 && num_2.sign==0)) // both +ve or both -ve nos.
	{
		int len_a=strlen(num_1.number),len_b=strlen(num_2.number),borrow=0,diffi,i,l,l3,r;
		bigint a,b;
		a=num_1;
		b=num_2;
		r=0;
		if(len_a==len_b)
		r=strcmp(a.number, b.number);
		if((len_a<len_b)||(r<0)) // if b>a swap the nos. and add a negative sign
		{
			a=num_2;
			b=num_1;
		}
		l=strlen(a.number);
		l3=strlen(b.number);
		for(i=0;(i<l3);i++)
		{
			diffi=(a.number[l-i-1]-'0')-(b.number[l3-i-1]-'0')+borrow;
			if(diffi<0)
			{
				diffi=10+diffi;
				borrow=-1;
			}
			else
				borrow=0;
			diff.number[i]='0'+diffi;
		}
		while(i<l)
		{
			if(borrow==-1)
			{
				diffi=(a.number[l-i-1]-'0')+borrow;
				borrow=0;		
			}
			else
				diffi=(a.number[l-i-1]-'0')+borrow;
			diff.number[i]='0'+diffi;	
			i++;
		}
		if(num_1.sign==1 && num_2.sign==1) // both num_1 and num_2 are positive
		{
			if(len_a<len_b||r<0) // second no. is bigger in modulus
			{
				diff.sign=0;
			}
			else // first no. is bigger in modulus
			{
				diff.sign=1;
			}
		}
		if(num_1.sign==0 && num_2.sign==0) // both num_1 and num_2 are negative
		{
			if(len_a<len_b||r<0) // second no. is bigger in modulus
			{
				diff.sign=1;
			}
			else // first no. is bigger in modulus
			{
				diff.sign=0;
			}
		}
		diff.number[i]='\0';
		diff=Str_rev(diff);
	}
	else // one positive, one negative
	{
		if(num_1.sign==1 && num_2.sign==0) // a positive b negative
		{
			num_2.sign=1;
			diff=Add(num_1,num_2);
			diff.sign=1;
		}
		else if(num_1.sign==0 && num_2.sign==1) // a negative, b positive
		{
			num_1.sign=1;
			diff=Add(num_1,num_2);
			diff.sign=0;
		}
	}
	return diff;

}
bigint Multiply(bigint a,bigint b)
{
	int i,j,len_a,len_b,product,t,carry;
	len_a=strlen(a.number);
	len_b=strlen(b.number);
	bigint temp,result;
	result.number[0]='\0';
	int flag=0;
	if(a.sign==b.sign) // if both the nos have same sign
	{
		result.sign=1;
	}
	else if(a.sign==0 && b.sign==1) // if a is negative and b is positive
	{
		a.sign=1;
		flag=1;
	}
	else if(a.sign==1 && b.sign==0) // if number 2 is positive and b is negative
	{
		b.sign=1;
		flag=2;
	}
	for(i=0;i<len_b;i++)
	{	
		carry=0;
		for(t=0;t<i;t++)
		{
			temp.number[t]='0';
		}
		for(j=0;j<len_a;j++)
		{
			product=(b.number[len_b-i-1]-'0')*(a.number[len_a-j-1]-'0')+carry;
			temp.number[j+t]='0'+product%10;
			carry=product/10;
		}
		if(carry!=0)
		{
			temp.number[j]='0'+carry;
			j++;
		}
		temp.number[j+t]='\0';
		temp=Str_rev(temp);
		result=Add(result,temp);
	}
	if(flag==0)
	{
		result.sign=1;
	}
	if(flag==1)
	{
		result.sign=0;
		a.sign=0;
	}
	if(flag==2)
	{
		result.sign=0;
		b.sign=0;
	}
	return result;


}
int main()
{
	int c=1;	
	bigint num_1,num_2,product,diff;
	bigint ans;
	printf("Enter the sign of first number (1 for + and 0 for -):\n");
	scanf("%d",&num_1.sign);
	printf("Enter first number:\n");
	scanf("%s",num_1.number);
	printf("Enter the sign of second number (1 for + and 0 for -):\n");
	scanf("%d",&num_2.sign);
	printf("Enter second number:\n");
	scanf("%s",num_2.number);
	while(c!=0)
	{
		printf("Enter the operation to be performed:\n");
		printf("1.Addition  2.Subtraction  3.Multiply  4.Exit\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				ans=Add(num_1,num_2);
				if(ans.sign==1)
				{
					printf("Sum is %s\n",ans.number);
				}
				else
				{
					printf("Sum is - %s\n",ans.number);
				}
				break;
				
			case 2:
				diff=Sub(num_1,num_2);
				if(diff.sign==1)
				{
					printf("Difference is %s\n",diff.number);
				}
				else
				{
					printf("Difference is - %s\n",diff.number);
				}
				break;

			case 3:
				product=Multiply(num_1,num_2);
				if(product.sign==1)
				{
					printf("Product is %s\n",product.number);
				}
				else
				{
					printf("Product is - %s\n",product.number);
				}
				break;
						
			case 4:
				c=0;
				break;
		}
	}
	return 0;
}
