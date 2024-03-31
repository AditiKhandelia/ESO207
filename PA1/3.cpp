#include<iostream>
using namespace std;

int k;
//function to calculate 2 raised to a certain power
long long power2(int n)
{
    if(n==0) return 1;
    else return 2*power2(n-1);
}
//function to multiply two square matrices of the same size
long long** matrix_multiply(long long** arr)
{
    long long** arr1=new long long*[k];
    for(int i=0;i<k;i++) arr1[i]=new long long[k];
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++)
        {
            arr1[i][j]=0;
            for(int p=0;p<k;p++)
            {
                arr1[i][j]+=(arr[i][p]*arr[p][j]);
                arr1[i][j]=(arr1[i][j])%998244353;
            }
        }
    }
    return arr1;
}
//function to multiply a square matrix and a column matrix
long long** matrix_multiply1(long long** final,long long** initial)
{
    long long** ans=new long long*[k];
    for(int i=0;i<k;i++) ans[i]=new long long;
    for(int i=0;i<k;i++)
    {
        ans[i][0]=0;
        for(int j=0;j<k;j++)
        {
            ans[i][0]+=((final[i][j]*initial[j][0]));
            ans[i][0]=(ans[i][0])%998244353;
        }
    }
    return ans;
}
//function to multiply to matrices of the same size
long long** matrix_multiply2(long long** final,long long** arr)
{
    long long** arr1=new long long*[k];
    for(int i=0;i<k;i++) arr1[i]=new long long[k];
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++)
        {
            arr1[i][j]=0;
            for(int p=0;p<k;p++)
            {
                arr1[i][j]+=((final[i][p]*arr[p][j]));
                arr1[i][j]=(arr1[i][j])%998244353;
            }
        }
    }
    return arr1;
}
//function to calculate the matrix raised to a certain  power
long long** power(long long**arr,long long num)
{
    if(num==1) return arr;
    else
    {
        long long** final=new long long*[k];
        for(int i=0;i<k;i++) final[i]=new long long[k];
        final=matrix_multiply(power(arr,num/2));
        if(num%2==1) final=matrix_multiply2(final,arr);
        return final;
    }
}

long long calculate(long long num)
{
    long long** arr=new long long*[k];
    for(int i=0;i<k;i++)
    {
        arr[i]=new long long[k];
        for(int j=0;j<k;j++)
        {
            if(i==0) arr[i][j]=1;
            else if(i-j==1) arr[i][j]=1;
            else arr[i][j]=0;
        }
    }
    long long** initial=new long long*[k];
    for(int i=0;i<k;i++)
    {
        initial[i]=new long long[k];
        initial[i][0]=power2(k-i-1);
    }
    
    long long** final=new long long*[k];
    for(int i=0;i<k;i++) final[i]=new long long[k];
    final=power(arr,num-k);
    initial=matrix_multiply1(final,initial);
    return initial[0][0];
}
int main()
{
    //number of test cases
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        //num stores the sum and k the max number on the dice's face
        long long num;
        cin>>num;
        cin>>k;
        if(num>k) cout<<calculate(num)<<endl;
        else if(num>=1) cout<<power2(num-1)<<endl;
        else cout<<"0"<<endl;
    }
}