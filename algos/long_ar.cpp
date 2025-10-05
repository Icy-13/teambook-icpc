struct LongInt {
    inline static const int base = 1e8;
    inline static const int base_len = 8;
    vector <int> number;
    bool negative = 0;

    size_t size() const {
        return number.size();
    }

    LongInt(ll v = 0) {
        do {
            number.push_back(v % base);
            v /= base;
        } while (v > 0);
    }

    LongInt(string s) {
        if (s[0] == '-') {
            negative = 1;
            s.erase(0, 1);
        }
        reverse(s.begin(), s.end());
        for (int it = 0; it < s.length(); it += base_len) {
            string temp = s.substr(it, min(base_len, (int)s.length() - it));
            reverse(temp.begin(), temp.end());
            number.push_back(stoi(temp));
        }
    }

    LongInt copy() const {
        return *this;
    }

    bool is_negative() const {
        return negative;
    }

    LongInt& operator+=(LongInt& other) {
        if (is_negative() && !other.is_negative()) {
            negative = 0;
            other -= *this;
            swap(other);
            return *this;
        }
        if (!is_negative() && other.is_negative()) {
            other.negative = 0;
            *this -= other;
            return *this;
        }
        int carry = 0;
        number.resize(max(size(), other.size()));
        for (size_t i = 0; i < max(size(), other.size()); i++) {
            ll temp = 1ll * get(i) + other.get(i) + carry;
            number[i] = temp % base;
            carry = temp / base;
        }
        if (carry) {
            number.push_back(carry);
        }
        return *this;
    }

    LongInt& operator-=(LongInt& other) {
        if (is_negative() && !other.is_negative()) {
            other.negative = 1;
            other += *this;
            swap(other);
            return *this;
        }
        if (!is_negative() && other.is_negative()) {
            other.negative = 0;
            *this += other;
            return *this;
        }
        if (is_negative() && other.is_negative()) {
            negative = 0;
            other.negative = 0;
            swap(other);
        }
        if (*this < other) {
            swap(other);
            negative = 1;
        }
        int carry = 0;
        for (size_t i = 0; i < size(); i++) {
            ll temp = 1ll * get(i) - carry - other.get(i);
            carry = 0;
            if (temp < 0) {
                carry = 1;
                temp += base;
            }
            number[i] = temp;
        }
        while (size() > 1 && !number.back()) {
            number.pop_back();
        }
        return *this;
    }

    LongInt& operator*=(const int& other) {
        negative ^= (other < 0);
        int carry = 0;
        for (size_t i = 0; i < size(); i++) {
            ll temp = 1ll * get(i) * other + carry;
            number[i] = temp % base;
            carry = temp / base;
        }
        if (carry) {
            number.push_back(carry);
        }
        while (size() > 1 && !number.back()) {
            number.pop_back();
        }
        return *this;
    }

    LongInt& operator*=(LongInt& other) {
        negative ^= other.is_negative();
        if (size() < other.size()) {
            swap(other);
        }
        LongInt res(0);
        for (int i = 0; i < other.size(); i++) {
            LongInt temp = (*this) * other.get(i);
            vector <int> new_number;
            new_number.assign(i, 0);
            for (int i = 0; i < temp.size(); i++) {
                new_number.push_back(temp.get(i));
            }
            std::swap(temp.number, new_number);
            res += temp;
        }
        swap(res);
        return *this;
    }

    LongInt& operator%=(const int& other) {
        pair <LongInt, int> res = div_mod(*this, other);
        LongInt temp(res.second * (is_negative() ? -1 : 1));
        swap(temp);
        return *this;
    }

    LongInt& operator/=(const int& other) {
        negative = (*this).is_negative() ^ (other < 0);
        pair <LongInt, int> res = div_mod(*this, abs(other));
        swap(res.first);
        return *this;
    }

    pair <LongInt, int> div_mod(LongInt& left, int rhs) {
        int carry = 0;
        for (int i = size() - 1; i >= 0; i--) {
            ll temp = get(i) + 1ll * carry * base;
	        number[i] = temp / rhs;
	        carry = temp % rhs;
        }
        while (size() > 1 && !number.back()) {
            number.pop_back();
        }
        return make_pair(*this, carry);
    }

    void swap(LongInt& other) {
        std::swap(number, other.number);
        std::swap(negative, other.negative);
    }

    void swap(LongInt& lhs, LongInt& rhs) {
        lhs.swap(rhs);
    }

    friend bool operator<(LongInt& left, LongInt& right) {
        if (left.negative && !right.negative) return true;
        if (!left.negative && right.negative) return false;
        int i = max(left.size(), right.size()) - 1;
        while (i >= 0) {
            int l = left.get(i);
            int r = right.get(i);
            if (left.negative) {
                if (l > r) return true;
                if (l < r) return false;
            } else {
                if (l < r) return true;
                if (l > r) return false;
            }
            i--;
        }
        return 0;
    }

    friend bool operator==(LongInt& left, LongInt& right) {
        if (left.negative != right.negative) return false;
        int i = max(left.size(), right.size()) - 1;
        while (i >= 0) {
            int l = left.get(i);
            int r = right.get(i);
            if (l < r) {
                return 0;
            } else if (l > r) {
                return 0;
            }
            i--;
        }
        return 1;
    }

    friend LongInt operator+(LongInt& left, LongInt& right) {
        LongInt result = left;
        result += right;
        return result;
    }

    friend LongInt operator-(LongInt& left, LongInt& right) {
        LongInt result = left;
        result -= right;
        return result;
    }

    friend LongInt operator*(LongInt& left, const int& right) {
        LongInt result = left;
        result *= right;
        return result;
    }

    friend LongInt operator*(LongInt& left, LongInt& right) {
        LongInt result = left;
        result *= right;
        return result;
    }

    friend LongInt operator/(LongInt& left, const int& right) {
        LongInt result = left;
        result /= right;
        return result;
    }

    friend LongInt operator%(LongInt& left, const int& right) {
        LongInt result = left;
        result %= right;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const LongInt& num) {
        if (num.negative) {
            os << "-";
        }

        if (!num.number.empty()) {
            os << num.number.back();
        } else {
            os << "0";
            return os;
        }

        for (int i = num.number.size() - 2; i >= 0; i--) {
            os.width(base_len);
            os.fill('0');
            os << num.number[i];
        }

        return os;
    }

    friend istream& operator>>(istream& is, LongInt& num) {
        string s;
        is >> s;
        num = LongInt(s);
        return is;
    }

    private:
        void normalize(LongInt& left, LongInt& right) {
            while (left.size() > right.size()) {
                right.number.push_back(0);
            }
            while (left.size() < right.size()) {
                left.number.push_back(0);
            }
        }

        int get(int index) const {
            return (index < size()) ? number[index] : 0;
        }
};
