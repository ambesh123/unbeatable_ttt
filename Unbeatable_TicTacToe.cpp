                      //  @ /\/\ BESH //

#include <bits/stdc++.h>
#define inp_out_work ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define testCase    int T; cin>>T; while(T--)
#define fr(i,n) for(int i=0;i<n;i++)
#define fro(i,s,e) for(int i=s;i<=e;i++)
#define endl '\n'
#define debug(P) cout<<#P<<" = "<<P<<endl;
#define pb push_back
#define FILE freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);


using namespace std;

const int MAXN = 100001;

int ttt[3][3];

int  cpu, player;

bool cpu_wins(){
    for(int i = 0; i < 3; i ++){
        bool wins = 1;
        for(int j = 0; j < 3; j ++)wins = wins && (ttt[i][j] == cpu);
        if(wins)return wins;
        wins = 1;
        for(int j = 0; j < 3; j ++)wins = wins && (ttt[j][i] == cpu);
        if(wins)return wins;
    }

    bool wins = 1;
    for(int i = 0; i < 3; i++)wins = wins && (ttt[i][i] == cpu);
    if(wins)return wins;

    wins = 1;
    for(int i = 0; i < 3; i++)wins = wins && (ttt[i][2-i] == cpu);

    return wins;
}

bool player_wins(){
    for(int i = 0; i < 3; i ++){
        bool wins = 1;
        for(int j = 0; j < 3; j ++)wins = wins && (ttt[i][j] == player);
        if(wins)return wins;
        wins = 1;
        for(int j = 0; j < 3; j ++)wins = wins && (ttt[j][i] == player);
        if(wins)return wins;
    }

    bool wins = 1;
    for(int i = 0; i < 3; i++)wins = wins && (ttt[i][i] == player);
    if(wins)return wins;

    wins = 1;
    for(int i = 0; i < 3; i++)wins = wins && (ttt[i][2-i] == player);

    return wins;
}

bool game_drawn(){  // must be checked after cpu_wins() && player_wins() are false
    for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(ttt[i][j] == 0){
                    return 0;
                }
            }
        }
        return 1;
}

int evaluate_move(int turn){
    if(cpu_wins())return 5;
    if(player_wins())return -5;
    if(game_drawn())return 0;

    if(turn == cpu){
        int mx = -5;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(ttt[i][j] == 0){
                    ttt[i][j] = turn;
                    mx = max(mx, evaluate_move(-turn));
                    ttt[i][j] = 0;
                }
            }
        }
        return mx;
    }
    else{
        int mn = 5;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(ttt[i][j] == 0){
                    ttt[i][j] = turn;
                    mn = min(mn, evaluate_move(-turn));
                    ttt[i][j] = 0;
                }
            }
        }
        return mn;
    }

}

bool make_move(){
    if(cpu_wins()){
        cout<< "You Loose!!\n";
        return false;
    }
    if(player_wins()){
        cout<< "You Won!!\n";
        return false;
    }

    if(game_drawn()){
        cout<< "Match Draw :|";
        return false;
    }

    int tx , ty, mx = -10;

    for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(ttt[i][j] == 0){
                    ttt[i][j] = cpu;
                    int ev = evaluate_move(player);
                    if(ev > mx){
                        mx = ev;
                        tx = i, ty = j;
                    }
                    ttt[i][j] = 0;
                }
            }
        }

        ttt[tx][ty] = cpu;

        return true;
}

char disp(int x){
    switch(x){
        case 0: return ' ';
        case 1: return 'X';
        case -1: return 'O';
    }
}

void display_board(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(i&1){
                if(j&1)cout<< disp(ttt[i>>1][j>>1]);
                else cout<< "|";
            }
            else{
                cout<< "-";
            }
        }
        cout<< endl;
    }
}

bool make_player_move(){

    cout<< "Enter Move ( row and column) : " << endl;
    int r, c;
    cin>>r>>c;

    if(ttt[r][c] == 0){
        ttt[r][c] = player;
        return true;
    }
    else return false;
}

void initialize_board(){
    for(int i = 0; i < 3; i++){
        for(int j =0 ; j < 3; j++)ttt[i][j] = 0;
    }
}

int main(){
    initialize_board();

    cpu = 1;
    player = -1;

    cout<<"Who's first? \n 1. CPU \t 2. Player \n";
    int turn;
    cin>>turn;
    if(turn != cpu)display_board(), make_player_move();

    while(make_move()){
        if(cpu_wins()){
            display_board();
            cout<<"Better Luck Next Time\n"; break;
        }
        else if(game_drawn()){
            cout<< "It's a Draw!!"; break;
        }
        display_board();
        while(!make_player_move())cout<<"Invalid Move!\n";
    }

    return 0;

}
