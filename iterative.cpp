#include<bits/stdc++.h>
using namespace std;

// move the top element from s1 to top element of s2
void move_from_to(stack<int> *s1,stack<int> *s2) {
    int temp = s1->top();
    s1->pop();
    s2->push(temp);
}
// determine the regular move and perform it
void move(stack<int> *s1,stack<int> *s2) {

    if(s1->empty()) {
        move_from_to(s2,s1);
    } else if(s2->empty()) {
        move_from_to(s1,s2);
    } else if(s1->top()>s2->top()) {
        move_from_to(s2,s1);
    } else {
        move_from_to(s1,s2);
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
//iterative solution to the problem
void iterative(int n, stack<int>rods[3]) {
    //source pole initially 0
    int src_pole=0;
    // auxiliary pole initially 1
    int aux_pole=1;
    // destination pole initially 2
    int des_pole=2;
    // if number of disks is even swap auxiliary and destination pole
    if(n%2==0) swap(src_pole,des_pole);
    
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
        //TODO IMPLEMENT UIO
        printf("After step %d, situation is the following\n",i);
        print(rods);
    }
}
int main() {
    //number of disks used in a game
    int n_disks=3;
    // number of rods should always be 3
    const int n_rods=3;
    //create three stacks to simulate 3 rods
    stack<int> rods[n_rods];
    //add disks to the 1st stack with n_disks-1 being the heaviest and 0 being lightest
    for(int i=1; i<=n_disks; i++) rods[0].push(n_disks-i);
    iterative(n_disks,rods);
}
