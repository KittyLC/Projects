#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Money {
public:
    Money(long dollars, int cents);
    Money(long dollars);
    Money();
    double get_value() const;
    friend istream& operator >>(istream& ins, Money& amount);
    friend ostream& operator <<(ostream& outs, const Money& amount);

private:
    long all_cents;
};
int digit_to_int(char c);

Money::Money(long dollars, int cents) {
    if (dollars * cents < 0) {
        cout << "Illegal values for dollars and cents.\n";
    }
    all_cents = dollars * 100 + cents;
}

Money::Money(long dollars) : all_cents(dollars*100) {}

Money::Money() : all_cents(0) {}

double Money::get_value() const {
    return (all_cents*0.01);
}

int digit_to_int(char c) {
    return (static_cast<int>(c) - static_cast<int>('0'));
}

istream& operator >>(istream& ins, Money& amount) {
    char one_char, decimal_point, digit1, digit2;
    long dollars;
    int cents;
    bool negative;

    ins >> one_char;
    if (one_char == ' ') {
        negative = true;
        ins >> one_char;
    } else
        negative = false;

    ins >> dollars >> decimal_point >> digit1 >> digit2;

    if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2)) {
        cout << "Error illegal form for money input\n";
        exit(1);}
    cents = digit_to_int(digit1)*10 + digit_to_int(digit2);
    amount.all_cents = dollars*100 + cents;
    if (negative)
        amount.all_cents = -amount.all_cents;
    return ins;
}

ostream& operator <<(ostream& outs, const Money& amount) {
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if (amount.all_cents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;
    return outs;
}

class Check {
public:
    Check();
    Check(string chkNo, Money chkAmt, bool chkCashed);
    void setNumber(string no);
    void setAmount(Money amt);
    void setCashed(bool cashd);
    string getNumber();
    Money getAmount();
    bool getCashed();
    friend istream& operator >>(istream& ins, Check& chk);
    friend ostream& operator <<(ostream& outs, const Check& chkInfo);
private:
    string number;
    Money amount;
    bool cashed;
};

Check::Check() :number(""), amount(), cashed(false) {}
Check::Check(string chkNo, Money chkAmt, bool chkCashed) {
    number = chkNo;
    amount = chkAmt;
    cashed = chkCashed;
}

void Check::setNumber(string no) {
    number = no;
}
void Check::setAmount(Money amt){
    amount = amt;
}
void Check::setCashed(bool cashd){
    cashed = cashd;
}
string Check::getNumber() {
    return number;
}
Money Check::getAmount() {
    return amount;
}
bool Check::getCashed() {
    return cashed;
}

istream& operator >>(istream& ins, Check& chk) {
    int cashd;
    string n;
    Money amt;
    while(!(ins >> n) || !(ins >> amt) || !(ins >> cashd)) {
        ins.clear();
        cin.ignore(80,'\n');
        cout << "Error, try again\n";
    }
    cin.ignore(80, '\n');
    chk.number = n;
    chk.amount = amt;
    chk.cashed = cashd;
    return ins;
}

ostream& operator <<(ostream& outs, const Check& chkInfo) {
    outs << "Check no: " << chkInfo.number;
    outs << ", Amount: " << chkInfo.amount << ", ";
    if (chkInfo.cashed) {
        outs << "Cashed";}
    else {
        outs << "Not Cashed";}
    return outs;
}

int main() {
    const int size = 10;
    Check *checks;
    checks = new Check[size];
    int count = 0;
    double initBal, deposit, CheckAmts = 0, depositAmts = 0, cashedAmts = 0;
    double deposits[size];
    char ans;
    vector<string> uncashedChecks, cashedChecks;

    cout << "Enter initial account balance:\n";
    cin >> initBal;

    cout << "Enter deposit amount (-1 to stop):\n";
    cin >> deposit;

    while (count<size && deposit !=-1) {
        deposits[count] = deposit;
        count++;
        cin >> deposit;
    }
    for (int i = 0; i<count; i++) {
        initBal = initBal + deposits[i];
        depositAmts = depositAmts + deposits[i];
    }
    count = 0;
    do {
        cout << "\n Enter check details (number, amount, cashed):\n";
        cin >> checks[count];
        cout << "\n Would you like to enter another check? y/n:\n";
        cin >> ans;
        count++;
    } while (ans == 'y' || ans == 'Y');

    for (int i = 0; i<size; i++) {
        double value = (checks[i].getAmount()).get_value();
        if (checks[i].getCashed()) {
            initBal = initBal - value;
            cashedAmts = cashedAmts + value;
            cashedChecks.push_back(checks[i].getNumber());
        }
        else if (checks[i].getNumber() != "")
            uncashedChecks.push_back(checks[i].getNumber());
        CheckAmts = CheckAmts + value;
    }

    sort(uncashedChecks.begin(), uncashedChecks.end());
    sort(cashedChecks.begin(), cashedChecks.end());

    cout << "\nThe final balance is: $" << initBal << endl;
    cout << "Total amount of deposits made: $" << depositAmts << endl;
    cout << "Total amount of all checks: $" << CheckAmts << endl;
    cout << "Total amount of checks cashed: $" << cashedAmts << endl;

    if (!cashedChecks.empty()) {
        cout << "Sorted list of cashed checks: " << endl;
        for (int i=0; i<cashedChecks.size(); i++)
            cout << cashedChecks[i] << ", ";
        cout << endl;
    }
    if (!uncashedChecks.empty()) {
        cout << "Sorted list of ucashed checks: " << endl;
        for (int i=0; i<uncashedChecks.size(); i++)
            cout << uncashedChecks[i] << ", ";
        cout << endl;
    }

    delete[] checks;
    return  0;
}