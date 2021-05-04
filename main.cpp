#include <iostream>
#include <string>
#include <stdio.h>
#include <cctype>
#include <math.h>
#include <stdlib.h>

using namespace std;

string qwerty(int, string);
string rot13(int, string);
string caeser(int, string);
string affine(int, string);
int mod(int, int);
int modInverse(int, int);
int gcd(int, int);
void ed_message(int, string);
// int continue_choice();

int main () {

    int ed_choice, cipher_choice, conti = 0;
    string input = "", output = "";

    cout << "*******Welcome to CrptoPad*******\n";
    cout << "\nSelect to encrypt or decrypt a message :";
    cout << "\n1.Encrypt a message.";
    cout << "\n2.Decrypt a message.";
    cout << "\nYour Choice : ";
    cin >> ed_choice;

    if (ed_choice == 1)
        cout << "Select the cipher to encrypt.\n";
    else if (ed_choice == 2) 
        cout << "Select the cipher to decrypt.\n";
    else {
        while (ed_choice < 1 || ed_choice > 2) {
        cout << "Enter a valid choice!";
        cout << "\nYour Choice : ";
        cin >> ed_choice;
        }
    }

    do {
        cout << "1.Qwerty\n2.Rot13\n3.Caeser\n4.Affine\n5.Exit";
        cout << "\nEnter your choice : ";
        cin >> cipher_choice;
        cin.ignore();
        if (cipher_choice > 0 && cipher_choice < 5) {
            cout << "Enter your message : ";
            getline(cin, input);
        }
        switch (cipher_choice) {
            case 1:
                output = qwerty(ed_choice, input);
                ed_message(ed_choice, output);
//                conti = continue_choice();
                break;
            case 2:
                output = rot13(ed_choice, input);
                ed_message(ed_choice, output);
//                conti = continue_choice();
                break;
            case 3 :
                output = caeser(ed_choice, input);
                ed_message(ed_choice, output);
//                conti = continue_choice();
                break;
            case 4:
                output = affine(ed_choice, input);
                ed_message(ed_choice, output);
//                conti = continue_choice();
                break; 
            case 5:
                exit(0);
                break; 
            default:
                cout << "\nThere's an option to exit too. Don't press keys unnecessarily.";
                break;
        }
    }while (cipher_choice > 0 && cipher_choice <= 5);

    return 0;
}

void ed_message(int choice, string output) {
    if(choice == 1) {
        cout << "Encrypting your message...";
        cout << "\nEncryption Successful!";
        cout << "\nYour Encrypted Message : " << output << endl;
    }
    else {
        cout << "Decrypting your message...";
        cout << "\nDecryption Successful!";
        cout << "\nYour Decrypted Message : " << output << endl;
    }
    return;
}

int mod(int a, int b)
{
    return a - b * floor((double)a / (double)b);
}

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1;
}

int gcd(int n1, int n2)
{
    int greater, lesser, gc = 0;
    if (n1 > n2) {
        greater = n1;
        lesser = n2;
    }
    else {
        greater = n2;
        lesser = n1;
    }
    for (int i = 1; i < greater; i++) {
        if (mod(n1, i) == 0 && mod(n2, i) == 0)
            gc = i;
    }
    return gc;
}

string qwerty(int ch, string input) {
    char key[26] = { 's','n','v','f','r','g','h','j','o','k','l','a','z','m','p','q','w','t','d','y','i','b','e','c','u','x' };
    char c = input[0];
    string output = "";
    int i = 0;

    if (ch == 1) {
        while (c != '\0') {
            if (isalpha(c)) {
                if (isupper(c)) {
                    c = (c - 'A') % 26;
                    output += toupper(key[c]);
                }
                else {
                    c = (c - 'a') % 26;
                    output += key[c];
                }
            }
            else {
                output += c;
            }
            i++;
            c = input[i];
        }
    }

    if (ch == 2) {
        while (c != '\0') {
            int index = 0, j = 0;
            char temp = tolower(c);

            while (temp != key[j]) {
                j++;
            }
            index = j;

            if (isalpha(c)) {
                if (isupper(c)) {
                    c = 'A' + index;
                    output += c;
                }
                else {
                    c = 'a' + index;
                    output += c;
                }
            }
            else {
                output += c;
            }
            i++;
            c = input[i];
        }
    }
    
    return output;
}

string rot13(int ch, string input) {
    char c = input[0];
    string output = "";
    int i = 0;

    while (c != '\0') {
        if (isalpha(c)) {
            if (isupper(c)) {
                c = (c - 'A' + 13) % 26 + 'A';
                output += c;
            }
            else {
                c = (c - 'a' + 13) % 26 + 'a';
                output += c;
            }
        }
        else {
            output += c;
        }
        i++;
        c = input[i];
    }

    return output;
}

string caeser (int ch, string input) {
    int shift, i = 0;
    char c = input[0];
    string output = "";
    cout << "\nEnter the value of shift : ";
    cin >> shift;
    (ch == 1) ? shift = (shift * 1) : shift = (shift * -1);

    while (c != '\0') {
        if (isalpha(c)) {
            if (isupper(c)) {
                c = mod(c - 'A' + shift, 26) + 'A';
                output += c;
            }
            else {
                c = mod(c - 'a' + shift, 26) + 'a';
                output += c;
            }
        }
        else {
            output += c;
        }
        i++;
        c = input[i];
    }

    return output;
}

string affine (int ch, string input) {
    int a, b, g, temp, i = 0;
    char c = input[0];
    string output = "";
    cout << "\nNote : You need two values ([a] and [b]) to use this encryption.";
    cout << "\nNote : [a] and [26] must be relatively prime.";
    cout << "Enter the values of a and b : ";
    cin >> a >> b;
    if ( a == 1) {
        while (a != 1) {
            cout << "[a] must be greater than 1.";
            cout << "Enter another value for [a] : ";
            cin >> a;
        }
    }
    g = gcd(a, 26);

    if (g == 1) {
        if (ch == 1) {
            while (c != '\0') {
                if (isalpha(c)) {
                    if (isupper(c)) {
                        temp = (c - 'A') % 26;
                        c = mod((a * temp) + b, 26) + 'A';
                        output += c;
                    }
                    else {
                        temp = (c - 'a') % 26;
                        c = mod((a * temp) + b, 26) + 'a';
                        output += c;
                    }
                }
                else {
                    output += c;
                }   
                i++;
                c = input[i];
            }
        }
        else {
            while (c != '\0') {
                if (isalpha(c)) {
                    int inverse = modInverse(a, 26);
                    if (isupper(c)) {
                        temp = (c - 'A') % 26;
                        c = mod((temp - b) * inverse, 26) + 'A';
                        output += c;
                    }
                    else {
                        temp = (c - 'a') % 26;
                        c = mod((temp - b) * inverse, 26) + 'a';
                        output += c;
                    }
                }
                else {
                    output += c;
                }   
                i++;
                c = input[i];
            }
        }
    }
    else 
        cout << "[a] and [26] are not relatively prime!\n";
    
    return output;
}