//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2

//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;


int main(){
bool conditionStillExists=0;
bool newlyInstalledServer=0;
bool answer=0;


cout<<"Starting General diagnosis "<<endl;
cout<<"Recording symptom information."<<endl;
cout<<"Rebooting server to see if condition still exists."<<endl;
cout<<"Is this a newly installed server?If so enter 1, if not enter 0"<<endl;
if(newlyInstalledServer == 1){
cout<<"Reseating any components that may have come loose during shipping and reboot the server."<<endl;
cout<<"Does condition still exist?If so enter 1, if not enter 0"<<endl;
cin>>conditionStillExists;
  if(conditionStillExists== 1)
    goto Line25;
    else {
    cout<<" Recording action taken"<<endl;
            return 0;
          }
}
else{
 Line25:  
cout<<"Were options added or was the configuration changed recently? If so enter 1, if not enter 0"<<endl;
cin>>answer;
    if(answer == 1){
        cout<<"Isolating what has changed. Verifying it was installed correctly. Restoring server to last known working state or original shipped configuration."<<endl;
        cout<<"Does condition still exist? If so enter 1, if not enter 0"<<endl;
        cin>>conditionStillExists;
        if(conditionStillExists){
            label2:
            cout<<"Isolating and minimizing the memory configuration"<<endl;
            cout<<"Does condition still exist? If so enter 1, if not enter 0"<<endl;
            cin>>conditionStillExists;
            if(conditionStillExists){
                cout<<"Breaking server down to minimal configuration"<<endl;
                 cout<<"Does condition still exist? If so enter 1, if not enter 0"<<endl;
                    if(conditionStillExists){
                        cout<<"Please Troubleshoot or replace basic server spare parts."<<endl;
                        cout<<"Does condition still exist?If so enter 1, if not enter 0"<<endl;
                        cin>>conditionStillExists;
                        if(conditionStillExists == 1){
                            goto label;
                        }
                        else{
                            cout<<"Recording symptom & error information on repair tag if sending back a failed part."<<endl;
                            return 0;
                        }
                    }
                    else{
                        cout<<"Adding one part at a time back to configuration to isolate faulty component"<<endl;
                        cout<<"Does condition still exist?If so enter 1, if not enter 0"<<endl;
                        cin>>conditionStillExists;
                          if(conditionStillExists == 1){
                          label:
                            cout<<"Ensuring the following information is available: • Survey configuration snapshots. OS event log file . Full crash dump"<<endl;
                            cout<<"Call HP Service Provider"<<endl;}
                           else{
                            cout<<" Recording action taken"<<endl;
                            return 0;}
                         }
                    }}
                    
         else{
              cout<<" Recording action taken"<<endl;
              return 0;}
              }
      else{
      cout<<"Check for Service Notifications"<<endl;
      cout<<"Download the latest software and firmware from HP website"<<endl;
      cout<<"Does condition still exist? If so enter 1, if not enter 0"<<endl;
            cin>>conditionStillExists;
            if(conditionStillExists){
              goto label2;}
            else{
             cout<<" Recording action taken"<<endl;
             return 0;}}}
            
return 0;
}
            
        
