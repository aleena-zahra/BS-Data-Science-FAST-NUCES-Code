//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2

#include<iostream>
#include<iomanip>
using namespace std;


int main(){
string ConnectionDate= "28 Dec 11";
float EDRate= 0;
string BillMonth= "Oct 21";                                                            ;
string ReadingDate= "02-Nov-21";
string IssueDate= "03-Nov-21";
string DueDate= "17-Nov-21";
int ConsumerID= 0;
cout<<"Input your birthday in day/month/year order.Suppose your date of birth is 20-07-2003 then input 20072003"<<endl;
cin>>ConsumerID;
string Tarrif= "A-1a(01)";
short int Load= 2;
short int OldACNumber= 0;
string Division = "Westridge";
string SubDivision= "Tarnol pesh RD";
string FeederName= "Nust Road";
string ReferenceNo= "23i2514"; ///////////////////////////////////////////////
string Name;
cout<<"What is your Name? "<<endl;
cin>>Name;
string Address;
cout<<"What is your address? "<<endl;
cin>>Address;
int MeterNo= 123456;
int Previous= 9742;
int Present= 9942;
short int MF= 1;
int UnitsConsumed = 2514;
int CostPerUnit = 20;
int Costofelectricity= UnitsConsumed*CostPerUnit;
int FuelPriceAdjustment= 700;
int FCSurcharge= 90;
int QTRTarrif= -14;
int Total1=0;
Total1 = Costofelectricity + FuelPriceAdjustment +FCSurcharge +QTRTarrif;
int TvFee= 35;
int GST= 800;
int GSTonFPA= 108;
int Total2=0;
Total2 = TvFee + GST + GSTonFPA;
int CurrentBill= Total1 + Total2;
int TotalFPA= 700;
int Payablewithinduedate= TotalFPA + CurrentBill;
int LPSurcharge= 400;
int Payableafterduedate= LPSurcharge + Payablewithinduedate;
int BillNo=203732;


cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "|                                                                                                                        |"<< endl;
cout << "|                                                    ELECTRICITY BILL                                                    |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| CONNECTION DATE   | CONNECTED LOAD | ED  | BILL MONTH  | READING DATE | ISSUE DATE  | DUE DATE    |"<< endl;
cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << ConnectionDate << " | " << setw(15) << right << Load << " | " << setw(5) << right << EDRate << " | " << setw(10) << right << BillMonth << " | " << setw(12) << right << ReadingDate << " | " << setw(12) << right << IssueDate << " | " << setw(12) << right << DueDate << " |"<< endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| CONSUMER ID  | TARIF       | LOAD | OLD A/C NUMBER | DIVISION    | SUB DIVISION   | REFERENCE NO |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << ConsumerID << " | " << setw(13) << right << Tarrif << " | " << setw(4) << right << Load << " | " << setw(10) << right << OldACNumber << " | " << setw(11) << right << Division << " | " << setw(16) << right << SubDivision << " | " << setw(13) << right << ReferenceNo << " |"<< endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| NAME & ADDRESS       | MONTH     | UNITS | BILL | PAYMENT |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << Name << " | " << setw(15) << right << Address << " | " << setw(5) << right << Month << " | " << setw(10) << right << Units << " | " << setw(12) << right << Bill << " | " << setw(12) << right << Payment << " | " << setw(12) << right << DueDate << " |"<< endl;
cout << "| " << setw(20) << left << Name << " | " << setw(8) << right << BillMonth << " | " << setw(6) << right << UnitsConsumed << " | " << setw(4) << right << CurrentBill << " | " << setw(7) << right << "due" << " |"<< endl;
cout << "--------------------------------------------------------------------------------------------------------------------------" << endl; 
cout << "| METER NO     | PREVIOUS READING | PRESENT READING | MF  | UNITS | STATUS |" << endl;
cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << MeterNo << " | " << setw(14) << right << Previous << " | " << setw(15)<< right << Present << " | " << setw(5) << right << MF << " | " << setw(6) << right << UnitsConsumed << " | " << setw(7) << right << "OK" << " |"<< endl;
cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| TEXT Reference No to 8118 | بجلی سے متعلق نام شکایات کے جوانا نے پاٹل اور لوڈ شیٹنگ کی تفصیلات کے لئے پہلی فرصت |" << endl;
cout<<"--------------------------------------------------------------------------------------------------------------------------------" << endl;
cout<<"FUEL PRICE ADJUSTMENT" << " | " << setw(13) << right << "EXTRA TAX" << " | " << setw(12) << right << "SUBSIDIES" << " |" << endl;
cout <<"-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(11) << right << "F.C SURCHARGE" << " | " << setw(13) << right << FCSurcharge << " | " << setw(11) << right << "FURTHER TAX" << " | " << setw(10) << right << "TOTAL FPA" << " |" << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(11) << right << "TR SURCHARGE" << " | " << setw(11) << right << "NJ SURCHARGE" << " | " << setw(14) << right << "PAYABLE WITHIN DUE DATE" << " | " << setw(10) << right << Payablewithinduedate << " |" << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(17) << right << "QTR TARRIF ADJ/DMC" << " | " << setw(8) << right << "R-STAX" << " | " << setw(12) << right << "LPSURCHARGE" << " | " << setw(12) << right << LPSurcharge << " |" << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(10) << right << "TOTAL" << " | " << setw(20) << right << "PAYABLE AFTER DUE DATE" << " |" << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(19) << right << "BILL CALCULATION" << " | " << setw(10) << right << "GST ON FPA" << " | " << setw(12) << right << "GST ON FPA" << " |" << endl;
cout << "| " << setw(17) << right << "FURTHER TAX ON PA" << " | " << setw(11) << right << "S.TAX ON PA" << " | " << setw(5) << right << "GOP" << " |" << endl;
cout << "| " << setw(11) << right << "IT ON FPA" << " | " << setw(10) << right << "Tariff" << " | " << setw(8) << right << "Units" << " | " << setw(10) << right << "ET ON FPA" << " |" << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(15) << right << "TOTAL TAXES ON FPA" << " | " << setw(10) << right << "TOTAL" << " | " << setw(22) << right << "FOR COMPLAINT CONTACT" << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(16) << right << "DEFFERRED AMOUNT" << " | " << setw(8) << right << "SMS" << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(17) << right << "OUTSTANDING AMOUNT" << " | " << setw(6) << right << "@" << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(6) << right << "Center" << " | " << setw(5) << right << 8118 << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(25) << left << "Center Name : CHITTINAD" << " | " << setw(4) << left << "OR" << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(6) << right << "Call" << " | " << endl;
cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << "| " << setw(17) << right << "PROG. GST PAID F-Y" << " | " << setw(17) << right << "PROG. IT PAID F-Y" << " | " << setw(4) << right << 118 << " |" << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;


cout << "| " << setw(11) << right << "CUT HERE" << " | " << endl;
cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
;
cout << "| " << setw(7) << right << "IESCO" << " | " << setw(53) << right << "ISLAMABAD ELECTRIC SUPPLY COMPANY - ELECTRIC CONSUMER BILL" << endl;
cout << "| YOUR BETTER SERVICE - OUR PRIDE " << " www.lesco.com.pk " << " CONSUMER ID " << ConsumerID << " BILL NO " << BillNo << endl;
    return 0;
}


