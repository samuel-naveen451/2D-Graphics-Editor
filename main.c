#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 100

#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

typedef struct {
    int type;
    int x1,y1,x2,y2,x3,y3,r;
} Shape;

Shape objects[MAX_OBJECTS];
int count = 0;

/* ================= BASIC FUNCTIONS ================= */

void clearPicture() {
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++)
            picture[i][j] = EMPTY;
}

void displayPicture() {
    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++)
            printf("%c", picture[i][j]);
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if(x>=0 && x<WIDTH && y>=0 && y<HEIGHT)
        picture[y][x] = PIXEL;
}

/* ================= DRAW FUNCTIONS ================= */

void drawLine(int x1,int y1,int x2,int y2) {
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x1<x2)?1:-1;
    int sy = (y1<y2)?1:-1;
    int err = dx - dy;

    while(1) {
        setPixel(x1,y1);
        if(x1==x2 && y1==y2) break;

        int e2 = 2*err;
        if(e2 > -dy){ err -= dy; x1 += sx; }
        if(e2 < dx){ err += dx; y1 += sy; }
    }
}

void drawRectangle(int x1,int y1,int x2,int y2) {
    for(int x=x1;x<=x2;x++){
        setPixel(x,y1);
        setPixel(x,y2);
    }
    for(int y=y1;y<=y2;y++){
        setPixel(x1,y);
        setPixel(x2,y);
    }
}

void drawCircle(int cx,int cy,int r) {
    int x=0,y=r;
    int d=3-2*r;

    while(x<=y){
        setPixel(cx+x,cy+y);
        setPixel(cx-x,cy+y);
        setPixel(cx+x,cy-y);
        setPixel(cx-x,cy-y);

        setPixel(cx+y,cy+x);
        setPixel(cx-y,cy+x);
        setPixel(cx+y,cy-x);
        setPixel(cx-y,cy-x);

        if(d<0) d += 4*x+6;
        else { d += 4*(x-y)+10; y--; }
        x++;
    }
}

void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3) {
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

/* ================= OBJECT HANDLING ================= */

void addObject() {
    int type;

    printf("Choose shape type:\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    printf("Enter shape type: ");
    scanf("%d",&type);

    objects[count].type = type;

    if(type==1){
        printf("Enter x1 y1 x2 y2: ");
        scanf("%d %d %d %d",
              &objects[count].x1,&objects[count].y1,
              &objects[count].x2,&objects[count].y2);
    }
    else if(type==2){
        printf("Enter top-left x y and bottom-right x y: ");
        scanf("%d %d %d %d",
              &objects[count].x1,&objects[count].y1,
              &objects[count].x2,&objects[count].y2);
    }
    else if(type==3){
        printf("Enter center x y and radius: ");
        scanf("%d %d %d",
              &objects[count].x1,&objects[count].y1,
              &objects[count].r);
    }
    else if(type==4){
        printf("Enter x1 y1 x2 y2 x3 y3: ");
        scanf("%d %d %d %d %d %d",
              &objects[count].x1,&objects[count].y1,
              &objects[count].x2,&objects[count].y2,
              &objects[count].x3,&objects[count].y3);
    }

    printf("Object added with index %d.\n\n", count);
    count++;
}

void redraw() {
    clearPicture();

    for(int i=0;i<count;i++){
        if(objects[i].type==1)
            drawLine(objects[i].x1,objects[i].y1,
                     objects[i].x2,objects[i].y2);

        else if(objects[i].type==2)
            drawRectangle(objects[i].x1,objects[i].y1,
                          objects[i].x2,objects[i].y2);

        else if(objects[i].type==3)
            drawCircle(objects[i].x1,objects[i].y1,
                       objects[i].r);

        else if(objects[i].type==4)
            drawTriangle(objects[i].x1,objects[i].y1,
                         objects[i].x2,objects[i].y2,
                         objects[i].x3,objects[i].y3);
    }
}

/* ================= MAIN ================= */

int main() {
    int choice;

    while(1) {

        printf("2D Graphics Editor\n");
        printf("Canvas size: 80 x 24\n");
        printf("1. Add object\n");
        printf("2. Delete object\n");
        printf("3. Modify object\n");
        printf("4. Display picture\n");
        printf("5. List objects\n");
        printf("0. Exit\n");
        printf("Enter choice: \n");

        scanf("%d",&choice);

        if(choice==1){
            addObject();
        }
        else if(choice==4){
            redraw();
            displayPicture();
            printf("\n");
        }
        else if(choice==0){
            printf("Goodbye.\n");
            break;
        }
    }

    return 0;
}