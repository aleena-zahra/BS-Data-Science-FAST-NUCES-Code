
int sumArr(int* arr, int length,int index){
    if(index<length){
        return arr[index]+sumArr(arr,length ,index+1);
    }
    else return 0;
}