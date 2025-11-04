template<int A, int B>
struct GCD {
    static constexpr int value = GCD<B, A % B>::value;
};


template<int A>
struct GCD<A, 0> {
    static constexpr int value = A;
};


template<int A, int B>
struct Reduce {
    static constexpr int sign = (A == 0 || B == 0 ? 0 : 1) *
                            (A > 0 ? 1 : -1) *
                            (B > 0 ? 1 : -1);
    static constexpr int abs_A = (A >= 0 ? A : -A);
    static constexpr int abs_B = (B >= 0 ? B : -B);
    
    static constexpr int gcd = GCD<abs_A, abs_B>::value;

    static constexpr int first = abs_A * sign / gcd;
    static constexpr int second = abs_B / gcd;
};


template < int N = 0, int D = 1 > struct Ratio
{
    static_assert(D != 0);

	constexpr static auto num = Reduce<N, D>::first;
	
	constexpr static auto den = Reduce<N, D>::second;

    using type = Ratio < num, den > ;
};


template < typename R1, typename R2 > struct Sum
{
	constexpr static auto num = Reduce<
                                    R1::num * R2::den + R2::num * R1::den,
                                    R1::den * R2::den
                                        >::first;

	constexpr static auto den = Reduce<
                                    R1::num * R2::den + R2::num * R1::den,
                                    R1::den * R2::den
                                        >::second;
	
	using type = Ratio < num, den > ;
};


template < typename R> struct Neg
{
    constexpr static auto num = -R::num;
	
	constexpr static auto den = R::den;

    using type = Ratio < num, den > ;
};


template < typename R1, typename R2 > struct Sub
{
    constexpr static auto num = Sum< R1, Neg<R2> >::num;
	
	constexpr static auto den = Sum< R1, Neg<R2> >::den;

    using type = Ratio < num, den > ;
};


template < typename R1, typename R2 > struct Mul
{
    constexpr static auto num = Reduce<
                                    R1::num * R2::num,
                                    R1::den * R2::den
                                        >::first;
	
	constexpr static auto den = Reduce<
                                    R1::num * R2::num,
                                    R1::den * R2::den
                                        >::second;

    using type = Ratio < num, den > ;
};


template < typename R> struct Rev
{
    static_assert(R::num != 0);

    constexpr static auto num = R::den;
	
	constexpr static auto den = R::num;

    using type = Ratio < num, den > ;
};


template < typename R1, typename R2 > struct Div
{
    constexpr static auto num = Mul< R1, Rev<R2> >::num;
	
	constexpr static auto den = Mul< R1, Rev<R2> >::den;

    using type = Ratio < num, den > ;
};


template < typename R1, typename R2 > using sum = typename Sum < R1, R2 > ::type;

template < typename R > using neg = typename Neg < R > ::type;

template < typename R1, typename R2 > using sub = typename Sub < R1, R2 > ::type;

template < typename R1, typename R2 > using mul = typename Mul < R1, R2 > ::type;

template < typename R > using rev = typename Rev < R > ::type;

template < typename R1, typename R2 > using div = typename Div < R1, R2 > ::type;


template < typename T, typename R = Ratio < 1 > > struct Duration 
{
	T x = T();
    using ratio = R;
};


template 
< 
	typename T1, typename R1, 
	typename T2, typename R2 
>
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);

	return Duration < decltype(x), ratio_t > (x);
}


template 
< 
	typename T, typename R
>
constexpr auto operator-(Duration < T, R > const & dur)
{
	return Duration<T, neg<R>>(-dur.x);
}


template 
< 
	typename T1, typename R1, 
	typename T2, typename R2 
>
constexpr auto operator-(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	return lhs + (-rhs);
}


int main()
{
    using r2_4 = Ratio<2, 4>;
    using r12_18 = Ratio<12, 18>;
    using r1_6 = Ratio<1, 6>;
    using r4_6 = Ratio<4, 6>;
    using r9_15 = Ratio<9, 15>;
    using r5_7 = Ratio<5, 7>;
    using r2_6 = Ratio<2, 6>;
    using r4_5 = Ratio<4, 5>;

    static_assert(r2_4::num == 1);
    static_assert(r2_4::den == 2);
    static_assert(r12_18::num == 2);
    static_assert(r12_18::den == 3);
    
    static_assert(sum<r2_4, Ratio<1, 3>>::num == 5);
    static_assert(sum<r2_4, Ratio<1, 3>>::den == 6);
    static_assert(sum<r1_6, Ratio<1, 3>>::num == 1);
    static_assert(sum<r1_6, Ratio<1, 3>>::den == 2);
    
    static_assert(mul<r2_4, rev<r2_4>>::num == 1);
    static_assert(mul<r9_15, r5_7>::num == 3);
    static_assert(mul<r9_15, r5_7>::den == 7);
    
    static_assert(sub<r2_4, r2_6>::num == 1);
    static_assert(sub<r2_4, r2_6>::den == 6);
    
    static_assert(div<r4_6, r4_5>::num == 5);
    static_assert(div<r4_6, r4_5>::den == 6);
    static_assert(div<r2_4, mul<r2_4, r2_4>>::num == 2);
    static_assert(div<r2_4, mul<r2_4, r2_4>>::den == 1);
        
    using combo1 = mul<sum<r2_4, sum<r1_6, r1_6>>, sum<sub<r4_6, mul<r2_4, r2_4>>, r2_6>>;
    static_assert(combo1::num == 5);
    static_assert(combo1::den == 8);
    
    using combo2 = div<sub<r4_6, r1_6>, r2_4>;
    static_assert(combo2::num == 1);
    static_assert(combo2::den == 1);
    
    using combo3 = sub<sum<r2_4, mul<r2_4, r2_4>>, mul<r2_4, mul<r2_4, r2_4>>>;
    static_assert(combo3::num == 5);
    static_assert(combo3::den == 8);

    static_assert(Ratio<0, 1>::num == 0);
    static_assert(Ratio<0, 1>::den == 1);
    
    static_assert(Ratio<-1, 2>::num == -1);
    static_assert(Ratio<-1, 2>::den == 2);
    
    static_assert(Ratio<1, 1>::num == 1);
    static_assert(Ratio<1, 1>::den == 1);


    Duration<int, Ratio<1, 1000>> milliseconds(500);
    Duration<int, Ratio<1, 2>> half_seconds(1);
    Duration<int, Ratio<1, 1>> seconds(1);
    
    auto result1 = milliseconds + half_seconds;
    auto result2 = half_seconds + seconds;
    auto diff = seconds - half_seconds;

    // static_assert(decltype(result1)::ratio::num == 1001);
    // static_assert(decltype(result1)::ratio::den == 2000);

    // static_assert(decltype(result2)::ratio::num == 3);
    // static_assert(decltype(result2)::ratio::den == 2);

    // static_assert(decltype(diff)::ratio::num == 1);
    // static_assert(decltype(diff)::ratio::den == 2);
}
