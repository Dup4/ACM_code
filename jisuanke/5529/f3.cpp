#include <bits/stdc++.h>
using namespace std;

string s[] = {"-5000 0 5000", "-5000 1 5000", "-4373 -486 4375", "-5 4 4", "impossible", "impossible", "-637 -205 644",
        "-169 44 168", "-5000 2 5000", "-216 -52 217", "-650 -353 683", "-695 -641 843", "-11 7 10", "impossible",
        "impossible", "-265 -262 332", "-4114 -588 4118", "-3331 2195 2977", "-1373 -1276 1671", "-95 47 91",
        "-2816 -741 2833", "-401 -287 445", "impossible", "impossible", "-10 8 8", "-2683 1839 2357", "-2107 237 2106",
        "-5000 3 5000", "-2268 -249 2269", "-233 -69 235", "impossible", "impossible", "impossible", "impossible",
        "-1555 -244 1557", "-1120 -509 1154", "-3223 2358 2731", "-444 -84 445", "-27 16 25", "impossible",
        "impossible", "impossible", "impossible", "-823 -307 837", "-7 -5 8", "-2369 1709 2025", "-758 -473 815",
        "-141 49 139", "-3950 -1247 3991", "impossible", "impossible", "-796 602 659", "impossible", "-2370 1518 2141",
        "-3885 -648 3891", "-3329 1837 3131", "-672 505 559", "-998 361 982", "impossible", "impossible",
        "-1201 -163 1202", "-966 668 845", "-2744 -1561 2903", "-161 102 146", "-5000 4 5000", "-929 403 903", "1 1 4",
        "impossible", "impossible", "-403 134 398", "-2359 824 2325", "-533 401 443", "-432 -104 434", "-335 -146 344",
        "impossible", "impossible", "impossible", "impossible", "-2080 -829 2123", "-706 -196 711", "-1300 -706 1366",
        "-2368 -1719 2638", "-1317 847 1188", "-3707 1315 3651", "impossible", "impossible", "impossible",
        "-4126 -1972 4271", "-1390 -1282 1686", "-2514 1953 2036", "-1803 365 1798", "-3389 -2912 3992",
        "-4052 861 4039", "-248 -98 253", "impossible", "impossible", "-22 14 20", "-3168 -991 3200",
        "-2101 -1638 2391", "-893 -622 984", "-1797 -903 1870", "-2327 319 2325", "-239 118 229", "impossible",
        "impossible", "-7 -4 8", "-2689 -1165 2760", "-1309 947 1117", "-1165 -948 1345", "-2948 853 2924",
        "impossible", "-4793 -2312 4966", "impossible", "impossible", "impossible", "-12 8 11", "-1906 -757 1945",
        "-896 -555 962", "-4328 383 4327", "-3677 -1673 3789", "-2804 1219 2725", "impossible", "impossible",
        "-37 -16 38", "-1 0 5", "-5000 5 5000", "-2212 -419 2217", "-4034 -3881 4988", "-3989 -726 3997",
        "-1580 -1238 1801", "impossible", "impossible", "-1 2 5", "-399 167 389", "-3013 -1766 3203", "-1351 -629 1395",
        "-1116 816 946", "-758 -428 801", "-86 -77 103", "impossible", "impossible", "-139 104 116", "-7 -3 8",
        "impossible", "-2746 -2552 3342", "-8 -7 10", "-327 -263 376", "-2366 1528 2131", "impossible", "impossible",
        "-367 260 317", "-463 215 447", "-805 486 741", "-3736 -695 3744", "-2135 -516 2145", "-3693 -1049 3721",
        "impossible", "impossible", "impossible", "-1534 383 1526", "-3874 -1654 3972", "-4767 -2476 4980",
        "-4125 -1417 4180", "-3423 -2943 4033", "-66 -59 79", "impossible", "impossible", "impossible", "-802 -574 890",
        "-1354 -1012 1521", "-3834 -2149 4047", "-1328 891 1178", "impossible", "impossible", "-335 -170 349",
        "impossible", "impossible", "-1168 -160 1169", "-13 -10 15", "-2839 1503 2691", "impossible", "-4874 974 4861",
        "-90 -29 91", "-4889 976 4876", "impossible", "impossible", "-4 5 5", "-1885 -1092 2000", "-1639 318 1635",
        "-1702 -1403 1974", "-4812 -593 4815", "-377 -215 399", "-20 16 16", "impossible", "impossible", "impossible",
        "-1057 -579 1112", "-2867 -1606 3026", "-3752 -1347 3809", "-2208 508 2199", "-2318 -638 2334"};

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        int x;
        cin >> x;
        cout << s[x] << "\n";
    }
    return 0;
}
