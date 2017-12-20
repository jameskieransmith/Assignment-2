//
//  main.cpp
//  Assignment 2
//
//  Created by Kieran Smith on 20/12/2017.
//  Copyright © 2017 Kieran Smith. All rights reserved.
//
// The encryption program in C++ and ASM with a very simple encryption method - it simply adds 1 to the character.
// The encryption method is written in ASM. You will replace this with your allocated version for the assignment.
// In this version parameters are passed via registers (see 'encrypt' for details).
// Filename: "CSA Assignment-2 2017/18 - Encryption Original with ASM.cpp"
// Based on work by A. Oram (SHU)
// Last revised Dec 2017 by Deepayan Bhowmik


#define StudentName "James Smith"

//  *** PLEASE CHANGE THE NAME IN QUOTES ABOVE TO YOUR NAME  ***
//  *** KEEP ALL COMMENTS UP-TO-DATE. COMMENT USEFULLY ALL CODE YOU PRODUCE. ***

#define MAXCHARS 6        // feel free to alter this, but 6 is the minimum

using namespace std;
//#include <conio.h>        // for kbhit
//#include <windows.h>
#include <string>       // for strings
#include <fstream>        // file I/O
#include <iostream>        // for cin >> and cout <<
#include <iomanip>        // for fancy output
//#include "TimeUtils.h"  // for GetTime, GetDate, etc.

#define dollarchar '$'  // string terminator

char OChars[MAXCHARS],
EChars[MAXCHARS],
DChars[MAXCHARS] = "Soon!";    // Global Original, Encrypted, Decrypted character strings

//----------------------------- C++ Functions ----------------------------------------------------------

void get_char(char& a_character)
{
    cin >> a_character;
    while (((a_character < '0') | (a_character > 'z')) && (a_character != dollarchar))
    {
        cout << "Alphanumeric characters only, please try again > ";
        cin >> a_character;
    }
}
//-------------------------------------------------------------------------------------------------------------

void get_original_chars(int& length)
{
    char next_char;
    length = 0;
    
    get_char(next_char);
    
    while ((length < MAXCHARS) && (next_char != dollarchar))
    {
        OChars[length++] = next_char;
        get_char(next_char);
    }
}

//---------------------------------------------------------------------------------------------------------------
//----------------- ENCRYPTION ROUTINES -------------------------------------------------------------------------
void encrypt_chars(int length)
{
    char temp_char;                        // Character temporary store
    
    for (int i = 0; i < length; i++)    // Encrypt characters one at a time
    {
        temp_char = OChars[i];            // Get the next char from Original Chars array
        // Note the lamentable lack of comments below!
        __asm {                            //
            push   rax                    // push the value of the EAX onto a stack
            push   rcx                    // push the value of the ECX onto the stack
            //
            movzx  rcx, temp_char        // move the value of the temporary character into ECX with zero extension
            
            //call   encrypt_nn            // go to the subroutine "encrypt_nn"
            
            mov rax, rcx        // get character from ecx and store in eax
            add rax, 7        // add 7 to the value of the character
            
            
            
            mov    temp_char, al        // store the last byte of the eax in temp_char
            //
            pop    rcx                    // pop the value ontop of the stack into the ECX
            pop    rax                    // pop the value ontop of the stack (last value in stack) into the EAX
        }
        EChars[i] = temp_char;            // Store encrypted char in the Encrypted Chars array
    }
    return;
    
    
    // Encrypt subroutine. You should modify the encryption routine based on you're allocation and
    // overwrite this initial, simple, version. Ensure you change the �call� above to use the
    // Inputs: register EAX = 32-bit address of Ekey,
    //                    ECX = the character to be encrypted (in the low 8-bit field, CL).
    // Output: register EAX = the encrypted value of the source character (in the low 8-bit field, AL).
    // REMEMBER TO UPDATE THESE COMMENTS AS YOU DO THE ASSIGNMENT. DELETE OLD/STALE COMMENTS.
    
    //__asm {
        
    //encrypt_nn:
        
    //}
    
    //--- End of Assembly code
}
// end of encrypt_chars function
//---------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------
//----------------- DECRYPTION ROUTINES -------------------------------------------------------------------------
//
void decrypt_chars(int length)
{
    // My decryption routine in here

    return;
}
// end of decrypt_chars function
//---------------------------------------------------------------------------------------------------------------


int main(void)
{
    int char_count(0);  // The number of actual characters entered (upto MAXCHARS limit).
    
    cout << "\nPlease enter upto " << MAXCHARS << " alphanumeric characters followed by '$' char:  \n\n";
    get_original_chars(char_count);
    
    ofstream EDump;
    EDump.open("EncryptDump.txt", ios::app);
    EDump << "\n\nCSA Encryption program results (" << StudentName << ") :";
    time_t now = time(0);
    tm* localtm = localtime(&now);
    EDump << "\nDate: " << asctime(localtm) << endl;
    
    // Display and save initial string
    cout << "\n\nOriginal string =  " << OChars << "\tHex = ";
    EDump << "\n\nOriginal string =  " << OChars << "\tHex = ";
    for (int i = 0; i < char_count; i++)
    {
        cout << hex << setw(2) << setfill('0') << ((int(OChars[i])) & 0xFF) << "  ";
        EDump << hex << setw(2) << setfill('0') << ((int(OChars[i])) & 0xFF) << "  ";
    };
    
    //*****************************************************
    // Encrypt the string and display/save the result
    encrypt_chars(char_count);
    
    cout << "\n\nEncrypted string = " << EChars << "\tHex = ";
    EDump << "\n\nEncrypted string = " << EChars << "\tHex = ";
    for (int i = 0; i < char_count; i++)
    {
        cout << ((int(EChars[i])) & 0xFF) << "  ";
        EDump << ((int(EChars[i])) & 0xFF) << "  ";
    }
    
    //*****************************************************
    // Decrypt the encrypted string and display/save the result
    decrypt_chars(char_count);
    
    cout << "\n\nDecrypted string = " << DChars << "\tHex = ";
    EDump << "\n\nDecrypted string = " << DChars << "\tHex = ";
    for (int i = 0; i < char_count; i++)
    {
        cout << ((int(DChars[i])) & 0xFF) << "  ";
        EDump << ((int(DChars[i])) & 0xFF) << "  ";
    }
    //*****************************************************
    
    cout << "\n\n\n";
    EDump << "\n\n-------------------------------------------------------------";
    EDump.close();

    system("PAUSE");
    return (0);
    
} // end of whole encryption/decryption program --------------------------------------------------------------------



