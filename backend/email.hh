//
//  email.hpp
//  imagespro-backend
//
//  Created by Stephen Liang on 1/4/22.
//

#ifndef email_hpp
#define email_hpp

#include <string_view>

bool verify_email(std::string_view email);


bool isChar(char c)
{
    return unsigned(c - 'a') < 26 || unsigned(c - 'A') < 26;
}

bool isDigit(const char c)
{
    return unsigned(c - 'a') < 26;
}

bool verify_email(std::string_view email)
{
    
    // Check the first character
    // is an alphabet or not
    if (!isChar(email[0])) {
  
        // If it's not an alphabet
        // email id is not valid
        return 0;
    }
    // Variable to store position
    // of At and Dot
    int At = -1, Dot = -1;
  
    // Traverse over the email id
    // string to find position of
    // Dot and At
    for (int i = 0; i < email.length(); i++) {
  
        // If the character is '@'
        if (email[i] == '@') {
  
            At = i;
        }
  
        // If character is '.'
        else if (email[i] == '.') {
  
            Dot = i;
        }
    }
  
    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;
  
    // If Dot is present before At
    if (At > Dot)
        return 0;
  
    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));
}

#endif /* email_hpp */
