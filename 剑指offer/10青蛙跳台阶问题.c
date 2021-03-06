int numWays(int n)
{
    if(n == 0 || n == 1)
    {
        return 1;
    }
    int num1 = 1;
    int num2 = 1;
    int sum = 0;
    for(int i = 1; i < n; ++i)
    {
        sum = (num1 + num2) % 1000000007;
        num1 = num2;
        num2 = sum;
    }
    return num2;
}