#include <stdio.h>
//DO EDYTOWANIA
const double L[3][3] = {
        {0.0, 0.0, 0.0}, // L[0] - NIEWAŻNE
        {1.0, 0.9, 0.1}, // 1 zostaw 1.0
        {1.0, 0.1, 1.0} // 1 zostaw 1.0
};
const int d[3] = {99, 1, 0}; // d[0] - NIEWAŻNE
const double wektor_wag_poczatkowych[3] = {-0.1, -0.1, -0.2};
const int n = 2;
const double wspolczynnik_uczenia = 0.1;
const int K = 2;

//NIE RUSZAJ
int t = 0;
int k = 1;
int lpd = 0;
double wx[3];
int ostatnia_wartosc_otrzymana;

void printLines();
void step1();
void step2();
void step3();
void step4();
void step5();
void calculatePoints(const double w[3]);
double calculateFJump(const double w[3], const double x[3]);

int main(){

    for(int i = 0; i < 3; i ++){
        wx[i] = wektor_wag_poczatkowych[i];
    }

    printLines();
    step1();

    while(lpd != n){
        printLines();
        step2();
        step3();
        step4();
        step5();
    }

}

void step1(){
    printf("KROK 1: w(%d) = [%.2f, %.2f, %.2f]^T\n", t, wx[0], wx[1], wx[2]);
    calculatePoints(wx);
}

void step2(){
    printf("KROK 2(%d): X(%d) = [%.2f, %.2f, %.2f]^T\n", t, k, L[k][0], L[k][1], L[k][2]);
}

void step3(){
    double fjump = calculateFJump(wx, L[k]);
    int fjumpoutput;
    if(fjump >= 0)
        fjumpoutput = 1;
    else
        fjumpoutput = 0;

    printf("KROK 3(%d): y(%d) = fskok([%.2f, %.2f, %.2f] * [%.2f, %.2f, %.2f]^T) = fskok(%.2f) = %d", t, k, wx[0], wx[1], wx[2], L[k][0], L[k][1], L[k][2],
           fjump, fjumpoutput);

    if(fjumpoutput == d[k]){
        lpd++;
        printf(" = d(%d) = %d -> lpd = lpd + 1 = %d\n", k, d[k], lpd);
    }else{
        lpd = 0;
        printf(" != d(%d) = %d -> lpd = %d\n", k, d[k], lpd);
    }
    ostatnia_wartosc_otrzymana = fjumpoutput;
}

void step4(){
    double wxtemp[3];
    for(int i = 0; i < 3; i++){
        wxtemp[i] = wx[i];
    }
    double tempy[3];
    for(int i = 0; i < 3; i++){
        tempy[i] = L[k][i];
        tempy[i] = wspolczynnik_uczenia * (d[k] - ostatnia_wartosc_otrzymana) * tempy[i];
    }

    for(int i = 0; i < 3; i++){
        wx[i] = wx[i] + tempy[i];
    }
    if(ostatnia_wartosc_otrzymana == d[k]){
        printf("KROK 4(%d): w(%d) = w(%d) = [%.2f, %.2f, %.2f]^T\n", t, t, t-1, wx[0], wx[1], wx[2]);
    }else{
        printf("KROK 4(%d): w(%d) = [%.2f, %.2f, %.2f]^T + %.2f * (%d - %d) * [%.2f, %.2f, %.2f] = [%.2f, %.2f, %.2f]^T\n", t, t,
               wxtemp[0], wxtemp[1], wxtemp[2], wspolczynnik_uczenia, d[k], ostatnia_wartosc_otrzymana,
               tempy[0], tempy[1], tempy[2], wx[0], wx[1], wx[2]);
    }
    calculatePoints(wx);
}

void step5(){
    t++;
    printf("KROK 5(%d): LPD = %d, t = t + 1 = %d, ", t-1, lpd, t);
    if(k + 1 > K){
        printf("k = k + 1 > K -> k = 1 ");
        k = 1;
    }else{
        k++;
        printf("k = k + 1 = %d ", k);
    }
    if(lpd != n)
        printf("Przejscie do KROK 2(%d)\n", t);
    else
        printf("KONIEC ALGORYTMU LPD = K = %d\n", lpd);
}

void printLines(){
    printf("\n");
    for(int i = 0; i < 40; i++)
        printf("-");

    printf("\n\n");
}

void calculatePoints(const double w[3]){
    double P1;
    double P2;
    if(ostatnia_wartosc_otrzymana != d[k]){
        if (w[0] != 0 && w[1] != 0 && w[2] != 0) {
            P1 = -(w[0] / w[1]);
            P2 = -(w[0] / w[2]);
	    printf("x10 = -(w[0]/w[1]) = -(%.2f/%.2f) = %.2f\n", w[0], w[1], P1);
	    printf("x20 = -(w[0]/w[2]) = -(%.2f/%.2f) = %.2f\n", w[0], w[2], P2);
            printf("P1(%.2f, 0), P2(0, %.2f) - linia ukośna\n", P1, P2);
        } else if (w[0] != 0 && w[1] == 0 && w[2] != 0) {
            P2 = -(w[0] / w[2]);
	    printf("x10 nie istnieje");
	    printf("x20 = -(w[0]/w[2]) = -(%.2f/%.2f) = %.2f\n", w[0], w[2], P2);
            printf("P1 nie istnieje, P2(0, %.2f) - linia pozioma\n", P2);
        } else if (w[0] != 0 && w[1] != 0 && w[2] == 0) {
            P1 = -(w[0] / w[1]);
	    printf("x10 = -(w[0]/w[1]) = -(%.2f/%.2f) = %.2f\n", w[0], w[1], P1);
	    printf("x20 nie istnieje");
            printf("P1(%.2f, 0), P2 nie istnieje - linia pionowa\n", P1);
        } else if (w[0] == 0 && w[1] != 0 && w[2] != 0) {
            printf("P1(0, 0), P2(0, 0) - linia ukośna\n");
        } else if (w[0] == 0 && w[1] == 0 && w[2] != 0) {
            printf("P1(c, 0), P2(0, 0) - linia pozioma\n");
        } else if (w[0] == 0 && w[1] != 0 && w[2] == 0) {
            printf("P1(0, 0), P2(0, c) - linia pionowa\n");
        }
    }else{
        printf("P1(%d) = P1(%d), P2(%d) = P2(%d)\n", t, t-1, t, t-1);
    }
}

double calculateFJump(const double w[3], const double x[3]){
    double output = 0;
    for(int i = 0; i < 3; i++){
        output = output + (w[i] * x[i]);
    }

    return output;
}
