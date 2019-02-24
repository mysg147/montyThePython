#include <stdio.h>
#include<stdlib.h>
struct snake{
  int x,y;
  char val;
  struct snake *next;
};
struct food{
  int x,y;
  char eat;
};
struct mine{
  int x,y;
  char eat;
};
struct wall{
    char val;
    int x,y;
};
struct wall *w1[3],*w2[3];
int score=0,level=1;
int randoms(){
    
        int num = rand() %9;
            return num;
}
int check(struct snake *start,int a,int b){
    struct snake *ptr=start;
    while(ptr!=NULL){
        if(ptr->x==a&&ptr->y==b)return 0;
        ptr=ptr->next;
    }
    return 1;
}
int checkMine(struct snake *start,struct food *f,int a,int b){
    struct snake *ptr=start;
    while(ptr!=NULL){//checking for no snake
        if(ptr->x==a&&ptr->y==b)return 0;
        ptr=ptr->next;
    }
    if(f->x==a&&f->y==b)return 0;//checking for no food
    return 1;
}
int checkWall(struct snake *start,struct food *f,int a,int b){
    struct snake *ptr=start;
    while(ptr!=NULL){//checking for no snake
        if((ptr)->x==a&&(ptr)->y==b)return 0;
        ptr=(ptr)->next;
    }
    if((f)->x==a&&(f)->y==b)return 0;//checking for no food
    return 1;
}
void createWall(struct snake *head,struct food *f){
    struct snake *ptr=head;

    for(int i=0;i<3;i++)w1[i]=(struct wall*)malloc(sizeof(struct wall*));
    struct food *f1=f;
    int a,b,i;
    a=randoms();
    b=randoms();
    int flag=0;
    while(1){
        flag=0;
        while(!checkWall(head,f,a,b)){
            a=randoms();
            b=randoms();
        }
        for(i=0;i<3;i++){
            w1[i]->x=a;
            w1[i]->y=b;
            w1[i]->val='w';
            
            a=a+1;
            if(a>9){
                flag++;
                break;
            }
            else if(!checkWall(head,f,a,b)){
                flag++;
               break;
            }
        }
        if(flag==0)break;
    }
      
}
void setWall(char board[10][10]){
    for(int i=0;i<3;i++){
        board[w1[i]->x][w1[i]->y]='w';
    }
}
struct snake* createSnake(struct snake *head,int a,int b){
  struct snake *n=(struct snake*)malloc(sizeof(struct snake)),*ptr;
  n->x=a;
  n->y=b;
  n->val='y';
  n->next=NULL;
  if(head==NULL){
    n->val='a';
    head=n;
  }//creating head
  else{
    ptr=head;
    while(ptr->next!=NULL)ptr=ptr->next;
    if(ptr!=head)ptr->val='#';
    ptr->next=n;
  }//creating body
  return head;
}
struct food* createFood(struct food *f,int a,int b){
  f->x=a;
  f->y=b;
  f->eat='x';
  return f;
}
struct mine* createMine(struct mine *m,int a,int b){
  m->x=a;
  m->y=b;
  m->eat='m';
  return m;
}
void setSnakeOnBoard(struct snake *head,char board[10][10]){
  struct snake *ptr=head;
  int i,j;
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      board[i][j]='_';
    }
  }
  //putting snake on board
  while(ptr!=NULL){
    board[ptr->x][ptr->y]=ptr->val;
    ptr=ptr->next;
  }
}
void setFoodOnBoard(struct food *f,char board[10][10]){
    //putting food on board
  board[f->x][f->y]=f->eat;
}
void setMineOnBoard(struct mine *m[4],char board[10][10]){
    //putting food on board
    if(level==2) board[m[0]->x][m[0]->y]='m';
    if(level>=3&&level<5){
        for(int i=0;i<4;i++)board[m[i]->x][m[i]->y]='m';
    }
}
struct snake* move(struct snake *head,char m,struct food *f,struct mine *min[4]){
    struct snake *n=(struct snake*)malloc(sizeof(struct snake));
    if(m=='q'||m=='l'||m=='r'||m=='u'||m=='d'){
    if(m=='q'){
        //saveGame();
        exit(0);
    }
    if(m=='l'){
        n->x=head->x;
        n->y=head->y-1;
        if(n->y < 0){
            if(level==4){
                printf("Game over");
                exit(0);
            }
            n->y=9;
        }
    }
    else if(m=='r'){
        n->x=head->x;
        n->y=head->y+1;
        if(n->y >9){
            if(level==4){
                printf("Game over");
                exit(0);
            }
            n->y=0;
        }
    }
    else if(m=='u'){
        n->x=head->x-1;
        n->y=head->y;
        if(n->x<0){
            if(level==4){
                printf("Game over");
                exit(0);
            }
            n->x=9;
        }
    }
    else if(m=='d'){
        n->x=head->x+1;
        n->y=head->y;
        if(n->x>9){
            if(level==4){
                printf("Game over");
                exit(0);
            }
            n->x=0;
        }
    }
    if(level==2 &&n->x==min[0]->x&&n->y==min[0]->y){//a mine preset or not
        printf("Game over!");
        exit(0);
    }
    if(level>=3&&level<=5){
        for(int k=0;k<4;k++){
            if(n->x==min[k]->x&&n->y==min[k]->y){
                printf("Game over!");
                exit(0);
            }
        }
    }
    if(level==5){
        for(int i=0;i<3;i++){
            if(n->x == w1[i]->x && n->y ==w1[i]->y){
                printf("Game Over!");
                exit(0);
            }
        }
    }

    if(n->x==f->x && n->y==f->y){
        head->val='#';
        n->val='a';
        n->next=head;
        head=n;
        //system("cls");
    }
    //whether to move
    else if(!(n->x==head->next->x && n->y==head->next->y)){
            struct snake *ptr=head->next;
            while(ptr!=NULL){
                if(n->x==ptr->x&&n->y==ptr->y){
                    printf("\ngame over");
                    exit (0);
                }
                ptr=ptr->next;
            }
        n->next=head;
        n->val='a';
        head->val='#';
        head=n;
        ptr=head;
        while(ptr->next->next!=NULL)ptr=ptr->next;
        ptr->val='y';
        ptr->next=NULL;


    }
    }
    return head;
}
void displayBoard(char board[10][10]){
  int i,j;
  //system("cls");
  printf("controls -l,r,u,d\nscore= %d\n",score);
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      printf("%c ",board[i][j]);
    }printf("\n");
  }
}
void readStr(char* str, struct food **f, struct snake **head){
    for(int i=0;str[i]!='\0';i++){
            int j=0,flag,no,p[2];
        if(str[i]=='f'){//if its food
                i++;
            for(;str[i]!=';'&&str[i]!='\0';i++){//till last node of food
                        flag=0;
                        no=0;
                for(;str[i]!=',' && str[i]!=';' && str[i]!='\0';i++){//till next food coordinate
                    if(str[i]>=48 && str[i]<=57){
                            no=no*10+str[i]-48;
                            flag++;
                    }
                }
                if(flag > 0){
                    p[j]=no;
                    j++;}
                    if(str[i]==';')break;
            }
          *f=createFood(*f,p[0],p[1]);
        }
        else if(str[i]=='s'){
          i++;//if it is snake
            for(;str[i]!=';'&&str[i]!='\0';i++){//till last node of snake node
                        flag=0;
                        no=0;
                for(;str[i]!=',' && str[i]!=';' && str[i]!='\0';i++){//till next food coordinate
                    if(str[i]>=48 && str[i]<=57){
                            no=no+str[i]-48;
                            flag++;
                    }
                }
            if(flag > 0){
                    p[j]=no;
                    j++;}

                    if(str[i]==';')break;
            }
          *head=createSnake(*head,p[0],p[1]);
        }
    }
}

int main()
{
	struct snake *head=NULL;
  	struct food *f;
    struct mine *min[4];
  	char board[10][10]={'_'};
    f=(struct food *)malloc(sizeof(struct food));
    for(int i=0;i<4;i++)min[i]=(struct mine *)malloc(sizeof(struct mine));
    //puts in value of snake in board
    int n=15,a,b,flag=1,i,p[2],j,no,flag2=1;
    char m,c;
    //ask choice
    printf("press 'c' to continue previous game and 'n' to start new game\n");
    c=getchar();
    char str[]="f,5,7; s,0,3,a; s,1,3,#; s,1,4,#; s,2,4,#; s,2,3,y;";
    //if continued put in the same value or create a new snake
    if(c=='c'){

        readStr(str,&f,&head);
        setSnakeOnBoard(head,board);
        setFoodOnBoard(f,board);
        displayBoard(board);
    }
    else if(c=='n'){
  	//creating new snake;
        head=createSnake(head,0,0);
        head=createSnake(head,1,0);
        head=createSnake(head,2,0);
        f=createFood(f,3,6);
        setSnakeOnBoard(head,board);
        setFoodOnBoard(f,board);
        displayBoard(board);
    }
    while(1){//whether food is already present or not
        if(flag==0){
            a=randoms();
            b=randoms();
            while(!check(head,a,b)){
                a=randoms();
                b=randoms();
            }
            f=createFood(f,a,b);
            setFoodOnBoard(f,board);
            displayBoard(board);
        }


        //pick the movement
        printf("enter move ");
        scanf("%*c%c",&m);
        //system("cls");
        //m=getchar();
        head=move(head,m,f,min);//move accordingly

        //if food eaten or not
        if(head->x==f->x && head->y==f->y){
            flag=0;
            setSnakeOnBoard(head,board);
            score++;
            if(score==20){//level 2
                printf("\nWelcome to level 2\n");
                level=2;
                flag2=0;
                if(level==2&&flag2==0){
                    a=randoms();//creating mine
                    b=randoms();
                    while(!checkMine(head,f,a,b)){
                        a=randoms();
                        b=randoms();
                    }
                min[0]=createMine(min[0],a,b);
               // setMineOnBoard(min,board);
                flag2++;
                }
            }
            if(score==40){//level 3
                printf("\nWelcome to level 3 \n");
                level=3;
                for(int k=0;k<4;k++){
                    a=randoms();//creating multiple mines
                    b=randoms();
                    while(!checkMine(head,f,a,b)){
                        a=randoms();
                        b=randoms();
                    }
                min[k]=createMine(min[k],a,b);
                //setMineOnBoard(min,board);
                }
            }
            if(score==60){//level 4
                level=4;
                printf("\nWelcome to level 4\nDo not touch the walls\n");
            }
            if(score==80){//level 5
                level=5;
                printf("\nWelcome to level 5\nDo not touch the walls\n ");
                createWall(head,f);
            }
            if(score==100){
                printf("You win!");
                exit(0);
            }
        }
        else {
            setSnakeOnBoard(head,board);//puts in value of snake in board
            setFoodOnBoard(f,board);
            flag=1;
        }
        if(level>=2 && level<5)setMineOnBoard(min,board);
        if(level==5)setWall(board);
        displayBoard(board);//displays the snake

    }
  	return 0;
}
