#include <iostream>
#include "gtest/gtest.h"
#include "deque.h"
#include <deque>
#include <numeric>

TEST(EmptyDeque, Test1) {
    Deque<int> deque;

    EXPECT_EQ(0, deque.size());
    EXPECT_EQ(true, deque.empty());
}

TEST(OneElement, Test1) {
    Deque<int> deque;
    deque.push_back(42);

    EXPECT_EQ(1, deque.size());
    EXPECT_EQ(false, deque.empty());
    EXPECT_EQ(42, deque.back());
    EXPECT_EQ(42, deque.front());
    EXPECT_EQ(42, deque[0]);
}

TEST(OneElement, Test2) {
    Deque<int> deque;
    deque.push_back(0);

    EXPECT_EQ(1, deque.size());
    EXPECT_EQ(false, deque.empty());
    EXPECT_EQ(0, deque.back());
    EXPECT_EQ(0, deque.front());
    EXPECT_EQ(0, deque[0]);
}

TEST(OneElement, Test3) {
    Deque<int> deque;
    deque.push_back(-1);

    EXPECT_EQ(1, deque.size());
    EXPECT_EQ(false, deque.empty());
    EXPECT_EQ(-1, deque.back());
    EXPECT_EQ(-1, deque.front());
    EXPECT_EQ(-1, deque[0]);
}

TEST(ElementsAdding, Test1) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);

    EXPECT_EQ(1, deque[0]);
    EXPECT_EQ(2, deque[1]);

    deque.push_front(3);
    deque.push_front(4);

    EXPECT_EQ(4, deque[0]);
    EXPECT_EQ(3, deque[1]);
    EXPECT_EQ(1, deque[2]);
    EXPECT_EQ(2, deque[3]);
}

TEST(ElementsAdding, Test2) {
    Deque<int> deque;

    deque.push_front(1);
    deque.push_back(2);

    EXPECT_EQ(1, deque.front());
    EXPECT_EQ(2, deque.back());

    deque.push_back(3);
    deque.push_front(4);

    EXPECT_EQ(4, deque.front());
    EXPECT_EQ(3, deque.back());
}

TEST(ElementsDeleting, Test1) {
    Deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);
    deque.push_back(6);
    deque.push_back(7);

    EXPECT_EQ(1, deque.front());
    EXPECT_EQ(7, deque.back());

    deque.pop_front();
    deque.pop_back();

    EXPECT_EQ(2, deque.front());
    EXPECT_EQ(6, deque.back());

    deque.pop_front();
    deque.pop_back();

    EXPECT_EQ(3, deque.front());
    EXPECT_EQ(5, deque.back());

    deque.pop_front();
    deque.pop_back();

    EXPECT_EQ(4, deque.front());
    EXPECT_EQ(4, deque.back());
}

TEST(SqrBrackets, Test1) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);

    EXPECT_EQ(1, deque[0]);
    EXPECT_EQ(2, deque[1]);
    EXPECT_EQ(3, deque[2]);
    EXPECT_EQ(4, deque[3]);
}

TEST(DequeVsDeque, Test1) {
    enum Type { push_back, pop_back, push_front, pop_front, brackets };

    Deque<int> deque1;
    std::deque<int> deque2;

    for (int i = 0; i < 1000000; ++i) {
        Type action = Type(rand() % 5);

        if (action == push_back) {
            int key = rand();

            deque1.push_back(key);
            deque2.push_back(key);
        } else if (action == pop_back && deque2.size() > 0) {
            deque1.pop_back();
            deque2.pop_back();
        } else if (action == push_front) {
            int key = rand();

            deque1.push_front(key);
            deque2.push_front(key);
        } else if (action == pop_front && deque2.size() > 0) {
            deque1.pop_front();
            deque2.pop_front();
        } else if (action == brackets && deque2.size() > 0) {
            int index = rand() % deque2.size();

            EXPECT_EQ(deque1[index], deque2[index]);
        }
    }
}

TEST(Copy, Test1) {
    Deque<int> deque1;

    deque1.push_back(1);
    deque1.push_back(2);
    deque1.push_back(3);
    deque1.push_back(4);

    Deque<int> deque2(deque1);

    EXPECT_EQ(false, deque1.empty());
    EXPECT_EQ(false, deque2.empty());
}

TEST(Iterators, Test1) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);

    Deque<int>::iterator it = deque.begin();

    EXPECT_EQ(1, *it);      ++it;
    EXPECT_EQ(2, *it);      ++it;
    EXPECT_EQ(3, *it);      *it = 1;
    EXPECT_EQ(1, deque[2]);
}

TEST(Iterators, Test2) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);

    Deque<int>::const_iterator it = deque.cbegin();

    EXPECT_EQ(1, *it);      ++it;
    EXPECT_EQ(2, *it);      ++it;
    EXPECT_EQ(3, *it);
}

TEST(Iterators, Test3) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);

    Deque<int>::reverse_iterator it = deque.rbegin();

    EXPECT_EQ(3, *it);      ++it;
    EXPECT_EQ(2, *it);      ++it;
    EXPECT_EQ(1, *it);      *it = 3;
    EXPECT_EQ(3, deque[0]);
}

TEST(Iterators, Test4) {
    Deque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);

    Deque<int>::const_reverse_iterator it = deque.crbegin();

    EXPECT_EQ(3, *it);      ++it;
    EXPECT_EQ(2, *it);      ++it;
    EXPECT_EQ(1, *it);
}

bool full_check (const Deque<int> &deque1, const std::deque<int> &deque2) {
    if (deque1.size() != deque2.size() || deque1.empty() != deque2.empty() ||
        deque1.front() != deque2.front() || deque1.back() != deque2.back())
    {
        return false;
    }

    for (int i = 0; i < deque1.size(); ++i) {
        if (deque1[i] != deque2[i]) {
            return false;
        }
    }

    {
        auto it1 = deque1.begin();
        auto it2 = deque2.begin();
        for (; it1 != deque1.end() && it2 != deque2.end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        if ((it1 == deque1.end()) + (it2 == deque2.end()) == 1) {
            return false;
        }
    }

    {
        auto it1 = deque1.cbegin();
        auto it2 = deque2.cbegin();
        for (; it1 != deque1.cend() && it2 != deque2.cend(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        if ((it1 == deque1.cend()) + (it2 == deque2.cend()) == 1) {
            return false;
        }
    }

    {
        auto it1 = deque1.rbegin();
        auto it2 = deque2.rbegin();
        for (; it1 != deque1.rend() && it2 != deque2.rend(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        if ((it1 == deque1.rend()) + (it2 == deque2.rend()) == 1) {
            return false;
        }
    }

    {
        auto it1 = deque1.crbegin();
        auto it2 = deque2.crbegin();
        for (; it1 != deque1.crend() && it2 != deque2.crend(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        if ((it1 == deque1.crend()) + (it2 == deque2.crend()) == 1) {
            return false;
        }
    }

    return true;
}

TEST(DequeVsDeque, Test2) {
    enum Type { push_back, pop_back, push_front, pop_front, brackets };

    Deque<int> deque1;
    std::deque<int> deque2;

    for (int i = 0; i < 50; ++i) {
        Type action = Type(rand() % 5);

        for (int j = 0; j <= 10 * i; ++j) {
            int key = rand();

            if (rand() % 2) {
                deque1.push_back(key);
                deque2.push_back(key);
            } else {
                deque1.push_front(key);
                deque2.push_front(key);
            }
        }

        for (int j = 0; j < 10 * i; ++j) {
            if (rand() % 2) {
                deque1.pop_back();
                deque2.pop_back();
            } else {
                deque1.pop_front();
                deque2.pop_front();
            }

            EXPECT_TRUE(full_check(deque1, deque2));
        }
    }
}