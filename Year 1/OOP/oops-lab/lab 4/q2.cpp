
void allocateMemory(int *&arr,int length);
void deallocateMemory(int *arr);
int find(int* arr, int length, int target);

int find(int *arr, int length, int target){
    if(*arr==target){
        return ;
    }
    find(arr+1,length,target);
}
void allocateMemory(int *&arr,int length){
    arr = new int[length];
}
void deallocateMemory(int *arr) {
    delete[] arr;
}