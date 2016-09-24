
#include<iostream>
#include<stack>
#include<cstdlib>

using namespace std;

struct pos {

	int x;
	int y;
};

void placeQueen(int ,int);
void backTrack();
void lock(int,int,int);

stack <pos> cds;
stack <pos> check;
pos v,k,u;
int col = 0;
int row = 0;
int **a,**b;

int main() {

	int i = 0 ,j = 0;

	cout<<"Enter number of rows and columns:";
	cin>>row>>col;

	a = (int**)malloc(row * sizeof(int *));
	b = (int**)malloc(row * sizeof(int *));

	for(i = 0; i < row; i++) {

		a[i] = (int *)malloc(col * sizeof(int));
	        b[i] = (int *)malloc(col * sizeof(int));
	}

	for(i=0;i<row;i++)
		for(j=0;j<col;j++) {
			b[i][j]=1;
			a[i][j]=0;
		}
	placeQueen(0,0);
	while(!cds.empty()) {
	
		k=cds.top();
		cds.pop();
		cout<<k.x<<" "<<k.y<<"\n";
	}
	
	for(i = 0; i < row; i++) {
		free(a[i]);
		free(b[i]);
	}
	free(a);
	free(b);
	return 0;
}

void placeQueen(int i,int j) {

	if(i==0&&j==col){
		cout<<"No posiible combination";
		return;
	}

	if(i>=row)
		return;

	if(j>=col) {
		backTrack();
		return;
	}

	if(b[i][j]) {

		a[i][j]=1;
		lock(i,j,0);
		v.x=i;
		v.y=j;
		cds.push(v);
		j=0;
		placeQueen(i+1,j);
	}
	else
		placeQueen(i,j+1);
}

void backTrack() {

	k=cds.top();
	cds.pop();
	int m,n;
	m=k.x;
	n=k.y;
	a[m][n]=0;
	lock(m,n,1);
	while(!(cds.empty())) {
	
		u=cds.top();
		cds.pop();
		int bc,mc;
		bc=u.x;
		mc=u.y;
		check.push(u);
		lock(bc,mc,0);
	}
	while(!(check.empty())) {

		u=check.top();
		cds.push(u);
		check.pop();
	}
	placeQueen(m,n+1);
}

void lock(int p,int q,int flag) {

	int e,f;

        e=p;
        f=q;
        while(e<row && f<col) {

                b[e][f]=flag;
                e++;
                f++;
        }

        e=p;
        f=q;
        while(e<row && f>=0) {

                b[e][f]=flag;
                e++;
                f--;
        }

	e=0;
	f=q;

	while(e<row) {
	
		b[e][f]=flag;
		e++;
	}
}
