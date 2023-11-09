    #include <iostream>
    #include<string>
    #include <concepts>

    /***********************************************************/

    #define CONDITION_0   1     // hash method that returns a value that is converted to long

    #define CONDITION_1   1     // toString method that returns std::string

    #define CONDITION_2   1     // class has no virtual destructor

    /***********************************************************/

    // concept

    template<class T>
    concept ComplexConcept = requires(T v)
    {
        {v.hash()}->std::convertible_to<long>;
        {v.toString()}->std::same_as<std::string>;
    }
    && !std::has_virtual_destructor_v<T>;

    /***********************************************************/

    // test class

    class Test_Class {
    public:
 
        Test_Class(int _n) :n(_n) {};
  
#if CONDITION_0
        int hash() const { return 0; };                             // condition 0 is met
#endif

#if CONDITION_1  
        std::string toString() const { return std::to_string(n); }  // condition 1 is met
#endif

#if !CONDITION_2                        
        virtual ~Test_Class(){};                                    // condition 2 is not met
#endif

    private:
        int n = 0;
    };

    /***********************************************************/

    template<ComplexConcept T>
    void test_Function(T x) 
    {
        long n = x.hash();
        std::cout << n << std::endl;
    };

    /***********************************************************/
    
    int main() {
        Test_Class x(0);
        test_Function<Test_Class>(x);
        return 0;
    };

    /***********************************************************/
