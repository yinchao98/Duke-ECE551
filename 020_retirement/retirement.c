#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months; // the number of months it is applicable to
  double contribution; // how many dollars are contributed
  double rate_of_return; // rate of the returns
};

typedef struct _retire_info retire_info;

double computeBalance (double initial, int startAge, retire_info retireInfo) {
  int ageYear = startAge / 12;
  int ageMonth = startAge % 12;
  double accountBalance = initial;
  for(int i = 0; i < retireInfo.months; i++) {
    ageYear = (startAge + i) / 12;
    ageMonth = (startAge + i ) % 12;
    printf("Age %3d month %2d you have $%.2lf\n", ageYear, ageMonth, accountBalance);
    accountBalance += accountBalance * (retireInfo.rate_of_return / 12) + retireInfo.contribution;
  }
  return accountBalance;
}

void retirement (int startAge,   //in months
                       double initial, //initial savings in dollars
                       retire_info working, //info about working
                       retire_info retired) //info about being retired
{
  double accountBalance;
  accountBalance = computeBalance(initial, startAge, working);
  accountBalance = computeBalance(accountBalance, (startAge + working.months), retired);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);

  return EXIT_SUCCESS;
}
