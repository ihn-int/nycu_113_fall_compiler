# nycu_113_fall_compiler

NYCU 113 fall Intro. to Compiler Design

國立陽明交通大學 113 學年度上學期。編譯器設計概論。

共有 6 次作業，沒有期中或期末的專案﹐第 0 次作業是熟悉開發環境。

作業主題和前幾年相同：設計一個 Pascal-like 語言對 RISC-V 架構的編譯器。不過實際上每年 sample code 的內容和架構都會調整。

Repository 中包含每次作業使用的 code ，但不包含 .git 資料夾，因此沒有歷史紀錄。在每次作業的 report 資料夾中則有繳交的報告，部分記錄作業相關內容。以下是每次作業的分數，僅供參考，如同程式架構，測資的內容每年也不盡相同。

- hw1
  - Grade: 105
    - testcase : 100/100 pts
    - report : 5/5 pts
    - penalty: 100%
  - Grading rule:
    - penalty x (testcase * 100% + report)
  - Grader: @Compiler-f24/TA
- hw2
  - Grade: 111
    - testcase : 106/106 pts
    - report : 5/10 pts
    - penalty: 100%
  - Grading rule:
      - penalty x (testcase * 100% + report)
  - Grader: @Compiler-f24/TA
- hw3
  - Grade: 111
    - testcase : 95/95 pts
    - report : 10/10 pts
    - visitor_pattern : 6/6 pts
    - visitor_explain : 0/4 pts
    - penalty: 100%
  - Grading rule:
    - penalty x (testcase * 100% + report)
  - Grader: @Compiler-f24/TA
- hw4
  - Grade: 102
    - testcase : 92/95 pts
    ```
        h11_condition
    // Diff of hidden cases is not shown.
    ```
    - report : 10/10 pts
- hw5
  - Grade: 104
    - testcase : 99/114 pts
    - report : 5/5 pts
    ```
    16_bonus_array_1
    --- your output:(/home/student/hw/test/result/16_bonus_array_1)
    +++ answer:(/home/student/hw/test/sample_solutions/16_bonus_array_1)
    @@ -1,5 +1,5 @@
    -5
    -5
     10
    +5
    +15
     123
    -123
    +10

    17_bonus_array_2
    --- your output:(/home/student/hw/test/result/17_bonus_array_2)
    +++ answer:(/home/student/hw/test/sample_solutions/17_bonus_array_2)
    @@ -1,5 +1,5 @@
    +5
     10
    -10
    -20
    -123
    +15
     123
    +10

    18_bonus_string
    --- your output:(/home/student/hw/test/result/18_bonus_string)
    +++ answer:(/home/student/hw/test/sample_solutions/18_bonus_string)
    @@ -1 +1,6 @@
    -couldn't open ELF program: /home/student/hw/test/executable/18_bonus_string!
    +hello
    +
    +world
    +hello
    +
    +world

    19_bonus_real_1
    --- your output:(/home/student/hw/test/result/19_bonus_real_1)
    +++ answer:(/home/student/hw/test/sample_solutions/19_bonus_real_1)
    @@ -1 +1,3 @@
    -couldn't open ELF program: /home/student/hw/test/executable/19_bonus_real_1!
    +1.100000
    +2.200000
    +1.100000

    20_bonus_real_2
    --- your output:(/home/student/hw/test/result/20_bonus_real_2)
    +++ answer:(/home/student/hw/test/sample_solutions/20_bonus_real_2)
    @@ -1 +1,3 @@
    -couldn't open ELF program: /home/student/hw/test/executable/20_bonus_real_2!
    +-3.300000
    +-1.100000
    +0.500000

    h16_bonus_array_1
    // Diff of hidden cases is not shown.
    h17_bonus_array_2
    // Diff of hidden cases is not shown.
    h18_bonus_string
    // Diff of hidden cases is not shown.
    h19_bonus_real_1
    // Diff of hidden cases is not shown.
    h20_bonus_real_2
    // Diff of hidden cases is not shown.
    ```