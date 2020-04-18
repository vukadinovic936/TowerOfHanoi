#include<bits/stdc++.h>
using namespace std;

// move the top element from s1 to top element of s2
//
stack<int> rods[3];
void move_from_to(stack<int> *s1,stack<int> *s2) {
    int temp = s1->top();
    s1->pop();
    s2->push(temp);
    if(s1==&rods[0] && s2==&rods[1]){
        printf("MOVE FROM %d to %d\n",0,1);
    }else if(s1==&rods[1] && s2==&rods[0]){
        printf("MOVE FROM %d to %d\n",1,0);
    }else if(s1==&rods[0] && s2==&rods[2]){
        printf("MOVE FROM %d to %d\n",0,2);
    }else if(s1==&rods[2] && s2==&rods[0]){
        printf("MOVE FROM %d to %d\n",2,0);
    }else if(s1==&rods[1] && s2==&rods[2]){
        printf("MOVE FROM %d to %d\n",1,2);
    }else if(s1==&rods[2] && s2==&rods[1]){
        printf("MOVE FROM %d to %d\n",2,1);
    }
}
// determine the regular move and perform it
void move(stack<int> *s1,stack<int> *s2) {

    if(s1->empty()) {
        move_from_to(s2,s1);
    } else if(s2->empty()) {
        move_from_to(s1,s2);
    } else if(s1->top()>s2->top()) {
        move_from_to(s2,s1);
    } else if(s1->top()<s2->top()) {
        move_from_to(s1,s2);
    }else{
        printf("ERROR");
    }
}
// print the current situation on rods
void print(stack<int> rods[3]) {
    stack<int> s[3]; 
    for(int i=0;i<3;i++){
        s[i]=rods[i];
    }
    for(int j=0; j<3; j++) {

        printf("ROD %d\n",(j+1));
        while(!s[j].empty()){

        for(int k=0;k<=s[j].top();k++) printf("*");
        s[j].pop(); 
        printf("\n");

        }
        printf("\n\n");
    }

}
void recursive(int n, stack<int> *source, stack<int> *target, stack<int> *spare){
    if(n==1){
        move(source,target);
    }else{
        recursive(n-1,source,spare,target);
        recursive(1,source,target,spare);
        recursive(n-1,spare,target,source);
    }
}
//iterative solution to the problem
void iterative(int n, stack<int>rods[3]) {
    //source pole initially 0
    int src_pole=0;
    // auxiliary pole initially 1
    int aux_pole=1;
    // destination pole initially 2
    int des_pole=2;
    // if number of disks is even swap auxiliary and destination pole
    if(n%2==0) swap(aux_pole,des_pole);
    
    //minimum number of movements is 2^n-1
    for(int i=1; i<= (1 << n)-1; i++) {
        int mod=i%3;
        switch(mod) {
        case 0:
            move(&rods[aux_pole],&rods[des_pole]);
            //legal movement of top disk between aux_pol and des_pole
            break;
        case 1:
            move(&rods[src_pole],&rods[des_pole]);
            //legal movement of top disk between src_pole and des_pole
            break;
        case 2:
            move(&rods[src_pole],&rods[aux_pole]);
            // legal movement of top disk between src pole and aux_pole
            break;
        default:
            break;
        }
        //TODOmove IMPLEMENT UI
        printf("After step %d, situation is the following\n",i);
        print(rods);
    }
}
//binary solution
void binary_sol(int n, stack<int>s[3]){
   int moves=(1 << n)-1;  
   // if the number of disks is even swap auxiliary and destination rod
   int encode[3]={0,1,2};
   if(n%2==0){ swap(encode[1],encode[2]);};
   for(int i=1;i<=moves;i++){
       move(&s[encode[(i & i-1)%3]],&s[encode[((i | i-1)+1)%3]]);
   }
}
int main() {
    //number of disks used in a game
    int n_disks=4;
    // number of rods should always be 3
    const int n_rods=3;
    //create three stacks to simulate 3 rods
    //add disks to the 1st stack with n_disks-1 being the heaviest and 0 being lightest
    for(int i=1; i<=n_disks; i++) rods[0].push(n_disks-i);
    //iterative(n_disks,rods);
   // recursive(n_disks, &rods[0], &rods[2], &rods[1]);
    binary_sol(n_disks,rods);
    print(rods);
}
