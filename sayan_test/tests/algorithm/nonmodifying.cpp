#include <sayan/algorithm.hpp>

#include <sayan/cursor/istream.hpp>

#include <catch/catch.hpp>

#include <algorithm>
#include <forward_list>

TEST_CASE("algorithms/nonmodifying/quantors: all_of, any_of, some_of")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    for(auto const & s : strs)
    {
        CHECK(::sayan::all_of(sayan::cursor(std::istringstream(s)), pred)
              == std::all_of(s.begin(), s.end(), pred));
        CHECK(::sayan::any_of(sayan::cursor(std::istringstream(s)), pred)
              == std::any_of(s.begin(), s.end(), pred));
        CHECK(::sayan::none_of(sayan::cursor(std::istringstream(s)), pred)
              == std::none_of(s.begin(), s.end(), pred));
    }
}

TEST_CASE("algorithms/nonmodifying/quantors: auto-cursor")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    for(auto const & s : strs)
    {
        CHECK(::sayan::all_of(std::istringstream(s), pred)
              == std::all_of(s.begin(), s.end(), pred));
        CHECK(::sayan::any_of(std::istringstream(s), pred)
              == std::any_of(s.begin(), s.end(), pred));
        CHECK(::sayan::none_of(std::istringstream(s), pred)
              == std::none_of(s.begin(), s.end(), pred));
    }
}

TEST_CASE("algorithms/nonmodifying/for_each")
{
    std::string const src{"Alex Stepanov"};

    std::string out;

    auto cur = sayan::for_each(::sayan::cursor(std::istringstream(src)),
                               [&out](char c){ out.push_back(c);});

    CHECK(out == src);
    CHECK(cur.empty());
}

TEST_CASE("algorithms/nonmodifying/for_each: auto-cursor")
{
    std::string const src{"Alex Stepanov"};

    std::string out;

    auto cur = sayan::for_each(std::istringstream(src),
                               [&out](char c){ out.push_back(c);});

    CHECK(out == src);
    CHECK(cur.empty());
}

TEST_CASE("algorithms/for_each: on forward")
{
    std::string const src{"Alex Stepanov"};

    std::string out;

    std::forward_list<int> const in(src.begin(), src.end());
    auto cur = sayan::for_each(in, [&out](char c){ out.push_back(c);});

    CHECK(cur.traversed_begin() == in.begin());
    CHECK(cur.begin() == in.end());
    CHECK(cur.end() == in.end());

    CHECK(out == src);
    CHECK(cur.empty());
}

TEST_CASE("algorithms/nonmodifying/find: success")
{
    std::string const src{"Alex Stepanov"};

    auto const value = 'e';

    auto const r_std = std::find(src.begin(), src.end(), value);

    CHECK((r_std != src.end()));

    std::istringstream is(src);

    auto const r = sayan::find(sayan::cursor(is), value);

    CHECK(!r.empty());

    std::string rest;
    sayan::for_each(r, [&rest](char c){ rest.push_back(c);});

    CHECK(rest == std::string(r_std, src.end()));
}

TEST_CASE("algorithm/find: forward")
{
    std::forward_list<int> const xs{1, 2, 4, 5, 6};
    auto const value = 4;

    auto const r_std = std::find(xs.begin(), xs.end(), value);
    auto const r = sayan::find(xs, value);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithms/nonmodifying/find: success, auto-cursor")
{
    std::string const src{"Alex Stepanov"};

    auto const value = 'e';

    auto const r_std = std::find(src.begin(), src.end(), value);

    CHECK((r_std != src.end()));

    std::istringstream is(src);

    auto const r = sayan::find(is, value);

    CHECK(!r.empty());

    std::string rest;
    sayan::for_each(r, [&rest](char c){ rest.push_back(c);});

    CHECK(rest == std::string(r_std, src.end()));
}

TEST_CASE("algorithms/nonmodifying/find: fail")
{
    std::string const src{"Alex Stepanov"};

    auto const value = 'z';

    auto const r_std = std::find(src.begin(), src.end(), value);

    CHECK((r_std == src.end()));

    std::istringstream is(src);

    auto const r = sayan::find(sayan::cursor(is), value);

    CHECK(r.empty());
}

TEST_CASE("algorithms/nonmodifying/find: fail, auto-cursor")
{
    std::string const src{"Alex Stepanov"};

    auto const value = 'z';

    auto const r_std = std::find(src.begin(), src.end(), value);

    CHECK((r_std == src.end()));

    std::istringstream is(src);

    auto const r = sayan::find(is, value);

    CHECK(r.empty());
}

TEST_CASE("algorithms/nonmodifying/find_if_not: success")
{
    std::string const src{"Alex Stepanov"};

    auto const pred = [](char c) { return std::isupper(c); };

    auto const r_std = std::find_if_not(src.begin(), src.end(), pred);

    CHECK((r_std != src.end()));

    std::istringstream is(src);

    auto const r = sayan::find_if_not(sayan::cursor(is), pred);

    CHECK(!r.empty());

    std::string rest;
    sayan::for_each(r, [&rest](char c){ rest.push_back(c);});

    CHECK(rest == std::string(r_std, src.end()));
}

TEST_CASE("algorithms/nonmodifying/find_if_not: fail")
{
    std::string const src{"STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    auto const r_std = std::find_if_not(src.begin(), src.end(), pred);

    CHECK((r_std == src.end()));

    std::istringstream is(src);

    auto const r = sayan::find_if_not(sayan::cursor(is), pred);

    CHECK(r.empty());
}

TEST_CASE("algorithms/nonmodifying/find_if_not: success, auto-cursor")
{
    std::string const src{"Alex Stepanov"};

    auto const pred = [](char c) { return std::isupper(c); };

    auto const r_std = std::find_if_not(src.begin(), src.end(), pred);

    CHECK((r_std != src.end()));

    std::istringstream is(src);

    auto const r = sayan::find_if_not(is, pred);

    CHECK(!r.empty());

    std::string rest;
    sayan::for_each(r, [&rest](char c){ rest.push_back(c);});

    CHECK(rest == std::string(r_std, src.end()));
}

TEST_CASE("algorithms/nonmodifying/find_if_not: fail, auto-cursor")
{
    std::string const src{"STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    auto const r_std = std::find_if_not(src.begin(), src.end(), pred);

    CHECK((r_std == src.end()));

    std::istringstream is(src);

    auto const r = sayan::find_if_not(is, pred);

    CHECK(r.empty());
}

TEST_CASE("algorithm/find_if: forward")
{
    std::forward_list<int> const xs{1, 2, 4, 5, 6};
    auto const pred = [](int x) { return x % 2 == 0;};

    auto const r_std = std::find_if(xs.begin(), xs.end(), pred);
    auto const r = sayan::find_if(xs, pred);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/find_if_not: forward")
{
    std::forward_list<int> const xs{1, 2, 4, 5, 6};
    auto const pred = [](int x) { return x % 2 == 0;};

    auto const r_std = std::find_if_not(xs.begin(), xs.end(), pred);
    auto const r = sayan::find_if_not(xs, pred);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/find_first_of")
{
    std::forward_list<int> const whats{1,2,3,5,8,13,21};
    std::forward_list<int> const where{25,5,49,7};

    auto r_std = std::find_first_of(whats.begin(), whats.end(), where.begin(), where.end());
    auto r = ::sayan::find_first_of(whats, where);

    CHECK(r.traversed_begin() == whats.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == whats.end());
}

TEST_CASE("algorithm/find_first_of: custom predicate, success")
{
    std::forward_list<int> const whats{1,2,3,5,8,13,21};
    std::forward_list<int> const where{25,-5,-49,7};

    auto const pred = [](auto x, auto y) { return std::abs(x) == std::abs(y); };

    auto r_std = std::find_first_of(whats.begin(), whats.end(), where.begin(), where.end(), pred);
    auto r = ::sayan::find_first_of(whats, where, pred);

    CHECK(r_std != whats.end());
    CHECK(!!r);

    CHECK(r.traversed_begin() == whats.begin());
    CHECK(r.begin() == r_std);
    CHECK(*r.begin() == *r_std);
    CHECK(r.end() == whats.end());
}

TEST_CASE("algorithm/find_first_of: custom predicate, fail")
{
    std::forward_list<int> const whats{1,2,3,5,8,13,21};
    std::forward_list<int> const where{0,-4,9,-10};

    auto const pred = [](auto x, auto y) { return std::abs(x) == std::abs(y); };

    auto r_std = std::find_first_of(whats.begin(), whats.end(), where.begin(), where.end(), pred);
    auto r = ::sayan::find_first_of(whats, where, pred);

    CHECK(r_std == whats.end());
    CHECK(!r);

    CHECK(r.traversed_begin() == whats.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == whats.end());
}

TEST_CASE("algorithm/adjacent_find")
{
    std::forward_list<int> const xs{1, 2, 3, 3, 4, 5};

    auto const r_std = std::adjacent_find(xs.begin(), xs.end());

    auto const r = sayan::adjacent_find(xs);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/adjacent_find: custom predicate, fail")
{
    std::forward_list<int> const xs{1, 2, 3, 3, 4, 5};
    auto const pred = std::greater<>{};

    auto const r_std = std::adjacent_find(xs.begin(), xs.end(), pred);
    auto const r = sayan::adjacent_find(xs, pred);

    CHECK(r_std == xs.end());
    CHECK(!r);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/adjacent_find: custom predicate, success")
{
    std::forward_list<int> const xs{1, 2, 4, 3, 6, 5};
    auto const pred = std::greater<>{};

    auto const r_std = std::adjacent_find(xs.begin(), xs.end(), pred);
    auto const r = sayan::adjacent_find(xs, pred);

    CHECK(r_std != xs.end());
    CHECK(!!r);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/search")
{
    std::forward_list<int> const haystack{2,7,1,8,2,8,1,8,2,8,4,6};
    std::forward_list<int> const needle{1,8,2,8};

    auto const r_std = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    auto const r = ::sayan::search(haystack, needle);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search: custom predicate, success")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{"or"};

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::search(haystack.begin(), haystack.end(),
                                   needle.begin(), needle.end(), pred);
    auto const r = ::sayan::search(haystack, needle, pred);

    CHECK(r_std != haystack.end());
    CHECK(!!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search: custom predicate, fail")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{"order"};

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::search(haystack.begin(), haystack.end(),
                                   needle.begin(), needle.end(), pred);
    auto const r = ::sayan::search(haystack, needle, pred);

    CHECK(r_std == haystack.end());
    CHECK(!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search: custom predicate, empty needle")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{};

    CHECK(needle.empty());

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r = ::sayan::search(haystack, needle, pred);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == haystack.begin());
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search_n")
{
    std::forward_list<int> const xs{0,1,0,1,1,0,0,1,1,1,0,0};
    auto const n = 2;
    auto const value = int{1};

    auto const r_std = std::search_n(xs.begin(), xs.end(), n, value);
    auto const r = sayan::search_n(xs, n, value);

    CHECK(r.traversed_begin() == xs.begin());
    CHECK(r.begin() == r_std);
    CHECK(std::distance(xs.begin(), r.begin()) == std::distance(xs.begin(), r_std));
    CHECK(r.end() == xs.end());
}

TEST_CASE("algorithm/search_n: custom predicate, success")
{
    std::string const haystack{"succeSs, success"};
    auto const n = 2;
    auto const value = 's';

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::search_n(haystack.begin(), haystack.end(), n, value, pred);
    auto const r = ::sayan::search_n(haystack, n, value, pred);

    CHECK(r_std != haystack.end());
    CHECK(!!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK((r.begin() - haystack.begin()) == (r_std - haystack.begin()));
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search_n: custom predicate, fail")
{
    std::string const haystack{"succeSs, success"};
    auto const n = 3;
    auto const value = 's';

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::search_n(haystack.begin(), haystack.end(), n, value, pred);
    auto const r = ::sayan::search_n(haystack, n, value, pred);

    CHECK(r_std == haystack.end());
    CHECK(!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK((r.begin() - haystack.begin()) == (r_std - haystack.begin()));
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/search_n: custom predicate, empty needle")
{
    std::string const haystack{"predicate"};
    auto const n = 0;
    auto const value = 's';

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r = ::sayan::search_n(haystack, n, value, pred);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == haystack.begin());
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/find_end")
{
    std::forward_list<int> const haystack{2,7,1,8,2,8,1,8,2,8,4,6};
    std::forward_list<int> const needle{1,8,2,8};

    auto const r_std = std::find_end(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    auto const r = ::sayan::find_end(haystack, needle);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/find_end: custom predicate, success")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{"or"};

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::find_end(haystack.begin(), haystack.end(),
                                   needle.begin(), needle.end(), pred);
    auto const r = ::sayan::find_end(haystack, needle, pred);

    CHECK(r_std != haystack.end());
    CHECK(!!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/find_end: custom predicate, fail")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{"order"};

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r_std = std::find_end(haystack.begin(), haystack.end(),
                                   needle.begin(), needle.end(), pred);
    auto const r = ::sayan::find_end(haystack, needle, pred);

    CHECK(r_std == haystack.end());
    CHECK(!r);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == r_std);
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithm/find_end: custom predicate, empty needle")
{
    std::string const haystack{"ALGORITHMS/nonmodifying/count: auto-cursor"};
    std::string const needle{};

    CHECK(needle.empty());

    auto const pred = [](auto x, auto y) { return std::tolower(x) == std::tolower(y);};

    auto const r = ::sayan::find_end(haystack, needle, pred);

    CHECK(r.traversed_begin() == haystack.begin());
    CHECK(r.begin() == haystack.end());
    CHECK(r.end() == haystack.end());
}

TEST_CASE("algorithms/nonmodifying/count")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const value = 'e';

    for(auto const & s : strs)
    {
        std::istringstream is(s);
        CHECK(::sayan::count(sayan::cursor(is), value)
              == std::count(s.begin(), s.end(), value));
    }
}

TEST_CASE("regression #29: cursor() is ambigeous for cursors")
{
    std::string const s{};

    auto const value = 'e';

    auto cur = ::sayan::cursor(s);
    auto cur1 = ::sayan::cursor(cur);

    CHECK(::sayan::count(cur1, value) == 0);
}

TEST_CASE("algorithms/nonmodifying/count: auto-cursor")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const value = 'e';

    for(auto const & s : strs)
    {
        std::istringstream is(s);
        CHECK(::sayan::count(is, value)
              == std::count(s.begin(), s.end(), value));
    }
}

TEST_CASE("algorithms/nonmodifying/count_if")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    for(auto const & s : strs)
    {
        std::istringstream is(s);

        CHECK(::sayan::count_if(sayan::cursor(is), pred)
              == std::count_if(s.begin(), s.end(), pred));
    }
}

TEST_CASE("algorithms/nonmodifying/count_if: auto-cursor")
{
    std::vector<std::string> const strs{"", "generic_programming",
                                        "Alex Stepanov", "STL"};

    auto const pred = [](char c) { return std::isupper(c); };

    for(auto const & s : strs)
    {
        std::istringstream is(s);

        CHECK(::sayan::count_if(is, pred)
              == std::count_if(s.begin(), s.end(), pred));
    }
}

TEST_CASE("algorithms/nonmodifying/equal")
{
    std::vector<std::string> const strs
        = {"Art", "Artist", "Burden", "art", "artist", "buRDen"};

    for(auto const & x : strs)
    for(auto const & y : strs)
    {
        auto const r_std = std::equal(x.begin(), x.end(),
                                      y.begin(), y.end());

        auto const r_sayan
            = ::sayan::equal(sayan::cursor(std::istringstream(x)),
                             sayan::cursor(std::istringstream(y)));

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/nonmodifying/equal: auto-cursor")
{
    std::vector<std::string> const strs
        = {"Art", "Artist", "Burden", "art", "artist", "buRDen"};

    for(auto const & x : strs)
    for(auto const & y : strs)
    {
        auto const r_std = std::equal(x.begin(), x.end(),
                                      y.begin(), y.end());

        auto const r_sayan = ::sayan::equal(std::istringstream(x),
                                            std::istringstream(y));

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/nonmodifying/equal with predicate")
{
    std::vector<std::string> const strs
        = {"Art", "Artist", "Burden", "art", "artist", "buRDen"};

    auto eq = [](char x, char y)
    {
        return std::tolower(x) == std::tolower(y);
    };

    for(auto const & x : strs)
    for(auto const & y : strs)
    {
        auto const r_std = std::equal(x.begin(), x.end(),
                                      y.begin(), y.end(), eq);

        auto const r_sayan
            = ::sayan::equal(sayan::cursor(std::istringstream(x)),
                             sayan::cursor(std::istringstream(y)), eq);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/nonmodifying/equal: with predicate, auto-cursor")
{
    std::vector<std::string> const strs
        = {"Art", "Artist", "Burden", "art", "artist", "buRDen"};

    auto eq = [](char x, char y)
    {
        return std::tolower(x) == std::tolower(y);
    };

    for(auto const & x : strs)
    for(auto const & y : strs)
    {
        auto const r_std = std::equal(x.begin(), x.end(),
                                      y.begin(), y.end(), eq);

        auto const r_sayan = ::sayan::equal(std::istringstream(x),
                                            std::istringstream(y), eq);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithm/mismatch: forward")
{
    std::forward_list<int> const xs1{1, 2, 3, 5, 8};
    std::forward_list<int> const xs2{1, 2, 3, 4, 5};

    auto const r_std = std::mismatch(xs1.begin(), xs1.end(), xs2.begin(), xs2.end());
    auto const r = sayan::mismatch(xs1, xs2);

    CHECK(r.first.traversed_begin() == xs1.begin());
    CHECK(r.first.begin() == r_std.first);
    CHECK(r.first.end() == xs1.end());

    CHECK(r.second.traversed_begin() == xs2.begin());
    CHECK(r.second.begin() == r_std.second);
    CHECK(r.second.end() == xs2.end());
}

TEST_CASE("algorithms/is_partitioned")
{
    std::vector<std::string> const strs{"", "generic", "AlexStepanov", "STL",
                                        "STLauthor", "authorofSTL"};

    auto const pred = [](char c) { return std::islower(c); };

    for(auto s : strs)
    {
        CHECK(::sayan::is_partitioned(sayan::cursor(std::istringstream(s)), pred)
              == std::is_partitioned(s.begin(), s.end(), pred));

        std::partition(s.begin(), s.end(), pred);

        CHECK(std::is_partitioned(s.begin(), s.end(), pred));
        CHECK(::sayan::is_partitioned(sayan::cursor(std::istringstream(s)), pred));
    }
}

TEST_CASE("algorithms/is_partitioned: auto-cursor")
{
    std::vector<std::string> const strs{"", "generic", "AlexStepanov", "STL",
                                        "STLauthor", "authorofSTL"};

    auto const pred = [](char c) { return std::islower(c); };

    for(auto s : strs)
    {
        CHECK(::sayan::is_partitioned(std::istringstream(s), pred)
              == std::is_partitioned(s.begin(), s.end(), pred));

        std::partition(s.begin(), s.end(), pred);

        CHECK(std::is_partitioned(s.begin(), s.end(), pred));
        CHECK(::sayan::is_partitioned(std::istringstream(s), pred));
    }
}

TEST_CASE("algorithms/lexicographical_compare")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "acbd", "aBCd"};

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::lexicographical_compare(s1.begin(), s1.end(),
                                                        s2.begin(), s2.end());

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan =
            ::sayan::lexicographical_compare(::sayan::cursor(is1),
                                             ::sayan::cursor(is2));

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/lexicographical_compare: auto-cursor")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "acbd", "aBCd"};

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::lexicographical_compare(s1.begin(), s1.end(),
                                                        s2.begin(), s2.end());

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::lexicographical_compare(is1, is2);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/lexicographical_compare with custom compare")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "acbd", "aBCd"};

    auto const cmp
        = [](char x, char y) { return std::toupper(x) < std::toupper(y); };

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::lexicographical_compare(s1.begin(), s1.end(),
                                                        s2.begin(), s2.end(),
                                                        cmp);

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan =
            ::sayan::lexicographical_compare(::sayan::cursor(is1),
                                             ::sayan::cursor(is2), cmp);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/lexicographical_compare: custom compare, auto-cursor")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "acbd", "aBCd"};

    auto const cmp
        = [](char x, char y) { return std::toupper(x) < std::toupper(y); };

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::lexicographical_compare(s1.begin(), s1.end(),
                                                        s2.begin(), s2.end(),
                                                        cmp);

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::lexicographical_compare(is1, is2, cmp);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/set_operations/includes")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "aabc"};

    for(auto const & s : strs)
    {
        CHECK(std::is_sorted(s.begin(), s.end()));
    }

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::includes(s1.begin(), s1.end(),
                                         s2.begin(), s2.end());

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::includes(::sayan::cursor(is1),
                                               ::sayan::cursor(is2));

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/set_operations/includes: auto-cursor")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "aabc"};

    for(auto const & s : strs)
    {
        CHECK(std::is_sorted(s.begin(), s.end()));
    }

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::includes(s1.begin(), s1.end(),
                                         s2.begin(), s2.end());

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::includes(is1, is2);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/set_operations/includes: custom predicate")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "aabc", "aAbC"};

    auto const cmp
        = [](char x, char y) { return std::toupper(x) < std::toupper(y); };

    for(auto const & s : strs)
    {
        CHECK(std::is_sorted(s.begin(), s.end(), cmp));
    }

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::includes(s1.begin(), s1.end(),
                                         s2.begin(), s2.end(), cmp);

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::includes(::sayan::cursor(is1),
                                               ::sayan::cursor(is2), cmp);

        CHECK(r_std == r_sayan);
    }
}

TEST_CASE("algorithms/set_operations/includes: custom predicate, auto-cursor")
{
    std::vector<std::string> const strs{"", "abc", "abcd", "aabc", "aAbC"};

    auto const cmp
        = [](char x, char y) { return std::toupper(x) < std::toupper(y); };

    for(auto const & s : strs)
    {
        CHECK(std::is_sorted(s.begin(), s.end(), cmp));
    }

    for(auto const & s1 : strs)
    for(auto const & s2 : strs)
    {
        auto const r_std = std::includes(s1.begin(), s1.end(),
                                         s2.begin(), s2.end(), cmp);

        std::istringstream is1(s1);
        std::istringstream is2(s2);

        auto const r_sayan = ::sayan::includes(is1, is2, cmp);

        CHECK(r_std == r_sayan);
    }
}
