#include<bits/stdc++.h>
#include <GL/glut.h>
#define ROD_RADIUS 0.025
#define DISC_RADIUS 0.25
#define LEFT_CENTER -0.65
#define MIDDLE_CENTER 0.00
#define RIGHT_CENTER 0.65
using namespace std;
int cnt=0;
stack<int> rods[3];
int n_disks;
// disc index, disc color
map<int,tuple<double,double,double>> disc_pictures;

void draw_rod(double center) {
    glBegin(GL_POLYGON);
    //center is |center +- 0.025|
    glColor3d(255.0,255.0,255.0);
    glVertex2f(center-ROD_RADIUS, -0.6);
    glVertex2f(center+ROD_RADIUS, -0.6);
    glVertex2f(center+ROD_RADIUS, 0.6);
    glVertex2f(center-ROD_RADIUS, 0.6);
    glEnd();

}
void clear() {
    for(int i=0; i<3; i++) {
        while(!rods[i].empty()) {
            rods[i].pop();
        }
    }
    n_disks=0;
    disc_pictures.clear();

}
void draw_disc(double center,int disc_label,double height) {
    glBegin(GL_POLYGON);
    //center is |center +- 0.025|
    glColor3d (get<0>(disc_pictures[disc_label]), get<1>(disc_pictures[disc_label]), get<2>(disc_pictures[disc_label]));
    double dd=DISC_RADIUS-(double(n_disks-disc_label)*DISC_RADIUS/11);
    glVertex2f(center-dd, -0.6+height);
    glVertex2f(center+dd, -0.6+height);
    glVertex2f(center+dd, -0.55+height);
    glVertex2f(center-dd, -0.55+height);
    glEnd();
}
void draw_ground(double center) {
    glBegin(GL_POLYGON);
    //center is |center +- 0.025|
    glColor3d (255.00,255.00,250.00);
    double dd=DISC_RADIUS;
    glVertex2f(center-dd, -0.6);
    glVertex2f(center+dd, -0.6);
    glVertex2f(center+dd, -0.55);
    glVertex2f(center-dd, -0.55);
    glEnd();
}


// print the current situation on rods
void print(stack<int> rods[3]) {
    stack<int> s[3];
    for(int i=0; i<3; i++) {
        s[i]=rods[i];
    }
    for(int j=0; j<3; j++) {

        printf("ROD %d\n",(j+1));
        while(!s[j].empty()) {

            for(int k=0; k<=s[j].top(); k++) printf("*");
            s[j].pop();
            printf("\n");

        }
        printf("\n\n");
    }

}
void draw() {
//draw each stack after each move
    glClear(GL_COLOR_BUFFER_BIT);
    draw_rod(LEFT_CENTER);
    draw_rod(MIDDLE_CENTER);
    draw_rod(RIGHT_CENTER);
    draw_ground(LEFT_CENTER);
    draw_ground(MIDDLE_CENTER);
    draw_ground(RIGHT_CENTER);
    stack<int> cprods[3]=rods;
    for(int i=0; i<3; i++) {
        double h=0.1;
        queue<int> helper;
        while(!cprods[i].empty()) {
            helper.push(cprods[i].top());
            cprods[i].pop();
        }
        stack<int> helper2;
        while(!helper.empty()) {
            helper2.push(helper.front());
            helper.pop();
        }
        while(!helper2.empty()) {
            int el=helper2.top();
            if(i==0) {
                draw_disc(LEFT_CENTER,el,h);
            } else if(i==1) {

                draw_disc(MIDDLE_CENTER,el,h);
            } else {

                draw_disc(RIGHT_CENTER,el,h);
            }
            helper2.pop();
            h+=0.1;
        }
    }
    glFlush();
}
// move the top element from s1 to top element of s2
void move_from_to(stack<int> *s1,stack<int> *s2) {
    int temp = s1->top();
    s1->pop();
    s2->push(temp);
    if(s1==&rods[0] && s2==&rods[1]) {
        printf("%d MOVE FROM %d to %d\n",cnt,0,1);
    } else if(s1==&rods[1] && s2==&rods[0]) {
        printf("%d MOVE FROM %d to %d\n",cnt,1,0);
    } else if(s1==&rods[0] && s2==&rods[2]) {
        printf("%d MOVE FROM %d to %d\n",cnt,0,2);
    } else if(s1==&rods[2] && s2==&rods[0]) {
        printf("%d MOVE FROM %d to %d\n",cnt,2,0);
    } else if(s1==&rods[1] && s2==&rods[2]) {
        printf("%d MOVE FROM %d to %d\n",cnt,1,2);
    } else if(s1==&rods[2] && s2==&rods[1]) {
        printf("%d MOVE FROM %d to %d\n",cnt,2,1);
    }
    //CHECK if it's compatible
    std::this_thread::sleep_for(2s);
    draw();
    printf("After step %d, situation is the following\n",cnt);
    print(rods);
    cnt++;
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
    } else {
        printf("ERROR");
    }
}
void recursive(int n, stack<int> *source, stack<int> *target, stack<int> *spare) {
    if(n==1) {
        move(source,target);
    } else {
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
    for(int i=0; i< (1 << n)-1; i++) {
        int mod=i%3;
        switch(mod) {
        case 0:
            move(&rods[src_pole],&rods[des_pole]);
            //legal movement of top disk between src_pole and des_pole
            break;
        case 1:
            move(&rods[src_pole],&rods[aux_pole]);
            // legal movement of top disk between src pole and aux_pole
            break;
        case 2:
            move(&rods[aux_pole],&rods[des_pole]);
            //legal movement of top disk between aux_pol and des_pole

            break;
        default:
            break;
        }
        //TODOmove IMPLEMENT UI
    }
}
//binary solution
void binary_sol(int n, stack<int>s[3]) {
    int moves=(1 << n)-1;
    // if the number of disks is even swap auxiliary and destination rod
    int encode[3]= {0,1,2};
    if(n%2==0) {
        swap(encode[1],encode[2]);
    };
    for(int i=1; i<=moves; i++) {
        move(&s[encode[(i & i-1)%3]],&s[encode[((i | i-1)+1)%3]]);
    }
}
int main(int argc, char** argv) {
    //number of disks used in a game
    // freopen("output.txt","w",stdout);
    int approach;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tower Of Hanoi");
    while(true) {
        cnt=0;
        clear();
        printf("Input the number of disks\n");
        scanf("%d",&n_disks);
        printf("Choose the algorithm\n");
        printf("For recursive approach type 1\n");
        printf("For iterative approach type 2\n");
        printf("For binary approach type 3\n");
        scanf("%d",&approach);
        // number of rods should always be 3
        const int n_rods=3;
        stack<int> cprods[3]=rods;
        //create three stacks to simulate 3 rods
        //add disks to the 1st stack with n_disks-1 being the heaviest and 0 being lightest

        for(int i=1; i<=n_disks; i++) {
            rods[0].push(n_disks-i);
            string randomcolor;
            //assign a random color to a disc
            disc_pictures.insert(make_pair(n_disks-i,make_tuple(((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX)) )));
        }
        //draw the initial picture -> all disks on one side
        draw();
        std::this_thread::sleep_for(2s);
        if(approach==1){
            iterative(n_disks,rods);
        }else if(approach==2){
            recursive(n_disks, &rods[0], &rods[2], &rods[1]);
        }else{
            binary_sol(n_disks,rods);
        }
        std::this_thread::sleep_for(4s);
    }
}

