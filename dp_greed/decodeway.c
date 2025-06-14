#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//leetcode 91
int numDecodings(char* s) {
    int len = strlen(s);
    if(len == 0 || (len == 1 && s[0] == '0')) return 0;
    if(len == 1) return 1;

    int* c = (int*) malloc(sizeof(int) * len);

    int subnumber;
    //base case
    c[0] = (s[0] - '0' != 0) ? 1 : 0;
    subnumber = 10 * (s[0] - '0') + (s[1] - '0');
    if(s[1] == '0' && subnumber > 26) return 0;//301,401...

    if(s[1] == '0'){
        c[1] = c[0];
    }
    else{
        c[1] = (subnumber <= 26 && subnumber > 10) ? c[0] + 1 : c[0];
    }
    //recursive structure
    for(int i = 2; i < len; i++){
        subnumber = 10 * (s[i-1] - '0') + (s[i] - '0');
        if(s[i] == '0' && s[i-1] == '0'){
            return 0;
        }
        else if(s[i] == '0'){
            if(subnumber <= 26){
                c[i] = c[i-2];
            }
            else{
                return 0;//33407
            }
        }
        else{//s[i] != '0'
            c[i] = (subnumber <= 26 && subnumber > 10) ? c[i-2] + c[i-1] : c[i-1];
        }
        
    }

    int result = c[len - 1];
    return result;
}
/** Note:
 *  We may encounter leading 0, and consecutive 0
 *  1. a big problem 06 != 6 
 *  2. 0 has no mapping
 *  3. other cases: 01, 10, 101, 201, 301, 1001, 2001,
 */

/** The following concept does not take 0 into consideration, but the above codes does
 * 
 */

//a digit look like: 1
//a new digit 2 is added, we consider subproblems 2 and 12
//boundary if 12 <= 26
//a new digit 3 is added, we consider 12,3 1,23
//c[i] = c[i-2] + c[i-1]


#define TEST(name) test = name;
#define ASSERT(expr) \
  do { \
    if (!(expr)) { \
      fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #expr, __FILE__, __LINE__); \
      exit(1); \
    } else { \
      putchar('.'); \
    } \
  } while(0)

//unit test
void test_basic_cases() {
    ASSERT(numDecodings("12") == 2);      // "AB", "L"
    ASSERT(numDecodings("226") == 3);     // "BZ", "VF", "BBF"
    ASSERT(numDecodings("0") == 0);       // invalid
    ASSERT(numDecodings("10") == 1);      // "J"
    ASSERT(numDecodings("101") == 1);     // "JA"
    ASSERT(numDecodings("207") == 1);     // "BG"
    ASSERT(numDecodings("301") == 0);     // invalid
    ASSERT(numDecodings("1001") == 0);    // invalid
    ASSERT(numDecodings("1") == 1);       // "A"
    ASSERT(numDecodings("") == 0);        // empty
}


int main(){
    const char* test = "";

    TEST("basic_cases") test_basic_cases();

    printf("\nAll tests passed.\n");
    return 0;
}