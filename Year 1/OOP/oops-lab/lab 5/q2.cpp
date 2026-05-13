
int findTarget(int* arr, int length, int target){
    if(length==0 && arr[length]!=target){
        return -1;
    }
    else if(arr[length]==target){
        return length;
    }
    else{
        findTarget(arr,length-1,target);
    }
}
// int main(){
//     int length=3;
//     int arr[length]={1,2,3};
//     cout<<findTarget(arr,length-1,1);
// }