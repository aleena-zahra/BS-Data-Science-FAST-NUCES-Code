
bool isPrimeNum(int x, int i){
    if (i == 1)
    {
        return true;
    }
    else
    {
       if (x % i == 0)
       {
         return false;
       }
       else
       {
         return isPrimeNum(x, i - 1);
       }       
    }
}
