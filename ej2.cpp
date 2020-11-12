#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;
const int NO_OF_STATES = 10;
int n1;
class states
{
public:
    char status;
    int sno;
    int gp;
    int* ts;
    states()
    {
        sno=gp=0;
        ts=NULL;
    }
    states(int state_no)
    {
        gp=0;
        sno=state_no;
        ts = new int[2];
        for(int i=0;i<2;i++)
            ts[i]=-1;
    }
    void input();
    void output();
};

void states::input()
{
    char ch='0';
    cout<<"\nIngrese detalles de transicion para ";
    cout<<"estado q"<<sno<<" : \n";
    for(int j=0;j<2;j++,ch++)
    {
        cout<<"Estado al que va con input "<<ch<<" : q";
        cin>>ts[j];
    }
    cout<<"No es o es un estado final? (N/F) : ";
    cin>>status;
    if(status=='n'||status=='N')
        gp=0;
    else
        gp=1;
}

void states::output()
{
    if(sno==-1){
        return;}
    cout<<"\n\n    q "<<sno<<"| - ";
    for(int i=0;i<2;i++){
        if(ts[i]!=-1){
            cout<<"      q"<<ts[i];
            }
        else {
            cout << "    N/A";
        }}
    if(sno==0)
        cout<<"     Estado inicial";
    if((status=='f'  ||   status=='F')and(sno==0))
        cout<<" y final";
    else if(status=='f'  ||   status=='F')
        cout<<"     Estado final";

}
void revision(states *);
int main()
{   states sta;
    char ch='0';
    cout<<"\nIngrese detalles del AFD : \n";
    cout<<"\nIngrese numero de estados :";
    cin>>n1;
    states state[NO_OF_STATES]={0,1,2,3,4,5,6,7,8,9};
    for(int i=0;i<n1;i++)
        state[i].input();

    revision(state);

    cout<<"        |    Inputs\n";
    cout<<"Estados |   ";
    for(int i=0;i<2;i++,ch++)          cout<<"      "<<ch;
    cout<<endl;
    for(int i=0;i<5;i++)               cout<<"-----";
    for(int i=0;i<n1;i++)
        state[i].output();
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Matriz de equivalencia";
    cout<<endl;
    cout<<"______________________";
    cout<<endl;
    for (int i=0; i < n1;i++){
        for (int j=0; j < n1
        ;j++){

            if (i==j){
                cout<<"1 ";}
            else{
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
    getch();


}



int existe(int s[],int ref)
{   states sta;
    for(int i=0;i<n1;i++)
        if(s[i]==ref)
            return i;

    return -1;
}

void revision(states state[])
{
    int array[NO_OF_STATES],temp,newgp[NO_OF_STATES],flag=0,count=2;
    for(int outerloop=0;outerloop<n1-2;outerloop++)
    {
        for(int j=0;j<2;j++)
        {
            for(int z=0;z<NO_OF_STATES;z++)
                array[z]=-1;
            for(int i=0;i<n1;i++)
            {
                temp=state[i].ts[j];
                for(int k=0;k<n1;k++)
                    if(state[k].sno==temp)
                    {
                        array[i]=state[k].gp;
                        break;
                    }
            }

            for(int i=0;i<n1-1;i++)
            {
                for(int z=0;z<NO_OF_STATES;z++)  newgp[z]=-1;
                flag=0;
                for(int k=i+1;k<n1;k++)
                {
                    if(state[i].gp==state[k].gp)
                    {
                        if((array[i]!=array[k]) && ( (flag==0) || (existe(newgp,array[k])==-1)) )
                        {
                            state[k].gp = count;
                            count++;
                            newgp[k] = array[k];
                            flag++;

                        }
                        else if(array[i]!=array[k])
                        {
                            state[k].gp = state[existe(newgp,array[k])].gp;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<n1-1;i++)
    {
        if(state[i].sno!=-1)
            for(int j=i+1;j<n1;j++)
                if(state[i].gp==state[j].gp)
                {
                    for(int h=0;h<n1;h++)
                        for(int z=0;z<2;z++)
                            if(state[h].ts[z]==state[j].sno)
                                state[h].ts[z]=state[i].sno;
                    state[j].sno=-1;
                    if((state[j].status=='f') || (state[j].status=='F'))
                        state[i].status='F';
                }
    }
}