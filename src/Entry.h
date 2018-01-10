//
// Created by phonzia on 2017/7/21.
//

#ifndef CRON_PARSER_ENTRY_H
#define CRON_PARSER_ENTRY_H


#include <string>
#include <vector>
#include "stringtool.h"

namespace sine {

template<int VALUE_START, int VALUE_END>
class Rule {
public:
    Rule() {}

    bool parse(const std::string &rule_expr) {
        std::string expr = cppbase::stringtool::trimAll(rule_expr);
        if (expr.empty()) {
            return false;
        }
        std::vector<std::string> sub_rules = cppbase::stringtool::stringSplit(expr, "/");

        if (sub_rules.size() <= 2) {
            if (cppbase::stringtool::trimAll(sub_rules[0]) == "*") {
                is_star_ = 1;
            } else {
                std::vector<std::string> between = cppbase::stringtool::stringSplit(sub_rules[0], "-");
                if (between.size() == 2) {
                    value_start_ = std::stoi(between[0]);
                    value_end_ = std::stoi(between[1]);
                    if (value_start_ < VALUE_START || value_start_ > VALUE_END ||
                        value_end_ < VALUE_START || value_end_ > VALUE_END ||
                        value_end_ < value_start_) {
                        return false;
                    }
                } else {
                    std::vector<std::string> values = cppbase::stringtool::stringSplit(sub_rules[0], ",");
                    if (values.size() > 1 && sub_rules.size() == 2) {
                        return false;
                    }
                    for (auto& value_str:values) {
                        int value = std::stoi(value_str);
                        if (value < VALUE_START || value > VALUE_END) {
                            return false;
                        }
                        value_vector_.push_back(value);
                    }

                    if (value_vector_.empty()) {
                        return false;
                    }
                }
            }

            if (sub_rules.size() == 2) {
                interval_ = std::stoi(sub_rules[1]);
                return true;
            }

            return true;
        }

        return false;
    }

    bool check(int value) {
        if (is_star_) {
            if (interval_ == 0 || value % interval_ == 0) {
                return true;
            }
        } else {
            if (value >= value_start_ && value <= value_end_) {
                if (interval_ == 0 || (value - value_start_) % interval_ == 0) {
                    return true;
                }
            }

            if (value_vector_.size() == 1 && interval_ != 0) {
                return value >= value_vector_[0] && value - value_vector_[0] % interval_ == 0;
            }

            for (size_t i = 0; i < value_vector_.size(); i++) {
                if (value == value_vector_[i]) {
                    return true;
                }
            }
        }

        return false;
    }

    void print() {
        std::cout << "value_start = " << value_start_ << std::endl;
        std::cout << "value_end = " << value_end_ << std::endl;
        std::cout << "is_star = " << is_star_ << std::endl;
        std::cout << "interval = " << interval_ << std::endl;
        std::cout << "value_vector = ";
        for (size_t i = 0; i < value_vector_.size(); ++i) {
            std::cout << value_vector_[i] << '\t';
        }
        std::cout << std::endl;
    }

    int value_start_ = -1;
    int value_end_ = -1;
    int is_star_ = 0;
    int interval_ = 0;
    std::vector<int> value_vector_;
};

typedef Rule<1, 12> Month;

typedef Rule<1, 31> Day;

typedef Rule<0, 23> Hour;

typedef Rule<0, 59> Minute;

typedef Rule<0, 59> Second;

typedef Rule<0, 6> Week;


class Entry {
public:
    Entry();

    bool parse(const std::string &cron_expr);

    bool check(time_t timestamp);

    void print() {
        month_.print();
        day_.print();
        hour_.print();
        minute_.print();
        second_.print();
        week_.print();
    }

private:
    Month month_;
    Day day_;
    Hour hour_;
    Minute minute_;
    Second second_;
    Week week_;
};
}

#endif //CRON_PARSER_ENTRY_H
