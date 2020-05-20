#include<iostream>
using namespace std;

class face
{
public:
    int blocks[3][3];
    face *lefter=NULL,*righter=NULL,*upper=NULL,*downer=NULL;
    void turn90CW();
    void turn90AC();
    bool sorted();
};

class cube
{
private:
    face top,bottom;
    face surrounding[4];
    face *view=&surrounding[0];
public:
    cube();     //输入顺序：前 后 左 右 顶 底，各面按阅读顺序输入颜色代号（黄Y，红R，绿G，橙O，蓝B，白W）

    bool restored();

    void _y();
    void _y_();
    void _R();
    void _R_();
    void R();
    void R_();
    void L();
    void L_();
    void U();
    void U_();
    void D();
    void D_();
    void F();
    void F_();
    void B();
    void B_();

    void cross_on_bottom();
    bool bottom_cross_done();
    bool bottom_cross_need_to_be_sorted();

    void finish_bottom();
    bool bottom_done();

    void sort_level_1();
    bool level_1_is_sorted();

    void finish_level_2();
    bool level_2_done();
    void level_2_process_with(face *,face *);
    void level_2_process_with(face *,int);

    void cross_on_top();
    void cross_on_top(int);
    bool top_cross_done();
    int way_to_top_cross();

    void finish_top();
    bool top_done();
    int pattern_of_top();

    void sort_level_3();
    void level_3_step_1();
    bool level_3_is_sorted();
    bool need_step_0();
    bool have_one_sorted_color();
};

class pattern
{
public:
    int p[4];
    pattern(int,int,int,int);
    pattern(int,int,int,int,int);
    void standardize(int);
};

pattern::pattern(int a,int b,int c,int d)
{
    p[0]=a;
    p[1]=b;
    p[2]=c;
    p[3]=d;
}

pattern::pattern(int a,int b,int c,int d,int standard_color)
{
    p[0]=a;
    p[1]=b;
    p[2]=c;
    p[3]=d;
    standardize(standard_color);
}

void pattern::standardize(int standard_color)
{
    for(int i=0;i<4;i++){
        if(p[i]==standard_color)p[i]=1;
        else p[i]=0;
    }
}

bool face::sorted()
{
    int center_color=blocks[1][1];
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(blocks[i][j]!=center_color)return false;
    return true;
}

void cube::_y()
{
    view=view->righter;
    view->upper->turn90CW();
    view->downer->turn90AC();
}
void cube::_y_()
{
    view=view->lefter;
    view->upper->turn90AC();
    view->downer->turn90CW();
}
void cube::_R()
{
    view->righter->turn90CW();
    int temp[3]={
        view->righter->upper->blocks[0][2],
        view->righter->upper->blocks[1][2],
        view->righter->upper->blocks[2][2]};
    for(int i=0;i<3;i++){
        view->upper->blocks[i][2]=view->blocks[i][2];
    }
    for(int i=0;i<3;i++){
        view->blocks[i][2]=view->downer->blocks[i][2];
    }
    for(int i=0;i<3;i++){
        view->downer->blocks[i][2]=view->righter->righter->blocks[2-i][0];
    }
    for(int i=0;i<3;i++){
        view->righter->righter->blocks[2-i][0]=temp[i];
    }
}
void cube::_R_()
{
    view->righter->turn90AC();
    int temp[3]={
        view->righter->upper->blocks[0][2],
        view->righter->upper->blocks[1][2],
        view->righter->upper->blocks[2][2]};
    for(int i=0;i<3;i++){
        view->upper->blocks[i][2]=view->righter->righter->blocks[2-i][0];
    }
    for(int i=0;i<3;i++){
        view->righter->righter->blocks[2-i][0]=view->downer->blocks[i][2];
    }
    for(int i=0;i<3;i++){
        view->downer->blocks[i][2]=view->blocks[i][2];
    }
    for(int i=0;i<3;i++){
        view->blocks[i][2]=temp[i];
    }
}
void cube::R()
{
    _R();
    cout<<"R ";
}
void cube::R_()
{
    _R_();
    cout<<"Ri ";
}
void cube::L()
{
    _y();
    _y();
    _R();
    _y();
    _y();
    cout<<"L ";
}
void cube::L_()
{
    _y();
    _y();
    _R_();
    _y();
    _y();
    cout<<"Li ";
}
void cube::F()
{
    _y_();
    _R();
    _y();
    cout<<"F ";
}
void cube::F_()
{
    _y_();
    _R_();
    _y();
    cout<<"Fi ";
}
void cube::B()
{
    _y();
    _R();
    _y_();
    cout<<"B ";
}
void cube::B_()
{
    _y();
    _R_();
    _y_();
    cout<<"Bi ";
}
void cube::U()
{
    view->upper->turn90CW();
    for(int i=0;i<3;i++){
        int temp=view->blocks[0][i];
        view->blocks[0][i]=view->righter->blocks[0][i];
        view->righter->blocks[0][i]=view->righter->righter->blocks[0][i];
        view->righter->righter->blocks[0][i]=view->lefter->blocks[0][i];
        view->lefter->blocks[0][i]=temp;
    }
    cout<<"U ";
}
void cube::U_()
{
    view->upper->turn90AC();
    for(int i=0;i<3;i++){
        int temp=view->blocks[0][i];
        view->blocks[0][i]=view->lefter->blocks[0][i];
        view->lefter->blocks[0][i]=view->lefter->lefter->blocks[0][i];
        view->lefter->lefter->blocks[0][i]=view->righter->blocks[0][i];
        view->righter->blocks[0][i]=temp;
    }
    cout<<"Ui ";
}
void cube::D()
{
    view->downer->turn90CW();
    for(int i=0;i<3;i++){
        int temp=view->blocks[2][i];
        view->blocks[2][i]=view->lefter->blocks[2][i];
        view->lefter->blocks[2][i]=view->lefter->lefter->blocks[2][i];
        view->lefter->lefter->blocks[2][i]=view->righter->blocks[2][i];
        view->righter->blocks[2][i]=temp;
    }
    cout<<"D ";
}
void cube::D_()
{
    view->downer->turn90AC();
    for(int i=0;i<3;i++){
        int temp=view->blocks[2][i];
        view->blocks[2][i]=view->righter->blocks[2][i];
        view->righter->blocks[2][i]=view->righter->righter->blocks[2][i];
        view->righter->righter->blocks[2][i]=view->lefter->blocks[2][i];
        view->lefter->blocks[2][i]=temp;
    }
    cout<<"Di ";
}

void face::turn90CW()
{
    int temp;
    temp=blocks[2][0];
    blocks[2][0]=blocks[2][2];
    blocks[2][2]=blocks[0][2];
    blocks[0][2]=blocks[0][0];
    blocks[0][0]=temp;
    temp=blocks[1][0];
    blocks[1][0]=blocks[2][1];
    blocks[2][1]=blocks[1][2];
    blocks[1][2]=blocks[0][1];
    blocks[0][1]=temp;
}

void face::turn90AC()
{
    int temp;
    temp=blocks[2][2];
    blocks[2][2]=blocks[2][0];
    blocks[2][0]=blocks[0][0];
    blocks[0][0]=blocks[0][2];
    blocks[0][2]=temp;
    temp=blocks[1][0];
    blocks[1][0]=blocks[0][1];
    blocks[0][1]=blocks[1][2];
    blocks[1][2]=blocks[2][1];
    blocks[2][1]=temp;
}

int color_num(char c){
    switch(c)
    {
        case 'Y':return 0;
        case 'R':return 1;
        case 'G':return 2;
        case 'O':return 3;
        case 'B':return 4;
        case 'W':return 5;
        default:return 6;
    }
}

cube::cube()
{
    //输入顺序：顶面，底面，前，右，后，左。
    char color;
    for(int k=0;k<4;k++){
        surrounding[k].upper=&top;
        surrounding[k].downer=&bottom;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;surrounding[0].blocks[i][j]=color_num(color);}
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;surrounding[2].blocks[i][j]=color_num(color);}
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;surrounding[3].blocks[i][j]=color_num(color);}
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;surrounding[1].blocks[i][j]=color_num(color);}
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;top.blocks[i][j]=color_num(color);}
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){cin>>color;bottom.blocks[i][j]=color_num(color);}
    }
    surrounding[0].lefter=&surrounding[3];
    surrounding[0].righter=&surrounding[1];

    surrounding[1].lefter=&surrounding[0];
    surrounding[1].righter=&surrounding[2];

    surrounding[2].lefter=&surrounding[1];
    surrounding[2].righter=&surrounding[3];

    surrounding[3].lefter=&surrounding[2];
    surrounding[3].righter=&surrounding[0];
}

bool cube::restored()
{
    if(!top.sorted()||!bottom.sorted())return false;
    for(face *check=view;;check=check->righter){
        if(!check->sorted())return false;
        if(check->righter==view)break;
    }
    return true;
}

void cube::cross_on_bottom()
{
    int target_color=view->downer->blocks[1][1];
    while(!bottom_cross_done()){
        if(top.blocks[2][1]==target_color){
            int another_color=view->blocks[0][1];
            face *search;
            for(search=view;search->blocks[1][1]!=another_color;search=search->lefter)U();
            if(search==view){F();F();}
            else if(search==view->righter){R();R();}
            else if(search==view->lefter){L();L();}
            else {B();B();}
            continue;
        }
        if(top.blocks[1][2]==target_color){
            int another_color=view->righter->blocks[0][1];
            face *search;
            for(search=view->righter;search->blocks[1][1]!=another_color;search=search->lefter)U();
            if(search==view){F();F();}
            else if(search==view->righter){R();R();}
            else if(search==view->lefter){L();L();}
            else {B();B();}
            continue;
        }
        if(top.blocks[1][0]==target_color){
            int another_color=view->lefter->blocks[0][1];
            face *search;
            for(search=view->lefter;search->blocks[1][1]!=another_color;search=search->lefter)U();
            if(search==view){F();F();}
            else if(search==view->righter){R();R();}
            else if(search==view->lefter){L();L();}
            else {B();B();}
            continue;
        }
        if(top.blocks[0][1]==target_color){
            int another_color=view->lefter->lefter->blocks[0][1];
            face *search;
            for(search=view->lefter->lefter;search->blocks[1][1]!=another_color;search=search->lefter)U();
            if(search==view){F();F();}
            else if(search==view->righter){R();R();}
            else if(search==view->lefter){L();L();}
            else {B();B();}
            continue;
        }


        if(view->blocks[0][1]==target_color){
            F();    R();    U_();   R_();   F_();
            continue;
        }
        if(view->righter->blocks[0][1]==target_color){
            R_();    F_();    U();   F();   R();
            continue;
        }
        if(view->lefter->blocks[0][1]==target_color){
            L();    F();    U_();   F_();   L_();
            continue;
        }
        if(view->righter->righter->blocks[0][1]==target_color){
            U();    U();
            F();    R();    U_();   R_();   F_();
            continue;
        }


        if(view->blocks[2][1]==target_color){
            if(bottom.blocks[0][1]==view->blocks[1][1]){
                F_();   R();    U();    R_();   F();    F();
                continue;
            }
            else{
                F_();   R();    U();    R_();
                continue;
            }
        }
        if(view->righter->blocks[2][1]==target_color){
            if(bottom.blocks[1][2]==view->righter->blocks[1][1]){
                R();   F_();    U_();    F();   R_();    R_();
                continue;
            }
            else{
                R();   F_();    U_();    F();
                continue;
            }
        }
        if(view->lefter->blocks[2][1]==target_color){
            if(bottom.blocks[1][0]==view->lefter->blocks[1][1]){
                L_();   F();    U();    F_();   L();    L();
                continue;
            }
            else{
                L_();   F();    U();    F_();
                continue;
            }
        }
        if(view->lefter->lefter->blocks[2][1]==target_color){
            if(bottom.blocks[2][1]==view->lefter->lefter->blocks[1][1]){
                L_();   F();    U();    F_();   L();    L();
                continue;
            }
            else{
                L_();   F();    U();    F_();
                continue;
            }
        }


        if(view->blocks[1][0]==target_color){
            L_();   U_();   L();
            continue;
        }
        else if(view->blocks[1][2]==target_color){
            R();    U();    R_();
            continue;
        }
        if(view->righter->blocks[1][0]==target_color){
            F_();   U_();   F();
            continue;
        }
        else if(view->righter->blocks[1][2]==target_color){
            B();    U();    B_();
            continue;
        }
        if(view->lefter->blocks[1][0]==target_color){
            B_();   U_();   B();
            continue;
        }
        else if(view->lefter->blocks[1][2]==target_color){
            F();    U();    F_();
            continue;
        }
        if(view->righter->righter->blocks[1][0]==target_color){
            R_();   U_();   R();
            continue;
        }
        else if(view->righter->righter->blocks[1][2]==target_color){
            L();    U();    L_();
            continue;
        }
    }
    if(bottom_cross_need_to_be_sorted()){
        F();F();R();R();B();B();L();L();
        int i=0;
        for(face *search=view;i<4;i++,search=search->righter){
            while(search->blocks[0][1]!=search->blocks[1][1])U();
            if(search==view){F();F();}
            else if(search==view->righter){R();R();}
            else if(search==view->lefter){L();L();}
            else {B();B();}
        }
    }
}

bool cube::bottom_cross_done()
{
    int count=0;
    if(bottom.blocks[0][1]==bottom.blocks[1][1])count++;
    if(bottom.blocks[1][0]==bottom.blocks[1][1])count++;
    if(bottom.blocks[1][2]==bottom.blocks[1][1])count++;
    if(bottom.blocks[2][1]==bottom.blocks[1][1])count++;
    if(count==4)return true;
    else return false;
}
bool cube::bottom_cross_need_to_be_sorted()
{
    int i=0;
    for(face *search=view;i<4;search=search->lefter,i++){
        if(search->blocks[1][1]!=search->blocks[2][1])return true;
    }
    return false;
}
void cube::finish_bottom()
{
    int main_color=view->downer->blocks[1][1];
    while(!bottom_done()){
        if(view->upper->blocks[2][2]==main_color){
            while(view->downer->blocks[0][2]==main_color)D();
            F_();   U_();   U_();   F();    U();    F_();   U_();   F();
            continue;
        }
        if(view->upper->blocks[2][0]==main_color){
            while (view->downer->blocks[0][0]==main_color)D();
            L_();   U_();   U_();   L();    U();    L_();   U_();   L();
            continue;
        }
        if(view->upper->blocks[0][0]==main_color){U_();continue;}
        if(view->upper->blocks[0][2]==main_color){U();continue;}

        if(view->blocks[0][2]==main_color){
            while(view->downer->blocks[0][2]==main_color)D();
            U();    R();    U_();   R_();
            continue;
        }
        if(view->blocks[0][0]==main_color){
            while(view->downer->blocks[0][0]==main_color)D();
            U_();    L_();    U();   L();
            continue;
        }
        if(view->righter->blocks[0][0]==main_color){
            while(view->downer->blocks[0][2]==main_color)D();
            R();    U();    R_();
        }
        if(view->lefter->blocks[0][2]==main_color){
            while(view->downer->blocks[0][0]==main_color)D();
            L_();    U_();    L();
        }
        if(view->righter->blocks[0][2]==main_color||view->righter->righter->blocks[0][0]==main_color){U();continue;}
        if(view->lefter->blocks[0][0]==main_color||view->righter->righter->blocks[0][2]==main_color){U_();continue;}

        if(view->blocks[2][2]==main_color){
            U();    R();    U_();   R_();   U();    R();    U_();   R_();
            continue;
        }
        if(view->blocks[2][0]==main_color){
            L_();   U();    L();    U_();   L_();   U();    L();
            continue;
        }
        if(view->righter->blocks[2][0]==main_color){
            F_();   U();    F();    U_();   F_();   U();    F();
            continue;
        }
        if(view->lefter->blocks[2][2]==main_color){
            U();    F();    U_();   F_();   U();    F();    U_();   F_();
            continue;
        }
        if(view->lefter->blocks[2][0]==main_color||view->lefter->lefter->blocks[2][2]==main_color){D();continue;}
        if(view->righter->blocks[2][2]==main_color||view->lefter->lefter->blocks[2][0]==main_color){D();continue;}
    }
    while(view->blocks[1][1]!=view->blocks[2][1])D();
}
bool cube::bottom_done()
{
    int check=bottom.blocks[1][1];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)if(bottom.blocks[i][j]!=check)return false;
    }
    return true;
}
void cube::sort_level_1()
{
    while(!level_1_is_sorted()){
        while(view->blocks[2][2]==view->blocks[1][1])D();
        R();    U();    R_();
        while(view->blocks[0][0]!=view->righter->blocks[2][1])D();
        R();    U_();    R_();
        if(bottom_done())continue;
        while(view->blocks[0][2]!=view->lefter->blocks[2][1])D();
        L_();   U();    L();
        if(bottom_done())continue;
        while(view->blocks[0][0]!=view->righter->blocks[2][1])D();
        R();    U_();    R_();
        if(bottom_done())continue;
        while(view->blocks[0][2]!=view->lefter->blocks[2][1])D();
        L_();   U();    L();
        if(bottom_done())continue;
    }
    while(view->blocks[1][1]!=view->blocks[2][1])D();
}
bool cube::level_1_is_sorted()
{
    face *check=view;
    for(;;check=check->righter){
        if(check->blocks[2][0]==check->blocks[2][1]&&check->blocks[2][0]==check->blocks[2][2]){
            if(check->righter==view)break;
            continue;
        }
        else return false;
    }
    return true;
}
void cube::finish_level_2()
{
    int top_color=view->upper->blocks[1][1];
    while(!level_2_done()){
        if(view->blocks[0][1]!=top_color&&view->upper->blocks[2][1]!=top_color){
            face *temp_view=view;
            for(;temp_view->blocks[1][1]!=view->blocks[0][1];temp_view=temp_view->righter);
            level_2_process_with(temp_view, view);
            continue;
        }
        if(view->righter->blocks[0][1]!=top_color&&view->upper->blocks[1][2]!=top_color){
            face *temp_view=view->righter;
            for(;temp_view->blocks[1][1]!=view->righter->blocks[0][1];temp_view=temp_view->righter);
            level_2_process_with(temp_view, view->righter);
            continue;
        }
        if(view->lefter->blocks[0][1]!=top_color&&view->upper->blocks[1][0]!=top_color){
            face *temp_view=view->lefter;
            for(;temp_view->blocks[1][1]!=view->lefter->blocks[0][1];temp_view=temp_view->righter);
            level_2_process_with(temp_view, view->lefter);
            continue;
        }
        if(view->righter->righter->blocks[0][1]!=top_color&&view->upper->blocks[0][1]!=top_color){
            face *temp_view=view->righter->righter;
            for(;temp_view->blocks[1][1]!=view->righter->righter->blocks[0][1];temp_view=temp_view->righter);
            level_2_process_with(temp_view, view->righter->righter);
            continue;
        }

        for(face *temp_view=view;;temp_view=temp_view->righter){
            if(temp_view->blocks[1][2]!=temp_view->blocks[1][1])level_2_process_with(temp_view, 1);
            if(temp_view->righter==view)break;
        }
    }
}
void cube::level_2_process_with(face *target_view,face *start_view)
{
    if(target_view==start_view->righter)U_();
    if(target_view==start_view->lefter)U();
    if(target_view==start_view->righter->righter){U();U();}

    if(target_view==view){
        if(target_view->upper->blocks[2][1]==target_view->righter->blocks[1][1]){
            U();    R();    U_();   R_();   U_();   F_();   U();    F();
        }
        else{
            U_();   L_();   U();    L();    U();    F();    U_();   F_();
        }
    }
    if(target_view==view->righter){
        if(target_view->upper->blocks[1][2]==target_view->righter->blocks[1][1]){
            U();    B();    U_();   B_();   U_();   R_();   U();    R();
        }
        else{
            U_();   F_();   U();    F();    U();    R();    U_();   R_();
        }
    }
    if(target_view==view->lefter){
        if(target_view->upper->blocks[1][0]==target_view->righter->blocks[1][1]){
            U();    F();    U_();   F_();   U_();   L_();   U();    L();
        }
        else{
            U_();   B_();   U();    B();    U();    L();    U_();   L_();
        }
    }
    if(target_view==view->righter->righter){
        if(target_view->upper->blocks[0][1]==target_view->righter->blocks[1][1]){
            U();    L();    U_();   L_();   U_();   B_();   U();    B();
        }
        else{
            U_();   R_();   U();    R();    U();    B();    U_();   B_();
        }
    }
}
bool cube::level_2_done()
{
    face *check=view;
    for(;;check=check->righter){
        if(check->blocks[1][0]==check->blocks[1][1]&&check->blocks[1][0]==check->blocks[1][2]){
            if(check->righter==view)break;
            continue;
        }
        else return false;
    }
    return true;
}

void cube::level_2_process_with(face *target_view,int right_side)
{
    if(target_view==view){
        if(right_side){
            U();    R();    U_();   R_();   U_();   F_();   U();    F();
        }
        else{
            U_();   L_();   U();    L();    U();    F();    U_();   F_();
        }
    }
    if(target_view==view->righter){
        if(right_side){
            U();    B();    U_();   B_();   U_();   R_();   U();    R();
        }
        else{
            U_();   F_();   U();    F();    U();    R();    U_();   R_();
        }
    }
    if(target_view==view->lefter){
        if(right_side){
            U();    F();    U_();   F_();   U_();   L_();   U();    L();
        }
        else{
            U_();   B_();   U();    B();    U();    L();    U_();   L_();
        }
    }
    if(target_view==view->righter->righter){
        if(right_side){
            U();    L();    U_();   L_();   U_();   B_();   U();    B();
        }
        else{
            U_();   R_();   U();    R();    U();    B();    U_();   B_();
        }
    }
}

bool cube::top_cross_done()
{
    int top_color=top.blocks[1][1];
    bool result=true;
    if(top.blocks[0][1]!=top_color)result=false;
    if(top.blocks[1][0]!=top_color)result=false;
    if(top.blocks[1][2]!=top_color)result=false;
    if(top.blocks[2][1]!=top_color)result=false;
    return result;
}

int cube::way_to_top_cross()
{
    if(top.blocks[1][0]==top.blocks[1][1]&&top.blocks[1][2]==top.blocks[1][1])return 10;
    if(top.blocks[0][1]==top.blocks[1][1]&&top.blocks[2][1]==top.blocks[1][1])return 11;

    if(top.blocks[2][1]==top.blocks[1][1]&&top.blocks[1][2]==top.blocks[1][1])return 20;
    if(top.blocks[0][1]==top.blocks[1][1]&&top.blocks[1][2]==top.blocks[1][1])return 21;
    if(top.blocks[0][1]==top.blocks[1][1]&&top.blocks[1][0]==top.blocks[1][1])return 22;
    if(top.blocks[1][0]==top.blocks[1][1]&&top.blocks[2][1]==top.blocks[1][1])return 23;

    return 20;
}

void cube::cross_on_top()
{
    while(!top_cross_done()){
        cross_on_top(way_to_top_cross());
    }
}
void cube::cross_on_top(int way)
{
    switch(way%10)
    {
        case 1:U();break;
        case 2:U();U();break;
        case 3:U_();break;
        default:break;
    }
    switch(way/10)
    {
        case 1:{F();R();U();R_();U_();F_();break;}
        case 2:{B();U();L();U_();L_();B_();break;}
    }
}
void cube::finish_top()
{
    while(!top_done()){
        while(pattern_of_top()==0)U();
        switch(pattern_of_top())
        {
            case 1:
                R_();U_();R();U_();R_();U_();U_();R();
                break;
            case 2:
                F();U();F_();U();F();U();U();F_();
                break;
            case 3:
                L();F();R_();F_();L_();F();R();F_();
                break;
            case 4:
                F_();
                L();F();R_();F_();L_();F();R();
                break;
            case 5:
                U();
                R();R();D_();R();U_();U_();R_();D();R();U_();U_();R();
                break;
            case 6:
                R();U();U();R_();U_();R();U();R_();U_();R();U_();R_();
                break;
            case 7:
                R();U_();U_();R_();R_();U_();R();R();U_();R_();R_();U();U();R();
                break;
        }
    }
}
bool cube::top_done()
{
    int top_color=top.blocks[1][1];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(top.blocks[i][j]!=top_color)return false;
        }
    }
    return true;
}
bool operator==(pattern p1,pattern p2)
{
    for(int i=0;i<4;i++)if(p1.p[i]!=p2.p[i])return false;
    return true;
}
int cube::pattern_of_top()
{
    int top_color=top.blocks[1][1];
    pattern p(top.blocks[0][0],top.blocks[0][2],top.blocks[2][0],top.blocks[2][2],top_color);
    pattern fish(1,0,0,0);
    pattern tank(0,1,0,1);
    pattern cross(0,0,0,0);
    pattern butterfly(0,1,1,0);

    if(p==fish){
        if(view->blocks[0][0]==top_color)return 1;
        if(view->blocks[0][2]==top_color)return 2;
    }
    if(p==tank){
        if(view->blocks[0][0]==top_color)return 3;
        else return 5;
    }
    if(p==butterfly)return 4;
    if(p==cross){
        if(view->blocks[0][0]==top_color&&view->blocks[0][2]==top_color&&view->righter->righter->blocks[0][0]==top_color)return 6;
        if(view->lefter->blocks[0][0]==top_color&&view->lefter->blocks[0][2]==top_color&&view->blocks[0][2]==top_color)return 7;
    }
    return 0;
}
void cube::level_3_step_1()
{
    R();R();F();F();R_();B_();R();F();F();R_();B();R_();
}
void cube::sort_level_3()
{
    while(!level_3_is_sorted()){
        while(need_step_0()){
            if(view->blocks[0][0]==view->blocks[0][2]){
                U_();
                level_3_step_1();
            }
            else if(view->righter->blocks[0][0]==view->righter->blocks[0][2]){
                level_3_step_1();
            }
            else if(view->lefter->blocks[0][0]==view->lefter->blocks[0][2]){
                U();U();
                level_3_step_1();
            }
            else if(view->righter->righter->blocks[0][0]==view->righter->righter->blocks[0][2]){
                U();
                level_3_step_1();
            }
            else{level_3_step_1();continue;}
        }
        if(have_one_sorted_color()){
            face *temp_view=view;
            while(temp_view->blocks[0][1]!=temp_view->blocks[0][0])temp_view=temp_view->righter;
            if(temp_view==view){U();U();}
            if(temp_view==view->lefter)U();
            if(temp_view==view->righter)U_();

            if(view->righter->blocks[0][1]==view->lefter->blocks[0][0]){
                R();U_();R();U();R();U();R();U_();R_();U_();R();R();
            }
            if(view->lefter->blocks[0][1]==view->righter->blocks[0][0]){
                R();U_();R();U();R();U();R();U_();R_();U_();R();R();
            }
        }
        else{
            if(view->blocks[0][1]==view->righter->blocks[0][1]){
                L();L();R();R();    D();
                L();L();R();R();    U();
                L();R_();   F();F();
                L();L();R();R();    B();B();
                L();R_();   U();U();
            }
            else{
                L();L();R();R();    D();
                L();L();R();R();    U();U();
                L();L();R();R();    D();
                L();L();R();R();
            }
        }
    }
    if(view->righter->blocks[0][1]==view->blocks[1][1])U();
    if(view->lefter->blocks[0][1]==view->blocks[1][1])U_();
    if(view->righter->righter->blocks[0][1]==view->righter->blocks[1][1]){U();U();}
}
bool cube::level_3_is_sorted()
{
    face *check=view;
    for(;;check=check->righter){
        if(check->blocks[0][0]==check->blocks[0][1]&&check->blocks[0][0]==check->blocks[0][2]){
            if(check->righter==view)break;
            continue;
        }
        else return false;
    }
    return true;
}
bool cube::need_step_0()
{
    face *check=view;
    if(check->blocks[0][0]==check->blocks[0][2]){
        if(check->righter->blocks[0][0]==check->righter->blocks[0][2]){
            if(check->lefter->blocks[0][0]==check->lefter->blocks[0][2]){
                if(check->lefter->lefter->blocks[0][0]==check->lefter->lefter->blocks[0][2])
                    return false;
            }
        }
    }
    return true;
}
bool cube::have_one_sorted_color()
{
    face *check=view;
    for(;;check=check->righter){
        if(check->blocks[1][0]==check->blocks[1][1]&&check->blocks[1][0]==check->blocks[1][2])return true;
        if(check->righter==view)break;
    }
    return false;
}

int main()
{
    cube Rubik;
    Rubik.cross_on_bottom();
    Rubik.finish_bottom();
    Rubik.sort_level_1();
    Rubik.finish_level_2();
    Rubik.cross_on_top();
    Rubik.finish_top();
    Rubik.sort_level_3();
    cout<<endl;
    if(Rubik.restored())cout<<"Rubik's Cube is restored."<<endl;
    return 0;
}





/*     //在此处编辑输入数据
GORBRGWRR
YBBROGYWR
WGOYBOBYB
GRBWGYGOG
RWOOYGWWY
OBWBWYYRO
//*/




















