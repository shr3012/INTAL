#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class INTAL {
private:
    string value;

public:
    // Constructors
    INTAL() : value("0") {}
    INTAL(string val) : value(val) {}

    // Function to compare two INTALs
    int compare(const INTAL& other) const {
        if (value.length() > other.value.length()) return 1;
        if (value.length() < other.value.length()) return -1;
        if (value > other.value) return 1;
        if (value < other.value) return -1;
        return 0;
    }

    // Function to add two INTALs
    INTAL add(const INTAL& other) const {
        string result = "";
        int carry = 0;
        int len1 = value.length();
        int len2 = other.value.length();
        int len = max(len1, len2);

        for (int i = 0; i < len; i++) {
            int digit1 = i < len1 ? value[len1 - i - 1] - '0' : 0;
            int digit2 = i < len2 ? other.value[len2 - i - 1] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }
        if (carry) result.push_back(carry + '0');
        reverse(result.begin(), result.end());
        return INTAL(result);
    }

    // Function to subtract two INTALs
    INTAL subtract(const INTAL& other) const {
        if (compare(other) < 0) return INTAL("0"); // Result would be negative

        string result = "";
        int borrow = 0;
        int len1 = value.length();
        int len2 = other.value.length();

        for (int i = 0; i < len1; i++) {
            int digit1 = value[len1 - i - 1] - '0';
            int digit2 = i < len2 ? other.value[len2 - i - 1] - '0' : 0;
            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }
        while (result.length() > 1 && result.back() == '0') result.pop_back(); // Remove leading zeros
        reverse(result.begin(), result.end());
        return INTAL(result);
    }

    // Function to multiply two INTALs
    INTAL multiply(const INTAL& other) const {
        int len1 = value.length();
        int len2 = other.value.length();
        vector<int> result(len1 + len2, 0);

        for (int i = len1 - 1; i >= 0; i--) {
            for (int j = len2 - 1; j >= 0; j--) {
                int mul = (value[i] - '0') * (other.value[j] - '0');
                int sum = mul + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string product = "";
        for (int num : result) {
            if (!(product.length() == 0 && num == 0)) {
                product.push_back(num + '0');
            }
        }

        return product.length() == 0 ? INTAL("0") : INTAL(product);
    }

    // Function to calculate factorial of an INTAL
    INTAL factorial() const {
        INTAL result("1");
        INTAL one("1");
        INTAL counter("1");
        while (counter.compare(*this) <= 0) {
            result = result.multiply(counter);
            counter = counter.add(one);
        }
        return result;
    }

    // Function to calculate the nth Fibonacci number
    static INTAL fibonacci(int n) {
        if (n == 0) return INTAL("0");
        if (n == 1) return INTAL("1");

        INTAL a("0");
        INTAL b("1");
        INTAL c;
        for (int i = 2; i <= n; i++) {
            c = a.add(b);
            a = b;
            b = c;
        }
        return b;
    }

    // Display function
    void display() const {
        cout << value << endl;
    }
};

int main() {
    string input1, input2;
    cout << "Enter the first INTAL: ";
    cin >> input1;
    cout << "Enter the second INTAL: ";
    cin >> input2;

    INTAL intal1(input1);
    INTAL intal2(input2);

    cout << "Comparison result (1 if greater, -1 if smaller, 0 if equal): " << intal1.compare(intal2) << endl;

    INTAL sum = intal1.add(intal2);
    cout << "Sum: ";
    sum.display();

    INTAL difference = intal1.subtract(intal2);
    cout << "Difference: ";
    difference.display();

    INTAL product = intal1.multiply(intal2);
    cout << "Product: ";
    product.display();

    int n;
    cout << "Enter an integer n to calculate the nth Fibonacci number: ";
    cin >> n;
    INTAL fib = INTAL::fibonacci(n);
    cout << n << "th Fibonacci number: ";
    fib.display();

    INTAL factorialResult = intal1.factorial();
    cout << "Factorial of first INTAL: ";
    factorialResult.display();

    return 0;
}
