#include <iostream>
#include <vector>
#include <deque>
#include <bitset>
#include <unordered_map>
#include <algorithm>
#include <map>

#define DEBUG 

namespace mymath
{
    int pow(int n, int m)
    {
        int k = 1;
        for (int i = 0; i < m; i++) k *= n;
        return k;
    }
}

#define CASE(a) break;case(a):
#define DEFAULT break;default:  
#define END break; 
#define FIRST 0

struct Colums
{
    uint8_t s1 : 4,
        s2 : 4,
        s3 : 4,
        s4 : 4;
};

struct Codes
{
    Codes(const std::vector<int>& vc) : c1(vc[0]), c2(vc[1]), c3(vc[2]) {};
    int c1,
        c2,
        c3;
    friend bool operator==(const Codes& f, const Codes& s);
};

bool operator==(const Codes& f, const Codes& s)
{
    return f.c1 == s.c1 && f.c2 == s.c2 && f.c3 == s.c3;
}

namespace std
{
    template<>
    struct hash<Codes>
    {
        std::size_t operator()(const Codes& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            return ((hash<int>()(k.c1)
                ^ (hash<int>()(k.c2) << 1)) >> 1)
                ^ (hash<int>()(k.c3) << 1);
        }
    };
}

struct HMap
{

    HMap()
    {
        Last_Elemets.resize(4, -1);
        set_empty_map();
    }

    HMap(const HMap& copy, std::pair<uint8_t, uint8_t > && swp)
    {

        this->pool_empty = copy.pool_empty;
        this->Last_Elemets = copy.Last_Elemets;
        this->history = copy.history;

        if (is_Empty_Column(swp.first)) throw std::exception("SWAP empty -> col ");

        for (int i = 0; i < size; i++)
        {
            this->Rows[i] = copy.Rows[i];
        }

        SWAP(swp);

        Last_Elemets[swp.first]--;

        this->step = copy.step + 1;

        history.push_back(swp);

        auto& el = Last_Elemets[swp.second];
        el++;
        //+-+-+-+-+-+-+-+-+END OF ALL RECURSIONS+-+-+-+-+-+-+-+-+-+
        if (el == size - 1)
        {
            if (swp.second != 0)
            {
                std::cout << "Total Iterators: " << iterators+1<<'\n';
                std::cout << "Minimum steps: " << step << "\nSteps: \n";
                for (auto i : history)
                {
                    std::cout << int(i.first) << " " << int(i.second) << '\n';
                }
                
                exit(0);
            }
        }
        //+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+
        if (Last_Elemets[swp.first] == -1) pool_empty[swp.first] = true;
        if (el == 0) pool_empty[swp.second] = false;

#ifndef DEBUG

        for (auto i : history)
        {
            std::cout << int(i.first) << "->" << int(i.second) <<' ';
        }
        std::cout << '\n';
#endif 

        iterators++;
    }

    Codes Take_Hash()
    {
        std::vector <int> vec(3);
        
        for (int i = Last_Elemets[1]; i >= 0; i--)
        {
            vec[0] += mymath::pow(10, i) * Rows[i].s2;
        }
        for (int i = Last_Elemets[2]; i >= 0; i--)
        {
            vec[1] += mymath::pow(10, i) * Rows[i].s3;
        }
        for (int i = Last_Elemets[3]; i >= 0; i--)
        {
            vec[2] += mymath::pow(10, i) * Rows[i].s4;
        }
        std::sort(vec.begin(), vec.end());
        return Codes(vec);
    }

    static constexpr void set_size(const short & sz)
    {
        size = sz;
    }

    bool is_Empty_Column(const int& col)
    {
        return pool_empty[col];
    }

    bool is_Last_Element(const int& col)
    {
        return Last_Elemets[col] == 0;
    }

    uint8_t Get_Last_Element(const int& col)
    {
        switch (col)
        {
            CASE(0)
            {
                if (Last_Elemets[0] == -1) return 511; else
                return Rows[Last_Elemets[0]].s1;
            }
            CASE(1)
            {
                if (Last_Elemets[1] == -1) return 511; else
                return Rows[Last_Elemets[1]].s2;
            }
            CASE(2)
            {
                if (Last_Elemets[2] == -1) return 511; else
                return Rows[Last_Elemets[2]].s3;
            }
            CASE(3)
            {
                if (Last_Elemets[3] == -1) return 511; else
                return Rows[Last_Elemets[3]].s4;
            }
            END
        }
    }

    std::vector <std::pair<uint8_t, uint8_t>> history;

private:

    void SWAP(const std::pair<uint8_t,uint8_t> & swp)
    {
        switch (swp.first)
        {
            CASE(0)
            {
                switch (swp.second)
                {
                    CASE(0)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s1;
                        Rows[Last_Elemets[swp.first]].s1 = Rows[Last_Elemets[swp.second] + 1].s1;
                        Rows[Last_Elemets[swp.second] + 1].s1 = std::move(t);

                    }
                    CASE(1)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s1;
                        Rows[Last_Elemets[swp.first]].s1 = Rows[Last_Elemets[swp.second] + 1].s2;
                        Rows[Last_Elemets[swp.second] + 1].s2 = std::move(t);
                    }
                    CASE(2)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s1;
                        Rows[Last_Elemets[swp.first]].s1 = Rows[Last_Elemets[swp.second] + 1].s3;
                        Rows[Last_Elemets[swp.second] + 1].s3 = std::move(t);
                    }
                    CASE(3)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s1;
                        Rows[Last_Elemets[swp.first]].s1 = Rows[Last_Elemets[swp.second] + 1].s4;
                        Rows[Last_Elemets[swp.second] + 1].s4 = std::move(t);
                    }
                    END
                }
            }
            CASE(1)
            {
                switch (swp.second)
                {
                    CASE(0)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s2;
                        Rows[Last_Elemets[swp.first]].s2 = Rows[Last_Elemets[swp.second] + 1].s1;
                        Rows[Last_Elemets[swp.second] + 1].s1 = std::move(t);
                    }
                    CASE(1)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s2;
                        Rows[Last_Elemets[swp.first]].s2 = Rows[Last_Elemets[swp.second] + 1].s2;
                        Rows[Last_Elemets[swp.second] + 1].s2 = std::move(t);
                    }
                    CASE(2)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s2;
                        Rows[Last_Elemets[swp.first]].s2 = Rows[Last_Elemets[swp.second] + 1].s3;
                        Rows[Last_Elemets[swp.second] + 1].s3 = std::move(t);
                    }
                    CASE(3)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s2;
                        Rows[Last_Elemets[swp.first]].s2 = Rows[Last_Elemets[swp.second] + 1].s4;
                        Rows[Last_Elemets[swp.second] + 1].s4 = std::move(t);
                    }
                    END
                }
            }
            CASE(2)
            {
                switch (swp.second)
                {
                    CASE(0)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s3;
                        Rows[Last_Elemets[swp.first]].s3 = Rows[Last_Elemets[swp.second] + 1].s1;
                        Rows[Last_Elemets[swp.second] + 1].s1 = std::move(t);
                    }
                    CASE(1)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s3;
                        Rows[Last_Elemets[swp.first]].s3 = Rows[Last_Elemets[swp.second] + 1].s2;
                        Rows[Last_Elemets[swp.second] + 1].s2 = std::move(t);
                    }
                    CASE(2)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s3;
                        Rows[Last_Elemets[swp.first]].s3 = Rows[Last_Elemets[swp.second] + 1].s3;
                        Rows[Last_Elemets[swp.second] + 1].s3 = std::move(t);
                    }
                    CASE(3)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s3;
                        Rows[Last_Elemets[swp.first]].s3 = Rows[Last_Elemets[swp.second] + 1].s4;
                        Rows[Last_Elemets[swp.second] + 1].s4 = std::move(t);
                    }
                    END
                }
            }
            CASE(3)
            {

                switch (swp.second)
                {
                    CASE(0)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s4;
                        Rows[Last_Elemets[swp.first]].s4 = Rows[Last_Elemets[swp.second] + 1].s1;
                        Rows[Last_Elemets[swp.second] + 1].s1 = std::move(t);
                    }
                    CASE(1)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s4;
                        Rows[Last_Elemets[swp.first]].s4 = Rows[Last_Elemets[swp.second] + 1].s2;
                        Rows[Last_Elemets[swp.second] + 1].s2 = std::move(t);
                    }
                    CASE(2)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s4;
                        Rows[Last_Elemets[swp.first]].s4 = Rows[Last_Elemets[swp.second] + 1].s3;
                        Rows[Last_Elemets[swp.second] + 1].s3 = std::move(t);
                    }
                    CASE(3)
                    {
                        auto t = Rows[Last_Elemets[swp.first]].s4;
                        Rows[Last_Elemets[swp.first]].s4 = Rows[Last_Elemets[swp.second] + 1].s4;
                        Rows[Last_Elemets[swp.second] + 1].s4 = std::move(t);
                    }
                    END
                }
            }
            END
        }
    }


    void set_empty_map()
    {
        for (int i = 0; i < size; i++)
        {
            Rows[i].s1 = size - i;
        }
        Last_Elemets[0] = size - 1;
    }

    static int iterators;

    static short size;

    short step = 0;
    std::vector <int8_t> Last_Elemets;
    std::vector <Colums> Rows{size};
    std::bitset<4> pool_empty{14};

};

short HMap::size = 6;

int HMap::iterators = 0;



class Hanoi
{

    Hanoi() {}
    static Hanoi* instanse;
    std::unordered_map <Codes, bool> Unique;
    std::deque <HMap> Recursion{1};

    bool is_Bad_History(const HMap & rec)
    {
        for (int i = 1; i * 2 <= rec.history.size(); i++)
        {
            bool is_circle = true;
            int p = i;
            int l = 0;
            while (p--)
            {
                auto data = rec.history[(p+1)*2-1];
                std::swap(data.first, data.second);
                if (rec.history[l] != data)
                {
                    is_circle = false;
                    break;
                }
                l++;
            }
            if (is_circle) return true;
        }
        return false;
    }

    inline bool is_empty_step(const std::pair<uint8_t, uint8_t> & fr)
    {
        return Recursion[FIRST].is_Empty_Column(fr.second) && Recursion[FIRST].is_Last_Element
                                                                         (fr.first) && fr.first!=0;
    }

    void RULES()
    {
        while (Recursion.size())
        {
            if (!is_Bad_History(Recursion[FIRST]))
            for (int i = 0; i < 4; i++)
            {
                if (Recursion[FIRST].is_Empty_Column(i)) continue;
                for (int j = 0; j < 4; j++)
                {
                    if (i != j)
                    {          
                        if (Recursion[FIRST].Get_Last_Element(i) < Recursion[FIRST].Get_Last_Element(j))
                        {       
                            if (!is_empty_step({ i,j }))
                            {
                                auto data = HMap(Recursion[FIRST], { i,j });
                               Codes hash = data.Take_Hash();
                               if (Unique.find(hash)->second)
                               {
                                    Recursion.push_back(std::move(data));
                                    Unique[hash] = false;
                                }
                            }         
                        }
                    }
                }
            }
            Recursion.erase(Recursion.begin());
        }
    }
                

public:

    constexpr static void setCircles(uint16_t&& circles)
    {
        HMap::set_size(circles);
    }

    static Hanoi* getInstanse()
    {

        if (instanse == nullptr)
        {
            instanse = new Hanoi{};
        }
        return instanse;
    }

    void start() 
    {
        RULES();
    }


};


Hanoi* Hanoi::instanse = nullptr;

int main()
{
    Hanoi::setCircles(10);
    Hanoi::getInstanse()->start();
}
